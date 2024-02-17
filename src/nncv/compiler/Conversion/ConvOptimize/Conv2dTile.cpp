// check https://discourse.llvm.org/t/vectorization-of-convolution-op/60458/7 as a reference
#include "nncv/compiler/Conversion/ConvOptimize/Conv2dTile.hpp"

#include "llvm/Support/ErrorHandling.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/LinalgInterfaces.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/SCF/Transforms/TileUsingInterface.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/IR/Operation.h"
#include "mlir/Support/LogicalResult.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_CONV2DTILE
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

int64_t get2sPowOrSelf(int64_t i) {
  // set candidates
  int64_t candidates[] = {8, 16, 32, 64};

  // try
  if (i < 8) return i;

  int64_t ret = i;
  for (size_t idx = 0; idx < 4; idx++) {
    if (i != candidates[idx] && i >= 2 * candidates[idx]) { ret = candidates[idx]; }
  }
  return ret;
}

bool isDynamic(const std::vector<int64_t>& shape) {
  for (auto item : shape) {
    if (item < 0) return true;
  }
  return false;
}

SmallVector<SmallVector<int64_t>> solveTileSizesConv2d(mlir::Operation* op) {
  SmallVector<SmallVector<int64_t>> res;
  auto _op = mlir::cast<mlir::linalg::LinalgOp>(op);
  if (mlir::isa<mlir::linalg::Conv2DNchwFchwOp>(_op)) {
    auto input = op->getOperand(0);
    auto filter = op->getOperand(1);
    auto output = op->getOperand(2);

    auto inputShape = mlir::cast<mlir::TensorType>(input.getType()).getShape();
    auto filterShape = mlir::cast<mlir::TensorType>(filter.getType()).getShape();
    auto outputShape = mlir::cast<mlir::TensorType>(output.getType()).getShape();

    int64_t N = inputShape[0];
    int64_t outC = outputShape[1];
    int64_t outH = outputShape[2];
    int64_t outW = outputShape[3];
    int64_t inC = inputShape[1];  // Also F
    int64_t kernelH = filterShape[2];
    int64_t kernelW = filterShape[3];

    if (isDynamic({N, outC, outH, outW, inC, kernelH, kernelW})) { return res; }

    // !!! Start solving tiling size. Using some built in logic.
    // For example:
    // %7 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> :
    // vector<2xi64>} ins(%3, %4 : tensor<1x128x30x30xf32>, tensor<128x128x3x3xf32>) outs(%6 :
    // tensor<1x128x28x28xf32>) -> tensor<1x128x28x28xf32>
    //
    // the inputs shape is <1x128x30x30>
    // the kernel shape is <128x128x3x3>
    // the output shape is <1x128x28x28>
    //
    // The recommend tiling size is:
    // 1. [0, 64, 28, 4, 0, 0, 0]
    // 2. [1, 4, 1, 4, 0, 0, 0]
    // 3. [0, 0, 0, 0, 8, 1, 1]
    // 4. [0, 0, 0, 0, 0, 0, 0] (remain)
    SmallVector<int64_t> loops = {N, outC, outH, outW, inC, kernelH, kernelW};
    auto loopsNum = loops.size();

    // solve first level tiling
    {
      res.emplace_back(SmallVector<int64_t>(loopsNum, 0));
      res[0][1] = get2sPowOrSelf(outC);
      res[0][2] = outH;
      res[0][3] = 8;
    }

    // solve second level tiling
    { res.emplace_back(SmallVector<int64_t>{1, 8, 1, 8, 0, 0, 0}); }

    // solve third level tiling
    { res.emplace_back(SmallVector<int64_t>{0, 0, 0, 0, 8, 1, 1}); }

    // solve fourth level tiling
    { res.emplace_back(SmallVector<int64_t>(loopsNum, 0)); }

    return res;
  }

  return res;
}

[[maybe_unused]] llvm::SmallVector<scf::ForOp> toScfForOp(
    llvm::SmallVector<mlir::Operation*, 8>& ops) {
  llvm::SmallVector<scf::ForOp> res;
  for (auto item : ops) res.push_back(mlir::cast<mlir::scf::ForOp>(item));
  return res;
}

FailureOr<mlir::scf::SCFTilingResult> tileAndReplaceConvOp(IRRewriter& rewriter,
                                                           mlir::Operation* op,
                                                           llvm::SmallVector<int64_t> sizes) {
  // process a new sizes;
  auto linalgOp = mlir::cast<mlir::linalg::LinalgOp>(op);
  auto opLoops = linalgOp.getStaticLoopRanges();
  assert(opLoops.size() == sizes.size()
         && "[assert] The size of static loops from linalg op should match tiled sizes' length.\n");

  // do tiling
  scf::SCFTilingOptions tileOption;
  llvm::SmallVector<OpFoldResult> _sizes;
  for (auto idx : sizes) _sizes.push_back(rewriter.getIndexAttr(idx));
  tileOption.setTileSizes(_sizes);

  auto tiledOps = scf::tileUsingSCFForOp(rewriter, dyn_cast<TilingInterface>(op), tileOption);
  rewriter.replaceOp(op, tiledOps->replacements);
  return tiledOps;
}

class Conv2dTilePass : public impl::Conv2dTileBase<Conv2dTilePass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry
        .insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    llvm::SmallVector<mlir::Operation*> candidates;
    IRRewriter rewriter(&getContext());
    getOperation()->walk([&](mlir::linalg::LinalgOp op) {
      if (mlir::isa<mlir::linalg::Conv2DNhwcHwcfOp, mlir::linalg::Conv2DNchwFchwOp,
                    mlir::linalg::Conv2DNhwcFhwcOp>(op)) {
        candidates.emplace_back(op);
      }
    });

    //===----------------------------------------------------------------------===//
    // 1 Tile to Small size.
    //===----------------------------------------------------------------------===//
    for (auto item : candidates) {
      auto op = mlir::cast<mlir::linalg::LinalgOp>(item);

      if (mlir::isa<mlir::linalg::Conv2DNchwFchwOp>(op)) {
        auto tileSizes = solveTileSizesConv2d(op);

        auto tiled = tileAndReplaceConvOp(rewriter, op, tileSizes[0]);
        tiled = tileAndReplaceConvOp(rewriter, tiled->tiledOps[0], tileSizes[1]);
        tiled = tileAndReplaceConvOp(rewriter, tiled->tiledOps[0], tileSizes[2]);
        tiled = tileAndReplaceConvOp(rewriter, tiled->tiledOps[0], tileSizes[3]);
        continue;
      }

      printf("[ Warn ] The data layout of conv2d that nncv supported now is "
             "[Conv2DNhwcHwcfOp/Conv2DNchwFchwOp]. %s "
             " in this file will fail through to nested for loops.\n",
             op->getName().getStringRef().str().c_str());
    }

    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::linalg::populateLinalgTilingCanonicalizationPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createConv2dTilePass() { return std::make_unique<Conv2dTilePass>(); }
}  // namespace mlir::nncv