#include "nncv/compiler/Dialects/NncvFrontend/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"

namespace mlir::nncv {
namespace {

class InterchangeTransposeGenericOpsPass
    : public InterchangeTransposeGenericOpsBase<InterchangeTransposeGenericOpsPass> {
 public:
  void getDependentDialects(DialectRegistry& registry) const override {
    registry.insert<arith::ArithDialect, linalg::LinalgDialect, tensor::TensorDialect>();
  }

  void runOnOperation() override { RewritePatternSet patterns(&getContext()); }
};

}  // namespace
std::unique_ptr<mlir::Pass> createInterchangeTransposeGenericOpsPass() {
  return std::make_unique<InterchangeTransposeGenericOpsPass>();
}
}  // namespace mlir::nncv