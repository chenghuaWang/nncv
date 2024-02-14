#include "nncv/compiler/Conversion/LinalgOptimize/LinalgPoolTile.hpp"
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

llvm::SmallVector<scf::ForOp> toScfForOp(llvm::SmallVector<mlir::Operation*, 8>& ops) {
  llvm::SmallVector<scf::ForOp> res;
  for (auto item : ops) res.emplace_back(mlir::cast<mlir::scf::ForOp>(item));
  return res;
}

FailureOr<mlir::linalg::TiledLinalgOp> tileAndReplacePoolOp(IRRewriter& rewriter,
                                                            mlir::Operation* op,
                                                            llvm::SmallVector<int64_t> sizes) {
  // process a new sizes;
  auto linalgOp = mlir::cast<mlir::linalg::LinalgOp>(op);
  auto opLoops = linalgOp.getStaticLoopRanges();
  assert(opLoops.size() == sizes.size()
         && "[assert] The size of static loops from linalg op should match tiled sizes' length.");
  for (size_t i = 0; i < sizes.size(); ++i) {
    auto cur = opLoops[i];
    auto want = sizes[i];
    if (cur <= want) sizes[i] = 1;
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

      if (mlir::isa<mlir::linalg::PoolingNhwcMaxOp, mlir::linalg::PoolingNhwcMinOp,
                    mlir::linalg::PoolingNhwcSumOp, mlir::linalg::PoolingNhwcMaxUnsignedOp,
                    mlir::linalg::PoolingNhwcMinUnsignedOp>(op)) {
        auto tiled = tileAndReplacePoolOp(
            rewriter, op,
            {/*batch*/ 0, /*outputH*/ 1, /*outputW*/ 8, /*kernelC*/ 8, /*kernelH*/ 1,
             /*kernelW*/ 0, /*kernelF*/ 0});
        if (succeeded(tiled)) {
          mlir::linalg::peelLoops(rewriter, toScfForOp(tiled->loops));
          continue;
        }
      }

      if (mlir::isa<mlir::linalg::PoolingNchwMaxOp, mlir::linalg::PoolingNchwSumOp>(op)) {
        auto tiled = tileAndReplacePoolOp(
            rewriter, op,
            {/*batch*/ 0, /*kernelC*/ 1, /*outputH*/ 1, /*outputW*/ 32, /*kernelH*/ 1,
             /*kernelW*/ 0});
        if (succeeded(tiled)) {
          mlir::linalg::peelLoops(rewriter, toScfForOp(tiled->loops));
          continue;
        }
      }

      printf("[ Warn ] The data layout of pooling that nncv supported now is [nhwc/nchw]. %s "
             " in this file will fail through to nested for loops.\n",
             op->getName().getStringRef().str().c_str());
    }

    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::linalg::populateLinalgTilingCanonicalizationPatterns(patterns);
      mlir::linalg::populateDecomposeConvolutionPatterns(patterns);
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