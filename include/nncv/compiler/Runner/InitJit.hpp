#ifndef NNCV_COMPILER_RUNNER_INITJIT_HPP_
#define NNCV_COMPILER_RUNNER_INITJIT_HPP_
#pragma once

#include "mlir/IR/BuiltinOps.h"
#include "mlir/ExecutionEngine/OptUtils.h"
#include "mlir/ExecutionEngine/ExecutionEngine.h"
#include "mlir/Target/LLVMIR/Dialect/LLVMIR/LLVMToLLVMIRTranslation.h"
#include "mlir/Target/LLVMIR/Dialect/Builtin/BuiltinToLLVMIRTranslation.h"

#include "llvm/Support/TargetSelect.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"

#include "nncv/compiler/Runner/RunnerCtx.hpp"

namespace nncv {
namespace runner {

class NncvJit {
 public:
  NncvJit(){};

  inline void setFilePath(const std::string& file_path) { m_FilePath = file_path; }

  bool run(const std::string& entry_point = "main");

 private:
  bool init();

 private:
  std::string m_FilePath;
  mlir::OwningOpRef<mlir::ModuleOp> m_Module;
  std::vector<std::string> m_Libs;
};

}  // namespace runner
}  // namespace nncv

#endif  //! NNCV_COMPILER_RUNNER_INITJIT_HPP_