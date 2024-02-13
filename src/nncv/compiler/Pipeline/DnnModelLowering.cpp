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
#include "mlir/Conversion/VectorToLLVM/ConvertVectorToLLVMPass.h"
#include "mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/Conversion/VectorToGPU/VectorToGPU.h"

// FIXME
#include "nncv/compiler/Conversion/ConvOptimize/Conv2dTile.hpp"
#include "nncv/compiler/Conversion/ConvOptimize/OptimizeConv2dUsingWinograd.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/CastAwayTensorLeadingOneDim.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/LinalgGenericTile.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/LinalgPoolTile.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/BatchMatMulOptVec.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMul2NvMMA.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptDefault.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptParallelVec.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptVec.hpp"
#include "nncv/compiler/Conversion/Vectorization/Vec.hpp"
#include "nncv/compiler/Dialects/LinalgExt/Transforms/Passes.hpp"

#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"
#include "nncv/compiler/Utils/MlirIo.hpp"

namespace nncv {
namespace pipeline {

void populateOneBufferizationPassPipeline(mlir::PassManager& pm) {
  pm.addPass(mlir::bufferization::createOneShotBufferizePass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
}

void DnnModelLowering::run() {
  mlir::PassManager pm(m_Module.get()->getName());
  if (m_GenNVPTX) {
    //===----------------------------------------------------------------------===//
    // 1 Finalize all input
    //===----------------------------------------------------------------------===//
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

    //===----------------------------------------------------------------------===//
    // 2 Doing some tensor elimination
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::createLinalgOpCastAwayTensorLeadingOneDimPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::bufferization::createEmptyTensorEliminationPass());
      pm.addPass(mlir::createCanonicalizerPass());
      pm.addPass(mlir::createCSEPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] Cast Away Tensor Leading One Dims. Failed\n");
        exit(-1);
      } else {
        printf("[ Info ] Cast Away Tensor Leading One Dims. Success.\n");
      }
      (void)pm.run(*m_Module);
    }

    //===----------------------------------------------------------------------===//
    // 3 Using winograd method before lowering MatMul
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      // winograd or img2col here.
      // pm.addPass(mlir::nncv::createOptimizeConv2dUsingWinogradPass());
      // pm.addNestedPass<mlir::func::FuncOp>(
      //     mlir::nncv::linalg_ext::createTileAndDecomposeWinogradTransformPass());
      // pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      (void)pm.run(*m_Module);
    }

    //===----------------------------------------------------------------------===//
    // 4 Tile MatMul
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationVecPass(/*use nv gpu*/ true));
      pm.addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationForBatchPass());
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::createLinalgOpCastAwayTensorLeadingOneDimPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] High Level Tiling [Matmul]. Failed\n");
        exit(-1);
      } else {
        printf("[ Info ] High Level Tiling [Matmul]. Success.\n");
      }
    }

    // Tile All
    // TODO

    //===----------------------------------------------------------------------===//
    // 7 Vectorization on NVIDIA
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::createVectorizationPass(/*use nv gpu*/ true));
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] Middle Level Vectorization. Failed\n");
        exit(-1);
      } else {
        printf("[ Info ] Middle Level Vectorization. Success.\n");
      }
    }

    if (!m_OutputFilePath.empty()) {
      nncv::compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
    } else {
      m_Module->dump();
    }
    return;
  }
  if (m_GenHostWoParallel) {
    mlir::nncv::createNncvFrontendToNormalPipeline(pm);
    return;
  }
  if (m_GenHostWParallel) {
    //===----------------------------------------------------------------------===//
    // 1 Finalize all input
    //===----------------------------------------------------------------------===//
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

    //===----------------------------------------------------------------------===//
    // 2 Doing some tensor eliminate
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::createLinalgOpCastAwayTensorLeadingOneDimPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::bufferization::createEmptyTensorEliminationPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] Cast Away Tensor Leading One Dims. Failed\n");
        exit(-1);
      } else {
        printf("[ Info ] Cast Away Tensor Leading One Dims. Success.\n");
      }
      (void)pm.run(*m_Module);
    }

    //===----------------------------------------------------------------------===//
    // 3 Using winograd method before lowering MatMul
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      // winograd or img2col here.
      // pm.addPass(mlir::nncv::createOptimizeConv2dUsingWinogradPass());
      // pm.addNestedPass<mlir::func::FuncOp>(
      //     mlir::nncv::linalg_ext::createTileAndDecomposeWinogradTransformPass());
      // pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      (void)pm.run(*m_Module);
    }

    //===----------------------------------------------------------------------===//
    // 4 High level tile for matmul
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addPass(
          mlir::nncv::matmul_optimize::createMatMulOptimizationVecPass(/*use nv gpu*/ false));
      pm.addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationForBatchPass());
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::createLinalgOpCastAwayTensorLeadingOneDimPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] High Level Tiling [Matmul]. Failed\n");
        exit(-1);
      } else {
        printf("[ Info ] High Level Tiling [Matmul]. Success.\n");
      }
    }

    //===----------------------------------------------------------------------===//
    // 5 High level tile for Conv2d/Conv1d/Conv
    // TODO linalg.conv
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createConv2dTilePass());
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::createLinalgPoolingTilePass(/*use nv gpu*/ false));
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] High Level Tiling [Conv/Pool]. Failed\n");
        exit(-1);
      } else {
        printf("[ Info ] High Level Tiling [Conv/Pool]. Success.\n");
      }
    }

    //===----------------------------------------------------------------------===//
    // 6 tile linalg.generic/pad
    //===----------------------------------------------------------------------===//
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

    //===----------------------------------------------------------------------===//
    // 7 Vectorization on X86 with AVX2
    //===----------------------------------------------------------------------===//
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

    //===----------------------------------------------------------------------===//
    // 8 Lowering all remaining linalg to affine and try to do super affine.
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      // pm.addPass(mlir::bufferization::createOneShotBufferizePass());
      // pm.addNestedPass<mlir::func::FuncOp>(mlir::createConvertLinalgToAffineLoopsPass());
      // pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createAffineLoopInvariantCodeMotionPass());
      // pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createLoopFusionPass());
      // pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createAffineLoopNormalizePass());
      // pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createAffineVectorize());

      // TODO
      // mlir::ConvertVectorToLLVMPassOptions option;
      // option.x86Vector = true;
      // pm.addPass(mlir::createConvertVectorToLLVMPass(option));
      // pm.addPass(mlir::createArithToLLVMConversionPass());
      // pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      // pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      (void)pm.run(*m_Module);
    }

    //===----------------------------------------------------------------------===//
    // 9 Lowering all one by one.
    //===----------------------------------------------------------------------===//
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