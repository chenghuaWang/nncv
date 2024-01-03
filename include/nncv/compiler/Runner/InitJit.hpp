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
  bool init() {
    // Initialize LLVM Target.
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();

    // translation from MLIR to LLVM.
    mlir::registerBuiltinDialectTranslation(*m_TheModule->getContext());
    mlir::registerLLVMDialectTranslation(*m_TheModule->getContext());

    // set optimize pipline.
    auto optPipeline = mlir::makeOptimizingTransformer(/*optimized level*/ 3, /*size levl*/ 0,
                                                       /*target machine*/ nullptr);

    // create execution engine.
    mlir::ExecutionEngineOptions engineOptions;
    engineOptions.transformer = optPipeline;

    // create Engine on this Module.
    auto maybeEngine = mlir::ExecutionEngine::create(m_TheModule, engineOptions);
    if (!maybeEngine) {
      // FIXME throw error
      return false;
    }
    auto& engine = maybeEngine.get();

    // Invoke the JIT-compiled function.
    auto invocationResult = engine->invokePacked("main");

    if (invocationResult) {
      // FIXME throw error
      return false;
    }

    return true;
  }

 private:
  mlir::ModuleOp m_TheModule;
};

}  // namespace runner
}  // namespace nncv

#endif  //! NNCV_COMPILER_RUNNER_INITJIT_HPP_