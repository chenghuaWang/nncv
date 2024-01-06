#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"

void mlir::nncv::createNncvFrontendToNormalPipeline(OpPassManager& pm) {
  pm.addPass(mlir::nncv::createMLProgramBufferizePass());
  return;
}