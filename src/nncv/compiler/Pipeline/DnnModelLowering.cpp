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
  pm.addPass(mlir::bufferization::createOneShotBufferizePass(OneShotOptions));
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());

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

  // optimize memref
  pm.addPass(mlir::memref::createExpandStridedMetadataPass());
  pm.addPass(mlir::memref::createExpandOpsPass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());

  // memref result type.
  pm.addPass(mlir::memref::createResolveRankedShapeTypeResultDimsPass());
  pm.addPass(mlir::memref::createResolveShapedTypeResultDimsPass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
}

void populateInputOptimizationPassPipeline(mlir::PassManager& pm) {
  mlir::nncv::createNncvFrontendToNormalPipeline(pm);
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
      populateInputOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Frontend Normalization Pass Pipeline");
    }

    //===----------------------------------------------------------------------===//
    // 2 Doing some tensor eliminate
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateTensorOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Cast Away Tensor Leading One Dims");
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
    // 4 High level tile
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateTileAllPassPipeline(pm, /*oneshot*/ false, /*lower conv*/ true, /*use gpu*/ true);
      runPmWithExit(pm, m_Module, "High Level Tiling [Matmul/Conv/Pool/Generic/Pad]");
    }

    //===----------------------------------------------------------------------===//
    // 5 Decompose All
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
      populateInputOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Frontend Normalization Pass Pipeline");
    }

    //===----------------------------------------------------------------------===//
    // 2 Doing some tensor eliminate
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateTensorOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Cast Away Tensor Leading One Dims");
    }

    //===----------------------------------------------------------------------===//
    // 3 Using winograd method before lowering MatMul
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateWinogradOrImg2ColPassPipeline(pm);
      runPmSilent(pm, m_Module);
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
      populateInputOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Frontend Normalization Pass Pipeline");
    }

    //===----------------------------------------------------------------------===//
    // 2 Doing some tensor eliminate
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateTensorOptimizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Cast Away Tensor Leading One Dims");
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
    // 4 High level tile
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateTileAllPassPipeline(pm, /*oneshot*/ false, /*lower conv*/ true, /*use gpu*/ false);
      runPmWithExit(pm, m_Module, "High Level Tiling [Matmul/Conv/Pool/Generic/Pad]");
    }

    //===----------------------------------------------------------------------===//
    // 5 Decompose All Conv2d And doing some optimization
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createDecomposeTransformGenPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      runPmWithExit(pm, m_Module, "Decompose Conv2d like op");
    }

    //===----------------------------------------------------------------------===//
    // 6 Vectorization on X86 with AVX2
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      // populateVectorizationPassPipeline(pm, /*use gpu*/ false);
      runPmWithExit(pm, m_Module, "Middle Level Vectorization");
    }

    //===----------------------------------------------------------------------===//
    // 7 Convert Tensor To linalg
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      pm.addPass(mlir::createConvertTensorToLinalgPass());
      runPmWithExit(pm, m_Module, "Convert Tensor To Linalg");
    }

    //===----------------------------------------------------------------------===//
    // 8 Bufferization all
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateOneBufferizationPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Bufferization all to memref and do memref based optimization");
    }

    //===----------------------------------------------------------------------===//
    // 9 linalg Optimization using manual method.
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateConv2dToAffineVecManuallyPassPipeline(pm);
      // pm.addPass(mlir::nncv::matmul_optimize::createMatMulOptimizationDefaultPass());
      runPmWithExit(pm, m_Module, "Convert Conv2d To Affine+Vector using manual method");
    }

    //===----------------------------------------------------------------------===//
    // 10 Lowering Affine to SCF. And do some fusion
    //===----------------------------------------------------------------------===//
    {
      pm.clear();
      populateLoopFusionAndNormalizationPassPipeline(pm);
      populateAffineToSCFPassPipeline(pm);
      runPmWithExit(pm, m_Module, "Affine Lowering to SCF and Loop fusion/normalization");
    }

    //===----------------------------------------------------------------------===//
    // 11 Lowering all one by one.
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
      mlir::VectorTransferToSCFOptions vectorTransferOptions;
      vectorTransferOptions.enableFullUnroll(true);
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::createConvertVectorToSCFPass(vectorTransferOptions));
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createLowerAffinePass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createConvertSCFToCFPass());
      pm.addPass(mlir::createConvertVectorToLLVMPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      pm.addPass(mlir::createConvertMathToLLVMPass());
      pm.addPass(mlir::createConvertMathToLibmPass());
      mlir::FinalizeMemRefToLLVMConversionPassOptions memrefLoweringOptions;
      memrefLoweringOptions.useAlignedAlloc = true;
      pm.addPass(mlir::createFinalizeMemRefToLLVMConversionPass(memrefLoweringOptions));
      pm.addPass(mlir::createConvertFuncToLLVMPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
      pm.addPass(mlir::createReconcileUnrealizedCastsPass());
      pm.addPass(mlir::nncv::createNestedTransformErasePass());
      // run
      runPmWithExit(pm, m_Module, "Lowering all to llvm and libs call");
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