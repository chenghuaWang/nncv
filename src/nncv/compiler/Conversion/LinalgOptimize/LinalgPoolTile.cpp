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

    for (auto item : candidates) {
      auto op = mlir::cast<mlir::linalg::LinalgOp>(item);

      // if this op can't be vectorized. No need to tile anymore.
      if (linalg::vectorizeOpPrecondition(op).failed()) continue;

      // get the number of loops in the first level
      auto numLoops = op.getNumLoops();
    }
  }
};
}  // namespace

std::unique_ptr<mlir::Pass> createLinalgPoolingTilePass(bool flag) {
  return std::make_unique<LinalgPoolingTilePass>();
}

}  // namespace nncv
}  // namespace mlir