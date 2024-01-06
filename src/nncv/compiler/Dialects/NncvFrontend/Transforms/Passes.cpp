#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"

void mlir::nncv::createNncvFrontendToNormalPipeline(OpPassManager& pm) {
  // Erease all ml_program.global
  pm.addPass(mlir::nncv::createMLProgramBufferizePass());

  // Conv2d1x1 to MatMul
  pm.addPass(mlir::nncv::createConvertConv2D1x1ToMatmulPass());
  return;
}