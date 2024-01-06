#ifndef NNCV_COMPILER_NNCV_FRONTEND_PASS_HPP_
#define NNCV_COMPILER_NNCV_FRONTEND_PASS_HPP_

#include "mlir/Pass/Pass.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/PassManager.h"

namespace mlir {
class ModuleOp;

namespace nncv {
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createMLProgramBufferizePass();

void createNncvFrontendToNormalPipeline(OpPassManager& pm);

#define GEN_PASS_REGISTRATION
#include "NncvFrontend/Transforms/Passes.h.inc"

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_COMPILER_NNCV_FRONTEND_PASS_HPP_
