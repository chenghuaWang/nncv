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

#include "mlir/Dialect/Affine/Passes.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/MLProgram/Transforms/Passes.h"
#include "mlir/Transforms/Passes.h"
#include "mlir/Dialect/Bufferization/Transforms/OneShotAnalysis.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/GPU/Transforms/Passes.h"
#include "mlir/Dialect/Linalg/Passes.h"
#include "mlir/Dialect/MemRef/Transforms/Passes.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Vector/Transforms/Passes.h"

#include "mlir/Conversion/SCFToGPU/SCFToGPUPass.h"
#include "mlir/Conversion/SCFToControlFlow/SCFToControlFlow.h"
#include "mlir/Conversion/AffineToStandard/AffineToStandard.h"
#include "mlir/Conversion/BufferizationToMemRef/BufferizationToMemRef.h"
#include "mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/Conversion/NVVMToLLVM/NVVMToLLVM.h"
#include "mlir/Conversion/FuncToLLVM/ConvertFuncToLLVMPass.h"

// FIXME
#include "nncv/compiler/Conversion/ConvOptimize/OptimizeConv2dUsingWinograd.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/LinalgGenericTile.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptDefault.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptParallelVec.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptVec.hpp"
#include "nncv/compiler/Conversion/Vectorization/Vec.hpp"
#include "nncv/compiler/Dialects/LinalgExt/Transforms/Passes.hpp"

#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"
#include "nncv/compiler/Utils/MlirIo.hpp"

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
void DnnModelLowering::run() {
  mlir::PassManager pm(m_Module.get()->getName());
  if (m_GenNVPTX) {
    mlir::nncv::createNncvFrontendToNormalPipeline(pm);

    // Level 1.1(Top). Canonicalize and CSE
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());

    // Level 1.2. Bufferize all.
    auto oneShotOption = mlir::bufferization::OneShotBufferizationOptions();
    oneShotOption.bufferizeFunctionBoundaries = true;
    pm.addPass(mlir::bufferization::createOneShotBufferizePass(oneShotOption));
    pm.addPass(mlir::bufferization::createBufferDeallocationPass());
    pm.addPass(mlir::createBufferizationToMemRefPass());

    // Level 1.3 lower affine and linalg to parallel
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createLowerAffinePass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createConvertLinalgToParallelLoopsPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createConvertSCFToCFPass());

    pm.addPass(mlir::memref::createExpandStridedMetadataPass());

    // Level 2. GPU Lowering
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createGpuMapParallelLoopsPass());
    pm.addPass(mlir::createParallelLoopToGpuPass());
    pm.addPass(mlir::createGpuKernelOutliningPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createLowerAffinePass());

    // Level 3. All to LLVM

    return;
  }
  if (m_GenHostWoParallel) {
    mlir::nncv::createNncvFrontendToNormalPipeline(pm);
    return;
  }
  if (m_GenHostWParallel) {
    // Stage 1. Finalize all input
    {
      pm.clear();
      mlir::nncv::createNncvFrontendToNormalPipeline(pm);
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] Frontend Normalize Pass Pipeline. Failed\n");
        exit(-1);
      } else {
        printf("[ Info ] Frontend Normalize Pass Pipeline. Success.\n");
      }
    }

    // using winograd
    // FIXME
    // pm.addPass(mlir::nncv::createOptimizeConv2dUsingWinogradPass());
    // pm.addNestedPass<mlir::func::FuncOp>(
    //     mlir::nncv::linalg_ext::createTileAndDecomposeWinogradTransformPass());
    // pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());

    // Stage 2.1 High Level Tile for MatMul
    {
      pm.clear();
      pm.addPass(
          mlir::nncv::matmul_optimize::createMatMulOptimizationVecPass(/*use nv gpu*/ false));
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] High Level Tiling [Matmul]. Failed\n");
        exit(-1);
      } else {
        printf("[ Info ] High Level Tiling [Matmul]. Success.\n");
      }
    }

    // stage 2.2 Tile for Conv2d
    {}

    // Stage 2.3 Tile others
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::createLinalgGenericTilePass(/*use nv gpu*/ false));
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] High Level Tiling [Generic]. Failed\n");
        exit(-1);
      } else {
        printf("[ Info ] High Level Tiling [Generic]. Success.\n");
      }
    }

    // stage 3. Vectorization
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::createVectorizationPass(/*use nv gpu*/ false));
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] Middle Level Vectorization. Failed\n");
        exit(-1);
      } else {
        printf("[ Info ] Middle Level Vectorization. Success.\n");
      }
    }

    // Stage 4. Lowering all left linalg to affine and try to do super affine.
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createConvertLinalgToAffineLoopsPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createAffineLoopInvariantCodeMotionPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createLoopFusionPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createAffineLoopNormalizePass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createAffineVectorize());
      (void)pm.run(*m_Module);
    }

    // Stage final
    // TODO
    {
      pm.clear();
      pm.addPass(mlir::ml_program::createMLProgramPipelineGlobalsPass());
      (void)pm.run(*m_Module);
    }

    if (!m_OutputFilePath.empty()) {
      nncv::compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
    } else {
      m_Module->dump();
    }
    return;
  }
}

}  // namespace pipeline
}  // namespace nncv