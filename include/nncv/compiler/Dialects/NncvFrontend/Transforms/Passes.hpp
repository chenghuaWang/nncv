#ifndef NNCV_COMPILER_NNCV_FRONTEND_PASS_HPP_
#define NNCV_COMPILER_NNCV_FRONTEND_PASS_HPP_

#include "mlir/Pass/Pass.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/PassManager.h"

namespace mlir {
class ModuleOp;

namespace nncv {
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createMLProgramBufferizePass();

std::unique_ptr<mlir::Pass> createConvertConv2D1x1ToMatmulPass();

std::unique_ptr<mlir::Pass> createConvertConv2DToImg2ColPass();

std::unique_ptr<mlir::Pass> createPadLinalgOpsToIntegerMultiplePass();

void createNncvFrontendToNormalPipeline(OpPassManager& pm);

#define GEN_PASS_REGISTRATION
#include "NncvFrontend/Transforms/Passes.h.inc"

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_COMPILER_NNCV_FRONTEND_PASS_HPP_
