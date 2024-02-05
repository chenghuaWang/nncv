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

struct LinalgPoolingOptions {
  int64_t kernelH;
  int64_t kernelW;
  int64_t outputC;
  int64_t outputH;
  int64_t outputW;
  int64_t batch;
  llvm::SmallVector<int64_t> loops;
  llvm::SmallVector<int64_t> tileSizes;
};

LinalgPoolingOptions getLinalgPoolingOptions(mlir::Operation* op) {
  if (mlir::isa<mlir::linalg::PoolingNhwcMaxOp, mlir::linalg::PoolingNhwcMinOp,
                mlir::linalg::PoolingNhwcSumOp, mlir::linalg::PoolingNhwcMaxUnsignedOp,
                mlir::linalg::PoolingNhwcMinUnsignedOp>(op)) {
    LinalgPoolingOptions res;
    res.loops = mlir::cast<mlir::linalg::LinalgOp>(op).getStaticLoopRanges();
    assert(res.loops.size() == 6 && "[assert] linalg.pooling* should have 6 loops\n");
    res.batch = res.loops[0];
    res.outputH = res.loops[1];
    res.outputW = res.loops[2];
    res.kernelH = res.loops[3];
    res.kernelW = res.loops[4];
    res.outputC = res.loops[5];
    res.tileSizes = {0, 0, 0, 0, 0, 0};
    return res;
  } else if (mlir::isa<mlir::linalg::PoolingNchwMaxOp, mlir::linalg::PoolingNchwSumOp>(op)) {
    LinalgPoolingOptions res;
    res.loops = mlir::cast<mlir::linalg::LinalgOp>(op).getStaticLoopRanges();
    assert(res.loops.size() == 6 && "[assert] linalg.pooling* should have 6 loops\n");
    res.batch = res.loops[0];
    res.outputC = res.loops[1];
    res.outputH = res.loops[2];
    res.outputW = res.loops[3];
    res.kernelH = res.loops[4];
    res.kernelW = res.loops[5];
    res.tileSizes = {0, 0, 0, 0, 0, 0};
    return res;
  }
  return LinalgPoolingOptions();
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

      // if this op can't be vectorized. No need to tile anymore.
      if (linalg::vectorizeOpPrecondition(op).failed()) continue;

      // get the number of loops in the first level
      auto res = getLinalgPoolingOptions(op);
      linalg::LinalgTilingOptions tileOption;
      tileOption.setTileSizes(res.tileSizes);

      OpBuilder::InsertionGuard guard(rewriter);
      rewriter.setInsertionPoint(op);
      auto tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
      rewriter.replaceOp(op, tiledOps->tensorResults);
    }
  }
};
}  // namespace

std::unique_ptr<mlir::Pass> createLinalgPoolingTilePass(bool flag) {
  return std::make_unique<LinalgPoolingTilePass>();
}

}  // namespace nncv
}  // namespace mlir