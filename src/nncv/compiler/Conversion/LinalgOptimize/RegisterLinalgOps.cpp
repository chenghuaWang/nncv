#include "nncv/compiler/Conversion/LinalgOptimize/RegisterLinalgOps.hpp"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "nncv/compiler/Utils/PlatformCtx.hpp"

#include "nncv/compiler/Optimizer/TileSolver.hpp"

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
#define GEN_PASS_DEF_REGISTERLINALGOPS
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class RegisterLinalgOpsPass : public impl::RegisterLinalgOpsBase<RegisterLinalgOpsPass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry
        .insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    getOperation().walk([&](mlir::linalg::LinalgOp op) {
      ::nncv::compiler::optimizer::TileSolver::getInstance().registerOp(
          op->getName().getStringRef().str(), op);
    });
    ::nncv::compiler::optimizer::TileSolver::getInstance().solveTileSize();
    ::nncv::compiler::optimizer::TileSolver::getInstance().solveThreadDispatch();
    ::nncv::compiler::optimizer::TileSolver::getInstance().dump();
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createRegisterLinalgOpsPass() {
  return std::make_unique<RegisterLinalgOpsPass>();
}

}  // namespace mlir::nncv
