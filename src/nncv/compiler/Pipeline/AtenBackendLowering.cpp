#include "nncv/compiler/Pipeline/AtenBackendLowering.hpp"
#include "mlir/Conversion/AffineToStandard/AffineToStandard.h"
#include "mlir/Conversion/OpenMPToLLVM/ConvertOpenMPToLLVM.h"
#include "mlir/Conversion/ReconcileUnrealizedCasts/ReconcileUnrealizedCasts.h"
#include "mlir/Conversion/SCFToControlFlow/SCFToControlFlow.h"
#include "mlir/Conversion/ControlFlowToLLVM/ControlFlowToLLVM.h"
#include "mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/Conversion/SCFToGPU/SCFToGPUPass.h"
#include "mlir/Conversion/SCFToOpenMP/SCFToOpenMP.h"
#include "mlir/Conversion/MemRefToLLVM/MemRefToLLVM.h"
#include "mlir/Conversion/FuncToLLVM/ConvertFuncToLLVMPass.h"
#include "mlir/Dialect/Affine/Passes.h"
#include "mlir/Dialect/Arith/Transforms/Passes.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/GPU/Transforms/Passes.h"
#include "mlir/Dialect/MemRef/Transforms/Passes.h"
#include "mlir/Dialect/SCF/Transforms/Passes.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"
#include "nncv/compiler/Conversion/AtenToMlir/AtenMlirToLlvm.hpp"

#include "nncv/compiler/Dialects/AutoTen/Transforms/Passes.hpp"
#include "nncv/compiler/Utils/MlirIo.hpp"
#include "nncv/compiler/Utils/Exec.hpp"

namespace nncv::compiler::pipeline {
void AtenBackendLoweringPipeline::run() {
  mlir::PassManager pm(m_Module.get()->getName());
  bool isPollyOk = false;

  {
    pm.clear();
    pm.addNestedPass<mlir::func::FuncOp>(mlir::createLoopInvariantCodeMotionPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createAffineLoopInvariantCodeMotionPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createPipelineDataTransferPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createAffineScalarReplacementPass());
    pm.addNestedPass<mlir::func::FuncOp>(mlir::affine::createAffineLoopNormalizePass(true));
    (void)pm.run(*m_Module);
  }

  if (m_isNative && !m_isNVPTX) {
    if (m_usingPoly) {
      // Raise memref.load and memref.store to affine.load and affine.store
      // if memref is in affine scope.
      {
        pm.clear();
        pm.addNestedPass<mlir::func::FuncOp>(
            mlir::nncv::aten::createRaiseMemerefLSInAffineToAffineLSPass());
        if (mlir::failed(pm.run(*m_Module))) {
          printf("[ Erro ] Raise memref.load and memref.store to affine.load and affine.store "
                 "failed\n");
          exit(-1);
        } else {
          compiler::utils::SaveMlirModuleToFile(m_Module, ".cache.air");
        }
      }

      // Affine Scheduler
      {
        utils::ExecObject exec("polymer-opt");
        exec.pushArgs("-reg2mem");
        exec.pushArgs("-extract-scop-stmt");
        if (m_usingOmp) {
          exec.pushArgs("-pluto-opt=parallelize gen-parallel");
        } else {
          exec.pushArgs("-pluto-opt");
        }
        exec.pushArgs(".cache.air");
        exec.pushArgs("-o");
        exec.pushArgs(".cache.mlir");

        exec.setHideOutput(true);
        exec.runSyncWait();

        if (!exec.isSuccess()) {
          printf("[ Erro ] Failed when doing polly, using original aten-ir\n");
        } else {
          isPollyOk = true;
        }
      }

      {
        if (isPollyOk) {
          compiler::utils::ImportMlirModuleFromFile(m_Module, &m_Context, ".cache.mlir");
        }
      }
    }

    if (m_usingOmp) {
      {
        pm.clear();
        pm.addNestedPass<mlir::func::FuncOp>(
            mlir::nncv::aten::createRaiseMemerefLSInAffineToAffineLSPass());
        pm.addNestedPass<mlir::func::FuncOp>(mlir::createLowerAffinePass());
        (void)pm.run(*m_Module);
      }
      {
        pm.clear();
        mlir::ConvertSCFToOpenMPPassOptions options;
        options.numThreads = 16;
        pm.addPass(mlir::createConvertSCFToOpenMPPass(options));
        pm.addNestedPass<mlir::func::FuncOp>(mlir::bufferization::createFinalizingBufferizePass());
        pm.addPass(mlir::memref::createExpandStridedMetadataPass());
        pm.addPass(mlir::arith::createArithExpandOpsPass());
        pm.addPass(mlir::createArithToLLVMConversionPass());
        pm.addPass(mlir::createFinalizeMemRefToLLVMConversionPass());
        pm.addPass(mlir::createConvertSCFToCFPass());
        pm.addPass(mlir::createConvertOpenMPToLLVMPass());
        pm.addPass(mlir::createArithToLLVMConversionPass());
        pm.addPass(mlir::createConvertFuncToLLVMPass());
        pm.addPass(mlir::createCanonicalizerPass());
        pm.addPass(mlir::createCSEPass());
        pm.addPass(mlir::createReconcileUnrealizedCastsPass());
        if (mlir::failed(pm.run(*m_Module))) {
          printf("[ Erro ] When doing aten-lang's mlir to llvm conversion\n");
          exit(-1);
        }
      }
    } else {
      // Lowering to all Llvm IR
      {
        pm.clear();
        pm.addPass(mlir::nncv::createConvertAtenMlirToLlvmPass());
        pm.addPass(mlir::createCSEPass());
        if (mlir::failed(pm.run(*m_Module))) {
          printf("[ Erro ] When doing aten-lang's mlir to llvm conversion\n");
          exit(-1);
        }
      }
    }

    if (m_ShowLlvmIR) {
      if (!m_OutputFilePath.empty()) {
        compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
      } else {
        m_Module->dump();
      }
      exit(0);
    } else {
      if (!m_DierctlyRun) {
        if (!m_OutputFilePath.empty()) {
          compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
        } else {
          std::string filePath = "a.nvm";
          compiler::utils::SaveMlirModuleToFile(m_Module, filePath);
        }
      }
    }
  } else if (m_isNVPTX && !m_isNative) {
    if (m_usingPoly) {
      printf("[ Warn ] When lowering to gpu target, functions will be inlined by default\n");
      // Raise memref.load and memref.store to affine.load and affine.store
      // if memref is in affine scope.
      {
        pm.clear();
        pm.addNestedPass<mlir::func::FuncOp>(
            mlir::nncv::aten::createRaiseMemerefLSInAffineToAffineLSPass());
        if (mlir::failed(pm.run(*m_Module))) {
          printf("[ Erro ] Raise memref.load and memref.store to affine.load and affine.store "
                 "failed\n");
          exit(-1);
        } else {
          compiler::utils::SaveMlirModuleToFile(m_Module, ".cache.air");
        }
      }

      // Affine Scheduler
      {
        utils::ExecObject exec("polymer-opt");
        exec.pushArgs("-reg2mem");
        exec.pushArgs("-extract-scop-stmt");
        if (m_usingOmp) {
          exec.pushArgs("-pluto-opt=parallelize gen-parallel");
        } else {
          exec.pushArgs("-pluto-opt");
        }
        exec.pushArgs(".cache.air");
        exec.pushArgs("-o");
        exec.pushArgs(".cache.mlir");

        exec.setHideOutput(true);
        exec.runSyncWait();

        if (!exec.isSuccess()) {
          printf("[ Erro ] Failed when doing polly, using original aten-ir\n");
        } else {
          isPollyOk = true;
        }
      }

      {
        if (isPollyOk) {
          compiler::utils::ImportMlirModuleFromFile(m_Module, &m_Context, ".cache.mlir");
        }
      }
    }

    // outline map to block and threads
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(mlir::createAffineForToGPUPass());
      (void)pm.run(*m_Module);
    }

    // save
    if (m_ShowLlvmIR) {
      if (!m_OutputFilePath.empty()) {
        compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
      } else {
        m_Module->dump();
      }
      exit(0);
    } else {
      if (!m_DierctlyRun) {
        if (!m_OutputFilePath.empty()) {
          compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
        } else {
          std::string filePath = "a.nvm";
          compiler::utils::SaveMlirModuleToFile(m_Module, filePath);
        }
      }
    }
  }
}
}  // namespace nncv::compiler::pipeline