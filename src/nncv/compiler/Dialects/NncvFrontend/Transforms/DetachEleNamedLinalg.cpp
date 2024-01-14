#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"

namespace mlir::nncv {
namespace {

class DetachElementwiseFromNamedOpsPass
    : public DetachElementwiseFromNamedOpsBase<DetachElementwiseFromNamedOpsPass> {
 public:
  void getDependentDialects(DialectRegistry& registry) const override {
    registry.insert<arith::ArithDialect, linalg::LinalgDialect, tensor::TensorDialect>();
  }

  void runOnOperation() override { RewritePatternSet patterns(&getContext()); }
};

}  // namespace
std::unique_ptr<mlir::Pass> createDetachElementwiseFromNamedOpsPass() {
  return std::make_unique<DetachElementwiseFromNamedOpsPass>();
}
}  // namespace mlir::nncv