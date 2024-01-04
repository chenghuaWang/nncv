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
 private:
  bool init();

 private:
  mlir::ModuleOp m_TheModule;
};

}  // namespace runner
}  // namespace nncv

#endif  //! NNCV_COMPILER_RUNNER_INITJIT_HPP_