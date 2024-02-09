#ifndef NNCV_COMPILER_NNCV_ATEN_TRANSFORMS_PASS_HPP_
#define NNCV_COMPILER_NNCV_ATEN_TRANSFORMS_PASS_HPP_

#include "mlir/Pass/Pass.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/PassManager.h"

namespace mlir {
class ModuleOp;

namespace nncv::aten {
std::unique_ptr<mlir::Pass> createEliminateTailReturnLoadPass();

std::unique_ptr<mlir::Pass> createEliminateRedundantLoadStoreForScfConditionalPass();

std::unique_ptr<mlir::Pass> createRaiseMemerefLSInAffineToAffineLSPass();

void createAtenLangHighLevelOptimizePipeline(OpPassManager& pm);

#define GEN_PASS_REGISTRATION
#include "AutoTen/Transforms/Passes.h.inc"

}  // namespace nncv::aten
}  // namespace mlir

#endif  //! NNCV_COMPILER_NNCV_ATEN_TRANSFORMS_PASS_HPP_