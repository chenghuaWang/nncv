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

def ConvertAtenMlirToLlvm : Pass<"convert-aten-mlir-to-llvm"> {
    let summary = "Convert aten's mlir to llvm ir";
    let description = [{
        Convert all ops to llvm ir.
    }];
    let constructor = "mlir::nncv::createConvertAtenMlirToLlvmPass()";
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

def Conv2dTile : Pass <"conv2d-tile", "func::FuncOp"> {
    let summary = "tile conv2d to conv1d";
    let constructor = "mlir::nncv::createConv2dTilePass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

//===----------------------------------------------------------------------===//
// MatMul optimization
//===----------------------------------------------------------------------===//
def MatMulOptimization_Default : Pass<"optimize-matmul-default-method", "ModuleOp"> {
    let summary = "optimizing all mat mul operation using vectorization.(default)";
    let constructor = "mlir::nncv::matmul_optimize::createMatMulOptimizationDefaultPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

def MatMulOptimization_Vec : Pass<"optimize-matmul-vec-method", "ModuleOp"> {
    let summary = "optimizing all mat mul operation using vectorization.(specific)";
    let constructor = "mlir::nncv::matmul_optimize::createMatMulOptimizationVecPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

def MatMulOptimization_ParallelVec : Pass<"optimize-matmul-parallel-vec-method", "ModuleOp"> {
    let summary = "optimizing all mat mul operation using parallel vectorization.";
    let constructor = "mlir::nncv::matmul_optimize::createMatMulOptimizationParallelVecPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

def MatMulOptimization_ForBatch : Pass<"optimize-batch-matmul-vec-method", "ModuleOp"> {
    let summary = "optimizing all Batch mat mul operation using vectorization.";
    let constructor = "mlir::nncv::matmul_optimize::createMatMulOptimizationForBatchPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

def MatMulOptimization_NvMMA : Pass<"optimize-matmul-to-nv-mma", "func::FuncOp"> {
    let summary = "optimizing all mat mul operation using gpu.subgroup_mma.";
    let constructor = "mlir::nncv::matmul_optimize::createMatMulOptimizationNvMMA()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

//===----------------------------------------------------------------------===//
// Linalg Generic Tile
//===----------------------------------------------------------------------===//
def LinalgGenericTile : Pass<"linalg-generic-tile", "func::FuncOp"> {
    let summary = "prepare linalg generic tiling for vectorization";
    let constructor = "mlir::nncv::createLinalgGenericTilePass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

//===----------------------------------------------------------------------===//
// Linalg Generic Tile
//===----------------------------------------------------------------------===//
def LinalgPoolingTile : Pass<"linalg-pooling-tile", "func::FuncOp"> {
    let summary = "prepare linalg pooling tiling for vectorization";
    let constructor = "mlir::nncv::createLinalgPoolingTilePass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

//===----------------------------------------------------------------------===//
// Linalg Op: Cast Away tensor leading one dim
//===----------------------------------------------------------------------===//
def LinalgOpCastAwayTensorLeadingOneDim : Pass<"linalg-cast-away-tensor-leading-one-dim", "func::FuncOp"> {
    let summary = "cast away tensor leading one dim";
    let constructor = "mlir::nncv::createLinalgOpCastAwayTensorLeadingOneDimPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

//===----------------------------------------------------------------------===//
// Vectorization All
// FIXME: modify func::FuncOp after impl outline in nncv.
//===----------------------------------------------------------------------===//
def Vectorization : Pass<"vectorization", "func::FuncOp"> {
    let summary = "vectorization after all tiling";
    let constructor = "mlir::nncv::createVectorizationPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

//===----------------------------------------------------------------------===//
// Register All linalg Ops that can be tiled and vectorized.
//===----------------------------------------------------------------------===//
def RegisterLinalgOps : Pass<"register-linalg-ops", "func::FuncOp"> {
    let summary = "register all linalg ops to generate a .json config file for tiling and vectorization.";
    let constructor = "mlir::nncv::createRegisterLinalgOpsPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

//===----------------------------------------------------------------------===//
// One shot Vectorization.
//===----------------------------------------------------------------------===//
def OneShotTiling : Pass<"oneshot-tiling", "func::FuncOp"> {
    let summary = "One shot tiling.";
    let constructor = "mlir::nncv::createOneShotTilingPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect"
    ];
}

//===----------------------------------------------------------------------===//
// Decompose All
//===----------------------------------------------------------------------===//
def DecomposeTransformGen : Pass<"gen-decompose-transform", "func::FuncOp"> {
    let summary = "decompose all";
    let constructor = "mlir::nncv::createDcomposeTransformGenPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect",
        "transform::TransformDialect",
    ];
}

//===----------------------------------------------------------------------===//
// nested transform erase pass
//===----------------------------------------------------------------------===//
def NestedTransformErase : Pass<"erase-nested-transform-scope", "mlir::ModuleOp"> {
    let summary = "erase all nested transform scopes";
    let constructor = "mlir::nncv::createNestedTransformErasePass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "affine::AffineDialect",
        "math::MathDialect",
        "tensor::TensorDialect",
        "linalg::LinalgDialect",
        "transform::TransformDialect",
    ];
}

#endif //! ATEN_CONVERSION_PASSES