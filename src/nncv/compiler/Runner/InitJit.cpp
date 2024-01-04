#include "nncv/compiler/Runner/InitJit.hpp"

namespace nncv {
namespace runner {

bool NncvJit::init() {
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

}  // namespace runner
}  // namespace nncv