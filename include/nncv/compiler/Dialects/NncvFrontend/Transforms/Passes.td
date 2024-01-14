#ifndef NNCV_NNCV_FRONTEND_PASSES
#define NNCV_NNCV_FRONTEND_PASSES

include "mlir/Pass/PassBase.td"

//===----------------------------------------------------------------------===//
// Remove all Global Ops by ml_program.
//===----------------------------------------------------------------------===//
def MLProgramBufferize: Pass<"nncv-frontend-mlprogram-bufferize", "ModuleOp"> {
  let summary = "Bufferize the MLProgram dialect ops";
  let constructor = "mlir::nncv::createMLProgramBufferizePass();";
  let dependentDialects = ["memref::MemRefDialect"];

  let description = [{

  }];
}

//===----------------------------------------------------------------------===//
// Conv2d 1x1 optimized to Mat Mul.
//===----------------------------------------------------------------------===//
def ConvertConv2D1x1ToMatmul : Pass<"nncv-frontend-convert-conv2d1x1-to-matmul", ""> {
  let summary = "Convert 1x1 Conv2D to mat mul";
  let constructor = "mlir::nncv::createConvertConv2D1x1ToMatmulPass()";

  let description = [{
    2d convolution with 1x1 kernel can be simplified to matrix mult.
  }];
}

//===----------------------------------------------------------------------===//
// Conv2d Optimize to (Image to column).
//===----------------------------------------------------------------------===//
def ConvertConv2DToImg2Col : Pass<"nncv-frontend-convert-conv2d-to-img2col", ""> {
  let summary = "Convert linalg convolution ops to matmul img2col based implementation";
  let constructor = "mlir::nncv::createConvertConv2DToImg2ColPass()";

  let description = [{
    Usign Image to column algorithm to accelerate convolution.
  }];
}

//===----------------------------------------------------------------------===//
// Padding Linalg Ops to pad-size=4(default)
//===----------------------------------------------------------------------===//
def PadLinalgOps :
    Pass<"nncv-frontend-pad-linalg-ops", ""> {
  let summary = "Pad linalg ops to the next integer multiple of paddingSize.";
  let constructor = "mlir::nncv::createPadLinalgOpsToIntegerMultiplePass()";
  let options = [
    Option<"paddingSize", "pad-size", "int", /*default=*/"4", "Specify the padding size">,
  ];
}

//===----------------------------------------------------------------------===//
// Interchange linalg.generic Ops
//===----------------------------------------------------------------------===//
def InterchangeGenericOps : Pass<"nncv-frontend-interchange-generic-ops", ""> {
  let summary = "Interchange generic op loops to have all the reduction loops to be inner loops.";
  let constructor = "mlir::nncv::createInterchangeGenericOpsPass()";
}

//===----------------------------------------------------------------------===//
// fusion tensors Ops: element wise most
//===----------------------------------------------------------------------===//
def FusionTensorOps :
    InterfacePass<"nncv-aten-fusion-tensor-ops", "mlir::FunctionOpInterface"> {
  let summary = "Fuse operations on tensors";
  let constructor = "mlir::nncv::createFusionOfTensorOpsPass()";
  let options = [
    Option<"fuseMultiUse", "fuse-multi-use", "bool",
           /*default=*/"false", "Fuse ops with multiuse">,
    Option<"multiUseFusionIteration", "multi-use-fusion-iteration", "unsigned",
           /*default=*/"2", "Number of iterations to fuse multiuse ops">
  ];
}

#endif // NNCV_NNCV_FRONTEND_PASSES