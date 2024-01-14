#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/Passes.h"
#include "mlir/Dialect/MemRef/Transforms/Passes.h"
#include "mlir/Transforms/Passes.h"

void mlir::nncv::createNncvFrontendToNormalPipeline(OpPassManager& pm) {
  // Erease all ml_program.global
  pm.addPass(mlir::nncv::createMLProgramBufferizePass());

  // detach named ops
  pm.addPass(mlir::nncv::createDetachElementwiseFromNamedOpsPass());

  // Conv2d1x1 to MatMul
  pm.addPass(mlir::nncv::createConvertConv2D1x1ToMatmulPass());

  // Padding for MatMul and BatchMatMul.
  // pm.addPass(mlir::nncv::createPadLinalgOpsToIntegerMultiplePass());

  // Linalg name op conversion
  pm.addPass(mlir::createLinalgNamedOpConversionPass());

  // Canonicalization and CSE
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());

  // element wise to linalg pass
  pm.addPass(mlir::createConvertElementwiseToLinalgPass());

  // eliminate for loop with length=1
  pm.addPass(mlir::createLinalgFoldUnitExtentDimsPass());

  // change the reduction loop to the out most loop.
  pm.addPass(mlir::nncv::createInterchangeGenericOpsPass());
  pm.addPass(mlir::memref::createResolveShapedTypeResultDimsPass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());

  // fusion of tensor ops
  pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createFusionTensorOpsPass());

  // 0-D to Normal
  pm.addNestedPass<mlir::func::FuncOp>(mlir::createLinalgDetensorizePass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
  pm.addPass(mlir::nncv::createInterchangeGenericOpsPass());

  // interchange transpose generic op.
  pm.addPass(mlir::nncv::createInterchangeTransposeGenericOpsPass());

  return;
}