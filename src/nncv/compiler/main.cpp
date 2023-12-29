/**
 * @file main.cpp
 * @author chenghua Wang (chenghua.wang.edu@domain.com)
 * @brief Parse command line and do some actions.
 * @version 0.1
 * @date 2023-05-19
 * @details check https://www.llvm.org/docs/CommandLine.html#quick-start-guide for how to use LLVM's
 * CommandLine tools.
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifdef _WIN32
#define VERSION_STR                                         \
  "NNCV Compiler(build for amd64, windows, using clang15);" \
  "version is 0.0.1(pre-build).\n"                          \
  "author: chenghua.wang\n"
#else
#define VERSION_STR                                               \
  "NNCV Compiler(build for amd64, general-linux, using clang15);" \
  "version is 0.0.1(pre-build).\n"                                \
  "author: chenghua.wang\n"
#endif

// make complex warning silence
#ifdef _WIN32
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#endif

#include "llvm/ADT/ScopeExit.h"
#include "llvm/Support/CommandLine.h"
#include "mlir/Dialect/Affine/Passes.h"
#include "mlir/ExecutionEngine/ExecutionEngine.h"
#include "mlir/ExecutionEngine/OptUtils.h"
#include "mlir/IR/AsmState.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Verifier.h"
#include "mlir/InitAllDialects.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Target/LLVMIR/Dialect/LLVMIR/LLVMToLLVMIRTranslation.h"
#include "mlir/Target/LLVMIR/Export.h"
#include "mlir/Transforms/Passes.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Pipeline/Frontend.hpp"
#include "nncv/compiler/Utils/PlatformCtx.hpp"

llvm::cl::opt<std::string> InputFilename(llvm::cl::Positional, llvm::cl::desc("<input file>"),
                                         llvm::cl::Optional);
llvm::cl::opt<bool> ShowCst("show-cst", llvm::cl::desc("<show CST>"), llvm::cl::Optional);
llvm::cl::opt<bool> ShowMlir("show-mlir", llvm::cl::desc("<show MLIR>"), llvm::cl::Optional);
llvm::cl::opt<bool> GetPlatformInfoOnly("get-platform-info-only",
                                        llvm::cl::desc("<get platform infomation only>"),
                                        llvm::cl::Optional);

mlir::FailureOr<std::string> ReadWholeFile(std::string& FilePath) {
  auto fd = llvm::sys::fs::openNativeFileForRead(FilePath);
  if (!fd) {
    llvm::consumeError(fd.takeError());
    printf("[ INFO ] Can not open file %s\n", FilePath.c_str());
    return mlir::failure();
  }
  std::optional exit = llvm::make_scope_exit([&fd] { llvm::sys::fs::closeFile(*fd); });
  llvm::sys::fs::file_status Status;
  {
    auto error = llvm::sys::fs::status(*fd, Status);
    if (error) {
      printf("[ INFO ] File descriptor is not available");
      return mlir::failure();
    }
  }
  std::string Content(Status.getSize(), '\0');
  auto read = llvm::sys::fs::readNativeFile(*fd, {Content.data(), Content.size()});
  if (!read) {
    llvm::consumeError(fd.takeError());
    printf("[ INFO ] Can not read file %s\n", FilePath.c_str());
    return mlir::failure();
  }
  return {std::move(Content)};
}

int main(int argc, char* argv[]) {
  // ---------------------------------------------------------------------
  //  Preparation for cli.
  // ---------------------------------------------------------------------
  mlir::registerAsmPrinterCLOptions();
  mlir::registerMLIRContextCLOptions();
  // mlir::registerPassManagerCLOptions();

  llvm::cl::SetVersionPrinter([](llvm::raw_ostream& OS) { OS << VERSION_STR; });
  llvm::cl::ParseCommandLineOptions(argc, argv);

  // detecting platform
  nncv::compiler::utils::PlatformCtx pctx = nncv::compiler::utils::PlatformCtxInit();
  if (GetPlatformInfoOnly.getValue() == true) { exit(0); }

  // init dialect
  mlir::DialectRegistry registry;

  // init MLIR
  mlir::MLIRContext MlirContext(registry);
  MlirContext.getOrLoadDialect<mlir::aten::AtenDialect>();
  mlir::OwningOpRef<mlir::ModuleOp> MlirModule;

  std::string CurFilePath = InputFilename.getValue();
  std::string SuffixStr = CurFilePath.substr(CurFilePath.find_last_of('.') + 1);

  // ---------------------------------------------------------------------
  //  Front end. Import materials.
  // ---------------------------------------------------------------------
  if (SuffixStr == "aten") {
    // compile aten-lang
    nncv::compiler::pipeline::FrontendPipeline fr(MlirContext, MlirModule);

    fr.setFilePath(InputFilename.getValue());
    fr.setShowCst(ShowCst.getValue());
    fr.setDumpMlir(ShowMlir.getValue());
    fr.run();
  } else if (SuffixStr == "nncv") {
    // compile dnn mlir from torch-mlir linag-on-tensor option on.
    auto StrContent = ReadWholeFile(CurFilePath);
    if (mlir::failed(StrContent)) { exit(-1); }

    // config
    auto Config = mlir::ParserConfig(&MlirContext, /*verifyAfterParse=*/false);

    if (auto Buffer = llvm::MemoryBufferRef(*StrContent, CurFilePath); mlir::isBytecode(Buffer)) {
      auto Body = std::make_unique<mlir::Block>();
      if (mlir::failed(mlir::readBytecodeFile(Buffer, Body.get(), Config))) {
        printf("[ Erro ] Failed to read bytecode file(failed from mlir).\n");
      }
      MlirModule = mlir::parseSourceString<mlir::ModuleOp>(*StrContent, Config);
      MlirModule->dump();
    }
  }

  // ---------------------------------------------------------------------
  //  Middle end. Register Some Pass for optimize and lowering.
  // ---------------------------------------------------------------------
}