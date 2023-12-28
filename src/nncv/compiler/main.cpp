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

llvm::cl::opt<std::string> InputFilename(llvm::cl::Positional, llvm::cl::desc("<input file>"),
                                         llvm::cl::Required);
llvm::cl::opt<bool> ShowCst("show-cst", llvm::cl::desc("<show CST>"), llvm::cl::Optional);
llvm::cl::opt<bool> ShowMlir("show-mlir", llvm::cl::desc("<show MLIR>"), llvm::cl::Optional);

int main(int argc, char* argv[]) {
  mlir::registerAsmPrinterCLOptions();
  mlir::registerMLIRContextCLOptions();
  // mlir::registerPassManagerCLOptions();

  llvm::cl::SetVersionPrinter([](llvm::raw_ostream& OS) { OS << VERSION_STR; });
  llvm::cl::ParseCommandLineOptions(argc, argv);

  // init dialect
  mlir::DialectRegistry registry;

  // init MLIR
  mlir::MLIRContext MlirContext(registry);
  MlirContext.getOrLoadDialect<mlir::aten::AtenDialect>();
  mlir::OwningOpRef<mlir::ModuleOp> MlirModule;

  nncv::compiler::pipeline::FrontendPipeline fr(MlirContext, MlirModule);

  fr.setFilePath(InputFilename.getValue());
  fr.setShowCst(ShowCst.getValue());
  fr.setDumpMlir(ShowMlir.getValue());
  fr.run();
}