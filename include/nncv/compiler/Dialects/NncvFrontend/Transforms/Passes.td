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
    Pass<"iree-preprocessing-pad-linalg-ops", ""> {
  let summary = "Pad linalg ops to the next integer multiple of paddingSize.";
  let constructor = "mlir::nncv::createPadLinalgOpsToIntegerMultiplePass()";
  let options = [
    Option<"paddingSize", "pad-size", "int", /*default=*/"4", "Specify the padding size">,
  ];
}

#endif // NNCV_NNCV_FRONTEND_PASSES