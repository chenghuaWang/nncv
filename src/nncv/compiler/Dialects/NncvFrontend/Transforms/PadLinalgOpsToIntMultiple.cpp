#include "mlir/Dialect/Linalg/IR/Linalg.h"

#include "nncv/compiler/Dialects/NncvFrontend/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"

namespace mlir::nncv {
namespace {
class PadLinalgOpsToIntegerMultiple : public PadLinalgOpsBase<PadLinalgOpsToIntegerMultiple> {
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::linalg::LinalgDialect>();
    return;
  }

  void runOnOperation() override {
    MLIRContext* context = &getContext();
    RewritePatternSet patterns(context);

    return;
  }
};
}  // namespace

std::unique_ptr<mlir::Pass> createPadLinalgOpsToIntegerMultiplePass() {
  return std::make_unique<PadLinalgOpsToIntegerMultiple>();
}

}  // namespace mlir::nncv
