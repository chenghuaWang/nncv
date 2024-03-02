#ifndef NNCV_COMPILER_NNCV_FRONTEND_PASS_HPP_
#define NNCV_COMPILER_NNCV_FRONTEND_PASS_HPP_

#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/PassManager.h"

#define P_LINALG_MAX_CONSTANT_FOLD_ELEMENTS 16

namespace mlir {
class ModuleOp;

namespace nncv {
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createMLProgramBufferizePass();

std::unique_ptr<mlir::Pass> createConvertConv2D1x1ToMatmulPass();

std::unique_ptr<mlir::Pass> createConvertConv2DToImg2ColPass();

std::unique_ptr<mlir::Pass> createPadLinalgOpsToIntegerMultiplePass();

std::unique_ptr<mlir::Pass> createInterchangeGenericOpsPass();

std::unique_ptr<InterfacePass<FunctionOpInterface>> createFusionTensorOpsPass(
    bool fuseMultiUse = false, unsigned multiUseFusionIteration = 2);

std::unique_ptr<mlir::Pass> createDetachElementwiseFromNamedOpsPass();

std::unique_ptr<mlir::Pass> createInterchangeTransposeGenericOpsPass();

void createNncvFrontendToNormalPipeline(OpPassManager& pm, bool enableImg2Col = false,
                                        bool enablePaddingMatMul = false);

#define GEN_PASS_REGISTRATION
#include "NncvFrontend/Transforms/Passes.h.inc"

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_COMPILER_NNCV_FRONTEND_PASS_HPP_
