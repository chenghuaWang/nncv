#include "nncv/compiler/Dialects/AutoTen/Transforms/Passes.hpp"

void mlir::nncv::aten::createAtenLangHighLevelOptimizePipeline(OpPassManager& pm) {
  pm.addPass(mlir::nncv::aten::createEliminateTailReturnLoadPass());
  return;
}