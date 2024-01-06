#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"

#include "nncv/compiler/Dialects/NncvFrontend/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"

namespace mlir::nncv {
namespace {

class ConvertConv2DToImg2Col
    : public mlir::nncv::ConvertConv2DToImg2ColBase<ConvertConv2DToImg2Col> {
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::linalg::LinalgDialect, mlir::tensor::TensorDialect>();
    return;
  }

  void runOnOperation() override { return; }
};

}  // namespace

std::unique_ptr<mlir::Pass> createConvertConv2DToImg2ColPass() {
  return std::make_unique<ConvertConv2DToImg2Col>();
}

}  // namespace mlir::nncv
