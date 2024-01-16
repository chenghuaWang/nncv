#ifndef ATEN_CONVERSION_PASSES
#define ATEN_CONVERSION_PASSES

include "mlir/Pass/PassBase.td"

//===----------------------------------------------------------------------===//
// AtenToArith
//===----------------------------------------------------------------------===//
def ConvertAtenToMlir : Pass<"convert-aten-to-mlir"> {
    let summary = "Convert Aten dialect to MLIR owned dialect";
    let description = [{
        Convert all ops to arith, scf, memref and linalg.
    }];
    let constructor = "mlir::nncv::createConvertAtenToMlirPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "aten::AtenDialect",
    ];
}

//===----------------------------------------------------------------------===//
// Convolution optimization
//===----------------------------------------------------------------------===//
def ConvertOptimizedConv2dToAffine : Pass<"convert-optimized-conv2d-to-affine", "ModuleOp"> {
    let summary = "convert optimized linalg-conv2d to affine";
    let description = [{
        using some strategy to determine which algorithms to use.
        The algorithms include:
        - winograd(Only works on 3x3 kernel)
        - CB
        - direct
        - img2col(default=false, and only in NncvFrontend transforms; It only has transforms on linalg, not affine)
    }];
    let constructor = "mlir::nncv::createConvertOptimizedConv2dToAffinePass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect"
    ];
}

def OptimizeConv2dUsingCB : Pass <"optimize-conv2d-CB", "ModuleOp"> {
    let summary = "optimize conv2d using Coefficient Broadcasting algorithm";
    let description = [{
        [High Performance Implementation of 2D Convolution using Intel's Advanced Vector Extensions](https://ieeexplore.ieee.org/abstract/document/8324097)
    }];
    let constructor = "mlir::nncv::createOptimizeConv2dUsingCBPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect"
    ];
}

def OptimizeConv2dUsingWinograd : Pass <"optimize-conv2d-winograd", "ModuleOp"> {
    let summary = "optimize conv2d using winograd algorithm";
    let description = [{
        https://github.com/nod-ai/MLIRWinogradTalk/blob/main/MLIRSummit2022.Nodai.Menon.pdf
    }];
    let constructor = "mlir::nncv::createOptimizeConv2dUsingWinogradPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect"
    ];
}

#endif //! ATEN_CONVERSION_PASSES