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

llvm::SmallVector<scf::ForOp> toScfForOp(llvm::SmallVector<mlir::Operation*, 8>& ops) {
  llvm::SmallVector<scf::ForOp> res;
  for (auto item : ops) res.emplace_back(mlir::cast<mlir::scf::ForOp>(item));
  return res;
}

FailureOr<linalg::TiledLinalgOp> tileAndReplaceConvOp(IRRewriter& rewriter, mlir::Operation* op,
                                                      llvm::SmallVector<int64_t> sizes) {
  // process a new sizes;
  auto linalgOp = mlir::cast<mlir::linalg::LinalgOp>(op);
  auto opLoops = linalgOp.getStaticLoopRanges();
  assert(opLoops.size() == sizes.size()
         && "[assert] The size of static loops from linalg op should match tiled sizes' length.\n");
  for (size_t i = 0; i < sizes.size(); ++i) {
    auto cur = opLoops[i];
    auto want = sizes[i];
    if (cur <= want) sizes[i] = 0;
  }

  // do tiling
  linalg::LinalgTilingOptions tileOption;
  tileOption.setTileSizes(sizes);

  OpBuilder::InsertionGuard guard(rewriter);
  rewriter.setInsertionPoint(op);

  auto tiledOps =
      linalg::tileLinalgOp(rewriter, mlir::cast<mlir::linalg::LinalgOp>(op), tileOption);
  rewriter.replaceOp(op, tiledOps->tensorResults);
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

    // tile to one dims;
    for (auto item : candidates) {
      auto op = mlir::cast<mlir::linalg::LinalgOp>(item);

      if (mlir::isa<mlir::linalg::Conv2DNhwcHwcfOp>(op)) {
        auto tiled = tileAndReplaceConvOp(
            rewriter, op,
            {/*batch*/ 0, /*outputH*/ 1, /*outputW*/ 8, /*kernelC*/ 8, /*kernelH*/ 1,
             /*kernelW*/ 0, /*kernelF*/ 0});
        if (succeeded(tiled)) {
          mlir::linalg::peelLoops(rewriter, toScfForOp(tiled->loops));
          continue;
        }
      }

      if (mlir::isa<mlir::linalg::Conv2DNchwFchwOp>(op)) {
        auto tiled = tileAndReplaceConvOp(
            rewriter, op,
            {/*batch*/ 0, /*kernelC*/ 8, /*outputH*/ 1, /*outputW*/ 8, /*kernelF*/ 0,
             /*kernelH*/ 1, /*kernelW*/ 0});
        if (succeeded(tiled)) {
          mlir::linalg::peelLoops(rewriter, toScfForOp(tiled->loops));
          continue;
        }
      }

      printf("[ Warn ] The data layout of conv that nncv supported now is [nchwfchw/nhwchwcf]. %s "
             " in this file will fail through to nested for loops.\n",
             op->getName().getStringRef().str().c_str());
    }

    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::linalg::populateDecomposeConvolutionPatterns(patterns);
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