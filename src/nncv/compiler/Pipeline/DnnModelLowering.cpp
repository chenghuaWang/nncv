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

#include "mlir/Conversion/MathToLibm/MathToLibm.h"
#include "mlir/Conversion/ReconcileUnrealizedCasts/ReconcileUnrealizedCasts.h"
#include "mlir/Conversion/TensorToLinalg/TensorToLinalgPass.h"
#include "mlir/Conversion/VectorToSCF/VectorToSCF.h"
#include "mlir/Dialect/Affine/Passes.h"
#include "mlir/Dialect/Arith/Transforms/Passes.h"
#include "mlir/Dialect/LLVMIR/Transforms/RequestCWrappers.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/MLProgram/Transforms/Passes.h"
#include "mlir/Dialect/SCF/Transforms/Passes.h"
#include "mlir/Pass/PassManager.h"
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
#include "mlir/Conversion/SCFToOpenMP/SCFToOpenMP.h"
#include "mlir/Conversion/OpenMPToLLVM/ConvertOpenMPToLLVM.h"
#include "mlir/Conversion/AffineToStandard/AffineToStandard.h"
#include "mlir/Conversion/BufferizationToMemRef/BufferizationToMemRef.h"
#include "mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/Conversion/NVVMToLLVM/NVVMToLLVM.h"
#include "mlir/Conversion/FuncToLLVM/ConvertFuncToLLVMPass.h"
#include "mlir/Conversion/VectorToLLVM/ConvertVectorToLLVMPass.h"
#include "mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/Conversion/VectorToGPU/VectorToGPU.h"
#include "mlir/Conversion/MathToLLVM/MathToLLVM.h"
#include "mlir/Conversion/MemRefToLLVM/MemRefToLLVM.h"

#include "nncv/compiler/Conversion/CodeGen/LlvmCpu/LoweringScfForAllToParallel.hpp"
#include "nncv/compiler/Conversion/CodeGen/LlvmCpu/ModernVec.hpp"
#include "nncv/compiler/Conversion/CodeGen/LlvmCpu/PrepareModernVec.hpp"
#include "nncv/compiler/Conversion/CodeGen/LlvmGpu/ModernTileGpu.hpp"
#include "nncv/compiler/Conversion/ConvOptimize/Conv2dTile.hpp"
#include "nncv/compiler/Conversion/ConvOptimize/ConvertOptimizedConv2dToAffine.hpp"
#include "nncv/compiler/Conversion/ConvOptimize/OptimizeConv2dUsingWinograd.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/CastAwayTensorLeadingOneDim.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/DecomposeTransGen.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/LinalgGenericTile.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/LinalgPoolTile.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/OneShotTiling.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/RegisterLinalgOps.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/BatchMatMulOptVec.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMul2NvMMA.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptDefault.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptParallelVec.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptVec.hpp"
#include "nncv/compiler/Conversion/Transforms/NestedTransformErasePass.hpp"
#include "nncv/compiler/Conversion/Vectorization/Vec.hpp"
#include "nncv/compiler/Dialects/LinalgExt/Transforms/Passes.hpp"
#include "nncv/compiler/Conversion/Passes.h"

#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"
#include "nncv/compiler/Utils/MlirIo.hpp"

namespace nncv {
namespace pipeline {

void populateOneBufferizationPassPipeline(mlir::PassManager& pm) {
  // empty tensor
  pm.addPass(mlir::bufferization::createEmptyTensorEliminationPass());
  pm.addPass(mlir::bufferization::createEmptyTensorToAllocTensorPass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());

  // bufferization
  mlir::bufferization::OneShotBufferizationOptions OneShotOptions;
  OneShotOptions.bufferizeFunctionBoundaries = true;
  OneShotOptions.allowReturnAllocsFromLoops = true;
  OneShotOptions.setFunctionBoundaryTypeConversion(
      mlir::bufferization::LayoutMapOption::IdentityLayoutMap);
  pm.addPass(mlir::bufferization::createOneShotBufferizePass(OneShotOptions));

  // optimize bufferization
  pm.addNestedPass<mlir::func::FuncOp>(mlir::bufferization::createBufferHoistingPass());
  pm.addNestedPass<mlir::func::FuncOp>(mlir::bufferization::createBufferLoopHoistingPass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());

  // delocation
  pm.addNestedPass<mlir::func::FuncOp>(mlir::bufferization::createBufferDeallocationPass());
  pm.addPass(mlir::createBufferizationToMemRefPass());
  pm.addNestedPass<mlir::func::FuncOp>(mlir::bufferization::createFinalizingBufferizePass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());

  // // memref result type.
  pm.addPass(mlir::memref::createResolveRankedShapeTypeResultDimsPass());
  pm.addPass(mlir::memref::createResolveShapedTypeResultDimsPass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
}

void populateInputOptimizationPassPipeline(mlir::PassManager& pm, bool enableImg2Col,
                                           bool enablePaddingMatMul) {
  mlir::nncv::createNncvFrontendToNormalPipeline(pm, enableImg2Col, enablePaddingMatMul);
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
  pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createRegisterLinalgOpsPass());
}

void populateTensorOptimizationPassPipeline(mlir::PassManager& pm) {
  pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createLinalgOpCastAwayTensorLeadingOneDimPass());
  pm.addNestedPass<mlir::func::FuncOp>(mlir::bufferization::createEmptyTensorEliminationPass());
}

void populateWinogradOrImg2ColPassPipeline(mlir::PassManager& pm, bool winograd, bool img2col) {
  if (winograd) {
    pm.addPass(mlir::nncv::createOptimizeConv2dUsingWinogradPass());
    pm.addNestedPass<mlir::func::FuncOp>(
        mlir::nncv::linalg_ext::createTileAndDecomposeWinogradTransformPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
    return;
  }
  if (img2col) {
    pm.addPass(mlir::nncv::createConvertConv2DToImg2ColPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
    return;
  }
}

void populateTileAllPassPipeline(mlir::PassManager& pm, bool oneshot, bool lowerConv, bool gpu) {
  if (gpu) {
  } else {
    if (oneshot) {
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createOneShotTilingPass());
      pm.addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationVecPass(/*use nv gpu*/ gpu));
      pm.addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationForBatchPass());
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::createLinalgGenericTilePass(/*use nv gpu*/ gpu));
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      return;
    }
    // matmul
    pm.addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationVecPass(/*use nv gpu*/ gpu));
    pm.addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationForBatchPass());
    pm.addNestedPass<mlir::func::FuncOp>(
        mlir::nncv::createLinalgOpCastAwayTensorLeadingOneDimPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
    // conv2d
    if (lowerConv) {
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createConv2dTilePass());
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::createLinalgPoolingTilePass(/*use nv gpu*/ gpu));
    }
    pm.addNestedPass<mlir::func::FuncOp>(
        mlir::nncv::createLinalgGenericTilePass(/*use nv gpu*/ gpu));
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
  }
}

void populateVectorizationPassPipeline(mlir::PassManager& pm, bool gpu) {
  pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createVectorizationPass(/*use nv gpu*/ gpu));
  pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
  pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
}

void populateConv2dToAffineVecManuallyPassPipeline(mlir::PassManager& pm) {
  // manually lower
  pm.addPass(mlir::nncv::createConvertOptimizedConv2dToAffinePass());

  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
}

void populateAffineToSCFPassPipeline(mlir::PassManager& pm) {
  pm.addPass(mlir::createLowerAffinePass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
}

void populateLoopFusionAndNormalizationPassPipeline(mlir::PassManager& pm) {
  // promote single iter
  pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createAffineLoopNormalizePass(true));

  // fusion
  pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createLoopFusionPass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
}

void runPmWithExit(mlir::PassManager& pm, mlir::OwningOpRef<mlir::ModuleOp>& module,
                   const std::string& str) {
  if (mlir::failed(pm.run(*module))) {
    printf("[ Erro ] %s. Failed\n", str.c_str());
    exit(-1);
  } else {
    printf("[ Info ] %s. Success.\n", str.c_str());
  }
}

void runPmSilent(mlir::PassManager& pm, mlir::OwningOpRef<mlir::ModuleOp>& module) {
  (void)pm.run(*module);
}

void DnnModelLowering::run() {
  mlir::PassManager pm(m_Module.get()->getName());
  if (m_GenNVPTX) {
    //===----------------------------------------------------------------------===//
    // 1 Finalize all input
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addPass(mlir::bufferization::createEmptyTensorToAllocTensorPass());
      populateInputOptimizationPassPipeline(pm, /*img2col*/ false, /*padding*/ false);
      runPmWithExit(pm, m_Module, "Pass Pipeline-1: Frontend Normalization Pass Pipeline");
    }

    //===----------------------------------------------------------------------===//
    // 2 Doing some tensor eliminatation
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateTensorOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Pass Pipeline-2: Cast Away Tensor Leading One Dims");
    }

    //===----------------------------------------------------------------------===//
    // 3 Using winograd method before lowering MatMul
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateWinogradOrImg2ColPassPipeline(pm);
      runPmSilent(pm, m_Module);
    }

    //===----------------------------------------------------------------------===//
    // 4 High level tile And Decompose For GPU !!!
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createModernOneShotTileAllGpuPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createDecomposeTransformGenPass());
      pm.addPass(mlir::createCSEPass());
      runPmWithExit(pm, m_Module, "Pass Pipeline-3: Perform gpu based tiling and map");
    }

    //===----------------------------------------------------------------------===//
    // 5. Prepare vec For GPU !!!
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createPrepareModernVecGpuPass());
      pm.addPass(mlir::createConvertTensorToLinalgPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      runPmWithExit(pm, m_Module, "Pass Pipeline-4: Prepare Modern Vectorization");
    }

    //===----------------------------------------------------------------------===//
    // 6. Bufferization all
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateOneBufferizationPassPipeline(pm);
      runPmWithExit(
          pm, m_Module,
          "Pass Pipeline-5: Bufferization all to memref and do memref based optimization");
    }

    // Remeber, In the code below, I should not use CSE pass. In order to let some memrefs exist for
    // further analyse.

    //===----------------------------------------------------------------------===//
    // 7. Finalize Vectorization For GPU !!!
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createModernVectorizationAllGpuPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      runPmWithExit(pm, m_Module, "Pass Pipeline-6: Finalize Modern Vectorization");
    }

    //===----------------------------------------------------------------------===//
    // 8. Map to Blocks and Threads using builtin pass
    // Map parallel to gpu's dimension Greedily
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createLoweringScfForAllToParallelPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createGpuMapParallelLoopsPass());
      pm.addPass(mlir::createParallelLoopToGpuPass());
      pm.addPass(mlir::createGpuKernelOutliningPass());
      runPmWithExit(pm, m_Module, "Pass Pipeline-7: Forall to Parallel and do Mapping to device");
    }

    //===----------------------------------------------------------------------===//
    // 9. Optimizing on gpu kernel
    //===----------------------------------------------------------------------===//

    //===----------------------------------------------------------------------===//
    // 10. Lowering Affine to SCF. And do some fusion
    //===----------------------------------------------------------------------===//

    //===----------------------------------------------------------------------===//
    // 10. Lowering all one by one
    //===----------------------------------------------------------------------===//

    if (!m_OutputFilePath.empty()) {
      nncv::compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
    } else {
      m_Module->dump();
    }
    return;
  } else if (m_GenHostWParallel) {
    //===----------------------------------------------------------------------===//
    // 1 Finalize all input
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addPass(mlir::bufferization::createEmptyTensorToAllocTensorPass());
      populateInputOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Pass Pipeline-1: Frontend Normalization Pass Pipeline");
    }

    //===----------------------------------------------------------------------===//
    // 2 Doing some tensor eliminate
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateTensorOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Pass Pipeline-2: Cast Away Tensor Leading One Dims");
    }

    //===----------------------------------------------------------------------===//
    // 3 Using winograd method before lowering MatMul
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateWinogradOrImg2ColPassPipeline(pm);
      runPmSilent(pm, m_Module);
    }

    //===----------------------------------------------------------------------===//
    // 4 High level tile And Decompose
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      mlir::nncv::codegen_llvm_cpu::addTilePassPipeline(pm);
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createDecomposeTransformGenPass());
      runPmWithExit(
          pm, m_Module,
          "Pass Pipeline-3: High Level Tiling [Matmul/Conv/Pool/Generic/Pad] And Decompose");
    }

    //===----------------------------------------------------------------------===//
    // 5. Prepare vec
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createPrepareModernVecPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      // TODO hoist

      runPmWithExit(pm, m_Module, "Pass Pipeline-4: Prepare Modern Vectorization");
    }

    //===----------------------------------------------------------------------===//
    // 6. Convert Tensor To linalg
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addPass(mlir::createConvertTensorToLinalgPass());
      runPmWithExit(pm, m_Module, "Pass Pipeline-5: Convert Tensor To Linalg");
    }

    //===----------------------------------------------------------------------===//
    // 7. Bufferization all
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateOneBufferizationPassPipeline(pm);
      runPmWithExit(
          pm, m_Module,
          "Pass Pipeline-6: Bufferization all to memref and do memref based optimization");
    }

    //===----------------------------------------------------------------------===//
    // 8. Finalize Vectorization
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createModernVectorizationAllPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      runPmWithExit(pm, m_Module, "Pass Pipeline-7: Finalize Modern Vectorization");
    }

    //===----------------------------------------------------------------------===//
    // 9. distribute scf.forall to parallel for cpu target.
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createLoweringScfForAllToParallelPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createParallelLoopFusionPass());
      runPmSilent(pm, m_Module);
    }

    //===----------------------------------------------------------------------===//
    // 10. linalg Optimization using manual method.
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateConv2dToAffineVecManuallyPassPipeline(pm);
      pm.addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationDefaultPass());
      runPmWithExit(pm, m_Module,
                    "Pass Pipeline-8: Convert Conv2d To Affine+Vector using manual method");
    }

    //===----------------------------------------------------------------------===//
    // 11. Lowering Affine to SCF. And do some fusion
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateLoopFusionAndNormalizationPassPipeline(pm);
      populateAffineToSCFPassPipeline(pm);
      runPmWithExit(pm, m_Module,
                    "Pass Pipeline-9: Affine Lowering to SCF and Loop fusion/normalization");
    }

    //===----------------------------------------------------------------------===//
    // 12. Lowering all one by one.
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addPass(mlir::createConvertLinalgToLoopsPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      if (m_WaprC) {
        pm.addNestedPass<mlir::func::FuncOp>(mlir::LLVM::createRequestCWrappersPass());
      }
      pm.addPass(mlir::memref::createExpandStridedMetadataPass());
      {
        mlir::ConvertSCFToOpenMPPassOptions options;
        printf("[ Warn ] Set num thread to %ld\n", m_NumThreads);
        options.numThreads = m_NumThreads;
        pm.addPass(mlir::createConvertSCFToOpenMPPass(options));
      }
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createConvertVectorToSCFPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createLowerAffinePass());
      pm.addPass(mlir::createConvertVectorToLLVMPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      pm.addPass(mlir::createConvertMathToLLVMPass());
      pm.addPass(mlir::createConvertMathToLibmPass());
      pm.addPass(mlir::createFinalizeMemRefToLLVMConversionPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createConvertSCFToCFPass());
      pm.addPass(mlir::createConvertOpenMPToLLVMPass());
      pm.addPass(mlir::createConvertFuncToLLVMPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      pm.addPass(mlir::createReconcileUnrealizedCastsPass());
      pm.addPass(mlir::nncv::createNestedTransformErasePass());
      // run
      runPmWithExit(pm, m_Module, "Pass Pipeline-10: Lowering all to llvm and libs call");
    }

    if (!m_OutputFilePath.empty()) {
      nncv::compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
    } else {
      m_Module->dump();
    }
    return;
  } else if (m_GenHostWoParallel) {
    //===----------------------------------------------------------------------===//
    // 1 Finalize all input
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addPass(mlir::bufferization::createEmptyTensorToAllocTensorPass());
      populateInputOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Pass Pipeline-1: Frontend Normalization Pass Pipeline");
    }

    //===----------------------------------------------------------------------===//
    // 2 Doing some tensor eliminate
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateTensorOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Pass Pipeline-2: Cast Away Tensor Leading One Dims");
    }

    //===----------------------------------------------------------------------===//
    // 3 Using winograd method before lowering MatMul
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateWinogradOrImg2ColPassPipeline(pm);
      runPmSilent(pm, m_Module);
    }

    //===----------------------------------------------------------------------===//
    // 4 High level tile And Decompose
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      mlir::nncv::codegen_llvm_cpu::addTilePassPipeline(pm);
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createDecomposeTransformGenPass());
      runPmWithExit(
          pm, m_Module,
          "Pass Pipeline-3: High Level Tiling [Matmul/Conv/Pool/Generic/Pad] And Decompose");
    }

    //===----------------------------------------------------------------------===//
    // 5. Prepare vec
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createPrepareModernVecPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      // TODO hoist

      runPmWithExit(pm, m_Module, "Pass Pipeline-4: Prepare Modern Vectorization");
    }

    //===----------------------------------------------------------------------===//
    // 6. Convert Tensor To linalg
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addPass(mlir::createConvertTensorToLinalgPass());
      runPmWithExit(pm, m_Module, "Pass Pipeline-5: Convert Tensor To Linalg");
    }

    //===----------------------------------------------------------------------===//
    // 7. Bufferization all
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateOneBufferizationPassPipeline(pm);
      runPmWithExit(
          pm, m_Module,
          "Pass Pipeline-6: Bufferization all to memref and do memref based optimization");
    }

    //===----------------------------------------------------------------------===//
    // 8. Finalize Vectorization
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createModernVectorizationAllPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      runPmWithExit(pm, m_Module, "Pass Pipeline-7: Finalize Modern Vectorization");
    }

    //===----------------------------------------------------------------------===//
    // 9. distribute scf.forall to parallel for gpu target.
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createLoweringScfForAllToParallelPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createParallelLoopFusionPass());
      runPmSilent(pm, m_Module);
    }

    //===----------------------------------------------------------------------===//
    // 10. linalg Optimization using manual method.
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateConv2dToAffineVecManuallyPassPipeline(pm);
      pm.addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationDefaultPass());
      runPmWithExit(pm, m_Module,
                    "Pass Pipeline-8: Convert Conv2d To Affine+Vector using manual method");
    }

    //===----------------------------------------------------------------------===//
    // 11. Lowering Affine to SCF. And do some fusion
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateLoopFusionAndNormalizationPassPipeline(pm);
      populateAffineToSCFPassPipeline(pm);
      runPmWithExit(pm, m_Module,
                    "Pass Pipeline-9: Affine Lowering to SCF and Loop fusion/normalization");
    }

    //===----------------------------------------------------------------------===//
    // 12. Lowering all one by one.
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addPass(mlir::createConvertLinalgToLoopsPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      if (m_WaprC) {
        pm.addNestedPass<mlir::func::FuncOp>(mlir::LLVM::createRequestCWrappersPass());
      }
      pm.addPass(mlir::memref::createExpandStridedMetadataPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createConvertVectorToSCFPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createLowerAffinePass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createConvertSCFToCFPass());
      pm.addPass(mlir::createConvertVectorToLLVMPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      pm.addPass(mlir::createConvertMathToLLVMPass());
      pm.addPass(mlir::createConvertMathToLibmPass());
      pm.addPass(mlir::createFinalizeMemRefToLLVMConversionPass());
      pm.addPass(mlir::createConvertFuncToLLVMPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      pm.addPass(mlir::createReconcileUnrealizedCastsPass());
      pm.addPass(mlir::nncv::createNestedTransformErasePass());
      // run
      runPmWithExit(pm, m_Module, "Pass Pipeline-10: Lowering all to llvm and libs call");
    }

    if (!m_OutputFilePath.empty()) {
      nncv::compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
    } else {
      m_Module->dump();
    }
    return;
  } else if (m_GenConfigFileOnly) {
    pm.clear();
    populateInputOptimizationPassPipeline(pm);
    runPmWithExit(pm, m_Module, "Frontend Normalization Pass Pipeline");
    if (!::nncv::compiler::utils::SaveTileOpsConfigFile(m_ConfigFilePath)) {
      printf("[ Erro ] Failed when saving config file.\n");
    }
    return;
  }
}

}  // namespace pipeline
}  // namespace nncv