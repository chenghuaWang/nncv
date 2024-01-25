#include "nncv/compiler/Runner/InitJit.hpp"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SourceMgr.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Support/FileUtilities.h"

namespace nncv {
namespace runner {

bool NncvJit::init() {
  // Initialize LLVM Target.
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();

  // translation from MLIR to LLVM.
  mlir::registerBuiltinDialectTranslation(*m_Module->getContext());
  mlir::registerLLVMDialectTranslation(*m_Module->getContext());

  return true;
}

bool NncvJit::run(const std::string& entry_point) {
  if (m_isDirectlyRun) {
    // Initialize LLVM Target.
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();

    // translation from MLIR to LLVM.
    mlir::registerBuiltinDialectTranslation(*(*m_DirectlyRunModule)->getContext());
    mlir::registerLLVMDialectTranslation(*(*m_DirectlyRunModule)->getContext());

    // set optimize pipline.
    auto optPipeline = mlir::makeOptimizingTransformer(/*optimized level*/ 3, /*size levl*/ 0,
                                                       /*target machine*/ nullptr);

    // create execution engine.
    mlir::ExecutionEngineOptions engineOptions;
    engineOptions.transformer = optPipeline;

    llvm::ArrayRef<llvm::StringRef> libPath = {
        "libmlir_c_runner_utils.so.18git", "libmlir_cuda_runtime.so.18git",
        "libmlir_runner_utils.so.18git", "libmlir_async_runtime.so.18git",
        "libmlir_float16_utils.so.18git"};
    engineOptions.sharedLibPaths = libPath;

    // create Engine on this Module.
    auto maybeEngine = mlir::ExecutionEngine::create(*(*m_DirectlyRunModule), engineOptions);
    if (!maybeEngine) {
      // FIXME throw error
      return false;
    }
    auto& engine = maybeEngine.get();

    // TODO pass library info to mlir jit

    // TODO timing

    // Invoke the JIT-compiled function.
    auto invocationResult = engine->invokePacked(entry_point);

    if (invocationResult) {
      // FIXME throw error
      return false;
    }

    return true;
  } else {
    // new context
    // init dialect
    mlir::DialectRegistry registry;

    // init MLIR
    mlir::MLIRContext MlirContext(registry);

    // Open File
    std::string ErrorMessage;
    auto __file = mlir::openInputFile(m_FilePath, &ErrorMessage);
    if (!__file) {
      printf("[ Erro ] %s\n", ErrorMessage.c_str());
      return -1;
    }
    std::unique_ptr<llvm::MemoryBuffer> Buffer = std::move(__file);
    llvm::SourceMgr SourceMgr;
    SourceMgr.AddNewSourceBuffer(std::move(Buffer), llvm::SMLoc());
    mlir::ParserConfig config(&MlirContext);
    MlirContext.loadDialect<mlir::LLVM::LLVMDialect>();
    m_Module = mlir::parseSourceFile<mlir::ModuleOp>(SourceMgr, config);

    init();

    // set optimize pipline.
    auto optPipeline = mlir::makeOptimizingTransformer(/*optimized level*/ 3, /*size levl*/ 0,
                                                       /*target machine*/ nullptr);

    // create execution engine.
    mlir::ExecutionEngineOptions engineOptions;
    engineOptions.transformer = optPipeline;

    llvm::ArrayRef<llvm::StringRef> libPath = {
        "libmlir_c_runner_utils.so.18git", "libmlir_cuda_runtime.so.18git",
        "libmlir_runner_utils.so.18git", "libmlir_async_runtime.so.18git",
        "libmlir_float16_utils.so.18git"};
    engineOptions.sharedLibPaths = libPath;

    // create Engine on this Module.
    auto maybeEngine = mlir::ExecutionEngine::create(*m_Module, engineOptions);
    if (!maybeEngine) {
      // FIXME throw error
      return false;
    }
    auto& engine = maybeEngine.get();

    // TODO pass library info to mlir jit

    // TODO timing

    // Invoke the JIT-compiled function.
    auto invocationResult = engine->invokePacked(entry_point);

    if (invocationResult) {
      // FIXME throw error
      return false;
    }

    return true;
  }
  return true;
}

}  // namespace runner
}  // namespace nncv