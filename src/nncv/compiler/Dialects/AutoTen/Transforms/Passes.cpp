#include "nncv/compiler/Dialects/AutoTen/Transforms/Passes.hpp"
#include "mlir/Transforms/Passes.h"

void mlir::nncv::aten::createAtenLangHighLevelOptimizePipeline(OpPassManager& pm) {
  pm.addPass(mlir::createCSEPass());
  pm.addPass(mlir::nncv::aten::createEliminateTailReturnLoadPass());
  return;
}