/**
 * @file DnnModelLowering.cpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief Lowering DNN Model to NNVM or LLVM
 * @version 0.1
 * @date 2024-01-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "nncv/compiler/Pipeline/DnnModelLowering.hpp"

#include "mlir/Transforms/Passes.h"
#include "mlir/Dialect/Bufferization/Transforms/OneShotAnalysis.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/GPU/Transforms/Passes.h"
#include "mlir/Dialect/Linalg/Passes.h"
#include "mlir/Dialect/MemRef/Transforms/Passes.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"

#include "mlir/Conversion/SCFToGPU/SCFToGPUPass.h"
#include "mlir/Conversion/SCFToControlFlow/SCFToControlFlow.h"
#include "mlir/Conversion/AffineToStandard/AffineToStandard.h"
#include "mlir/Conversion/BufferizationToMemRef/BufferizationToMemRef.h"
#include "mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/Conversion/NVVMToLLVM/NVVMToLLVM.h"
#include "mlir/Conversion/FuncToLLVM/ConvertFuncToLLVMPass.h"

// FIXME
#include "nncv/compiler/Conversion/ConvOptimize/OptimizeConv2dUsingWinograd.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptDefault.hpp"
#include "nncv/compiler/Dialects/LinalgExt/Transforms/Passes.hpp"

#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"

namespace nncv {
namespace pipeline {
//===----------------------------------------------------------------------===//
// To NVIDIA GPU Pipeline
//===----------------------------------------------------------------------===//
// -pass-pipeline=\"builtin.module(func.func(canonicalize,cse),
// one-shot-bufferize{bufferize-function-boundaries}, buffer-deallocation-pipeline,
// convert-bufferization-to-memref, func.func(lower-affine, convert-linalg-to-parallel-loops),
// func.func(canonicalize), func.func(convert-scf-to-cf), expand-strided-metadata,
// func.func(gpu-map-parallel-loops), convert-parallel-loops-to-gpu, gpu-kernel-outlining,
// lower-affine, convert-arith-to-llvm, finalize-memref-to-llvm, convert-nvvm-to-llvm,
// convert-func-to-llvm, reconcile-unrealized-casts)\"
//===----------------------------------------------------------------------===//
// To Normal CPU without any parallel Pipeline
//===----------------------------------------------------------------------===//
// -pass-pipeline=\"builtin.module(func.func(canonicalize,cse),
// one-shot-bufferize{bufferize-function-boundaries},
// buffer-deallocation-pipeline,convert-bufferization-to-memref,func.func(convert-vector-to-scf,lower-affine,
// convert-linalg-to-loops), func.func(canonicalize, convert-scf-to-cf), convert-vector-to-llvm,
// expand-strided-metadata, lower-affine,convert-arith-to-llvm, finalize-memref-to-llvm,
// convert-func-to-llvm, reconcile-unrealized-casts)
//===----------------------------------------------------------------------===//
// To Normal CPU with AVX and pthread Pipeline
//===----------------------------------------------------------------------===//
// TODO
//===----------------------------------------------------------------------===//
void DnnModelLowering::registerAllPass() {
  if (m_GenNVPTX) {
    mlir::nncv::createNncvFrontendToNormalPipeline(*m_PM);

    // Level 1.1(Top). Canonicalize and CSE
    m_PM->addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
    m_PM->addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());

    // Level 1.2. Bufferize all.
    auto oneShotOption = mlir::bufferization::OneShotBufferizationOptions();
    oneShotOption.bufferizeFunctionBoundaries = true;
    m_PM->addPass(mlir::bufferization::createOneShotBufferizePass(oneShotOption));
    m_PM->addPass(mlir::bufferization::createBufferDeallocationPass());
    m_PM->addPass(mlir::createBufferizationToMemRefPass());

    // Level 1.3 lower affine and linalg to parallel
    m_PM->addNestedPass<mlir::func::FuncOp>(mlir::createLowerAffinePass());
    m_PM->addNestedPass<mlir::func::FuncOp>(mlir::createConvertLinalgToParallelLoopsPass());
    m_PM->addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
    m_PM->addNestedPass<mlir::func::FuncOp>(mlir::createConvertSCFToCFPass());

    m_PM->addPass(mlir::memref::createExpandStridedMetadataPass());

    // Level 2. GPU Lowering
    m_PM->addNestedPass<mlir::func::FuncOp>(mlir::createGpuMapParallelLoopsPass());
    m_PM->addPass(mlir::createParallelLoopToGpuPass());
    m_PM->addPass(mlir::createGpuKernelOutliningPass());
    m_PM->addNestedPass<mlir::func::FuncOp>(mlir::createLowerAffinePass());

    // Level 3. All to LLVM

    return;
  }
  if (m_GenHostWoParallel) {
    mlir::nncv::createNncvFrontendToNormalPipeline(*m_PM);
    return;
  }
  if (m_GenHostWParallel) {
    mlir::nncv::createNncvFrontendToNormalPipeline(*m_PM);

    // TODO
    // the sequence of a pm is not in order?

    // using winograd
    // FIXME
    m_PM->addPass(mlir::nncv::createOptimizeConv2dUsingWinogradPass());

    // Tiling anf Decompose on winograd should followed by a cse.
    m_PM->addNestedPass<mlir::func::FuncOp>(
        mlir::nncv::linalg_ext::createTileAndDecomposeWinogradTransformPass());

    m_PM->addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationDefaultPass());

    return;
  }
}

}  // namespace pipeline
}  // namespace nncv