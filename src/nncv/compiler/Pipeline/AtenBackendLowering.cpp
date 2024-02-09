#include "nncv/compiler/Pipeline/AtenBackendLowering.hpp"
#include "mlir/Dialect/Func/IR/FuncOps.h"
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

  if (m_isNative && !m_isNVPTX) {
    // Raise memref.load and memref.store to affine.load and affine.store
    // if memref is in affine scope.
    {
      pm.clear();
      pm.addNestedPass<mlir::func::FuncOp>(
          mlir::nncv::aten::createRaiseMemerefLSInAffineToAffineLSPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf(
            "[ Erro ] Raise memref.load and memref.store to affine.load and affine.store failed\n");
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
      exec.pushArgs("-pluto-opt");
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

    // TODO read from ".cache.mlir" if success.
    {
      if (isPollyOk) {
        compiler::utils::ImportMlirModuleFromFile(m_Module, &m_Context, ".cache.mlir");
      }
    }

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
    // TODO for nvidia pipeline
  }
}
}  // namespace nncv::compiler::pipeline