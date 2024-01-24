#include "nncv/compiler/Pipeline/AtenBackendLowering.hpp"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"
#include "nncv/compiler/Conversion/AtenToMlir/AtenMlirToLlvm.hpp"

#include "nncv/compiler/Utils/MlirIo.hpp"

namespace nncv::compiler::pipeline {
void AtenBackendLoweringPipeline::run() {
  mlir::PassManager pm(m_Module.get()->getName());

  // TODO Affine scheduler
  {

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
    if (!m_OutputFilePath.empty()) {
      compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
    } else {
      std::string filePath = "a.nvm";
      compiler::utils::SaveMlirModuleToFile(m_Module, filePath);
    }
  }
}
}  // namespace nncv::compiler::pipeline