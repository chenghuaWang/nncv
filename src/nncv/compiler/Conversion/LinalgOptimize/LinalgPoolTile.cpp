#include "nncv/compiler/Conversion/LinalgOptimize/LinalgPoolTile.hpp"
#include "mlir/Dialect/SCF/Transforms/TileUsingInterface.h"
#include "mlir/Dialect/SCF/Transforms/Transforms.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "nncv/compiler/Utils/PlatformCtx.hpp"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/LinalgInterfaces.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_LINALGPOOLINGTILE
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {

namespace {

llvm::SmallVector<scf::ForOp> toScfForOp(llvm::SmallVector<mlir::Operation*>& ops) {
  llvm::SmallVector<scf::ForOp> res;
  for (auto item : ops) res.emplace_back(mlir::cast<mlir::scf::ForOp>(item));
  return res;
}

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

SmallVector<SmallVector<int64_t>> solveTileSizesPooling(mlir::Operation* op) {
  SmallVector<SmallVector<int64_t>> res;
  auto _op = mlir::cast<mlir::linalg::LinalgOp>(op);
  if (mlir::isa<mlir::linalg::PoolingNchwMaxOp, mlir::linalg::PoolingNchwSumOp>(_op)) {
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
    int64_t kernelH = filterShape[0];
    int64_t kernelW = filterShape[1];

    if (isDynamic({N, outC, outH, outW, kernelH, kernelW})) { return res; }

    // !!! Start solving tiling size. Using some built in logic.
    // For example:
    // %3 = linalg.pooling_nchw_max {dilations = dense<1> : vector<2xi64>, strides = dense<2> :
    // vector<2xi64>} ins(%arg0, %2 : tensor<1x64x114x114xf32>, tensor<3x3xf32>) outs(%1 :
    // tensor<1x64x56x56xf32>) -> tensor<1x64x56x56xf32>
    //
    // the inputs shape is <1x64x114x114>
    // the kernel shape is <3x3>
    // the output shape is <1x64x56x56>
    //
    // The recommend tiling size is:
    // 1. [0, 32, 56, 8, 0, 0]
    // 2. [1, 8, 1, 8, 0, 0]
    // 3. [0, 0, 0, 0, 1, 3]
    // 4. [0, 0, 0, 0, 0, 0] (remain)
    SmallVector<int64_t> loops = {N, outC, outH, outW, kernelH, kernelW};
    auto loopsNum = loops.size();

    // solve first level tiling
    {
      res.emplace_back(SmallVector<int64_t>(loopsNum, 0));
      res[0][1] = get2sPowOrSelf(outC);
      res[0][2] = outH;
      res[0][3] = 8;
    }

    // solve second level tiling
    { res.emplace_back(SmallVector<int64_t>{1, 8, 1, 8, 0, 0}); }

    // solve third level tiling
    { res.emplace_back(SmallVector<int64_t>{0, 0, 0, 0, 1, kernelW}); }

    // solve fourth level tiling
    { res.emplace_back(SmallVector<int64_t>(loopsNum, 0)); }

    return res;
  }

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

class LinalgPoolingTilePass : public impl::LinalgPoolingTileBase<LinalgPoolingTilePass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry
        .insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    llvm::SmallVector<mlir::Operation*> candidates;
    getOperation().walk([&](mlir::linalg::LinalgOp op) {
      // check if pooling and insert to candidates;
      if (mlir::isa<mlir::linalg::PoolingNhwcMaxOp, mlir::linalg::PoolingNhwcMinOp,
                    mlir::linalg::PoolingNhwcSumOp, mlir::linalg::PoolingNhwcMaxUnsignedOp,
                    mlir::linalg::PoolingNhwcMinUnsignedOp, mlir::linalg::PoolingNchwMaxOp,
                    mlir::linalg::PoolingNchwSumOp>(op)) {
        if (op.hasBufferSemantics()) return signalPassFailure();
        candidates.emplace_back(op);
      }
    });

    IRRewriter rewriter(&getContext());

    for (auto item : candidates) {
      auto op = mlir::cast<mlir::linalg::LinalgOp>(item);

      if (mlir::isa<mlir::linalg::PoolingNchwMaxOp, mlir::linalg::PoolingNchwSumOp>(op)) {
        auto tileSizes = solveTileSizesPooling(op);

        auto tiled = tileAndReplaceConvOp(rewriter, op, tileSizes[0]);
        tiled = tileAndReplaceConvOp(rewriter, tiled->tiledOps[0], tileSizes[1]);
        tiled = tileAndReplaceConvOp(rewriter, tiled->tiledOps[0], tileSizes[2]);
        tiled = tileAndReplaceConvOp(rewriter, tiled->tiledOps[0], tileSizes[3]);
        continue;
      }

      printf("[ Warn ] The data layout of pooling that nncv supported now is [nhwc/nchw]. %s "
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

std::unique_ptr<mlir::Pass> createLinalgPoolingTilePass(bool flag) {
  return std::make_unique<LinalgPoolingTilePass>();
}

}  // namespace nncv
}  // namespace mlir