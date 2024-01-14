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

#include "mlir/Dialect/Tensor/IR/Tensor.h"
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
#include "llvm/Support/SourceMgr.h"
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
#include "mlir/Support/FileUtilities.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/MLProgram/IR/MLProgram.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlow.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Pipeline/Frontend.hpp"
#include "nncv/compiler/Utils/PlatformCtx.hpp"

#include "nncv/compiler/Conversion/Passes.h"

#include "nncv/compiler/Pipeline/DnnModelLowering.hpp"

llvm::cl::opt<std::string> InputFilename(llvm::cl::Positional, llvm::cl::desc("<input file>"),
                                         llvm::cl::Optional);
llvm::cl::opt<bool> ShowCst("show-cst", llvm::cl::desc("<show CST>"), llvm::cl::Optional);
llvm::cl::opt<bool> ShowMlir("show-mlir", llvm::cl::desc("<show MLIR>"), llvm::cl::Optional);
llvm::cl::opt<bool> GetPlatformInfoOnly("get-platform-info-only",
                                        llvm::cl::desc("<get platform infomation only>"),
                                        llvm::cl::Optional);
llvm::cl::opt<std::string> SetLowerTarget("target", llvm::cl::desc("<to target>"),
                                          llvm::cl::Optional);

void LoadMLIRDialects(mlir::MLIRContext& context) {
  context.loadDialect<mlir::arith::ArithDialect, mlir::memref::MemRefDialect,
                      mlir::func::FuncDialect, mlir::bufferization::BufferizationDialect,
                      mlir::linalg::LinalgDialect, mlir::ml_program::MLProgramDialect,
                      mlir::cf::ControlFlowDialect, mlir::affine::AffineDialect,
                      mlir::scf::SCFDialect, mlir::tensor::TensorDialect>();
  mlir::registerLLVMDialectTranslation(context);
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
  LoadMLIRDialects(MlirContext);
  if (SuffixStr == "aten") {
    // compile aten-lang
    nncv::compiler::pipeline::FrontendPipeline fr(MlirContext, MlirModule);

    fr.setFilePath(InputFilename.getValue());
    fr.setShowCst(ShowCst.getValue());
    fr.setDumpMlir(ShowMlir.getValue());
    fr.run();
  } else if (SuffixStr == "nncv" || SuffixStr == "mlir") {
    std::string ErrorMessage;
    auto __file = mlir::openInputFile(CurFilePath, &ErrorMessage);
    if (!__file) {
      printf("[ Erro ] %s\n", ErrorMessage.c_str());
      return -1;
    }
    std::unique_ptr<llvm::MemoryBuffer> Buffer = std::move(__file);
    llvm::SourceMgr SourceMgr;
    SourceMgr.AddNewSourceBuffer(std::move(Buffer), llvm::SMLoc());
    mlir::ParserConfig config(&MlirContext);
    MlirModule = mlir::parseSourceFile<mlir::ModuleOp>(SourceMgr, config);
  }

  // Start to lower all
  if (SetLowerTarget.empty()) { return 0; }

  mlir::PassManager pm(MlirModule.get()->getName());

  // ---------------------------------------------------------------------
  //  Middle end. Register Some Pass for optimize and lowering.
  // ---------------------------------------------------------------------
  nncv::pipeline::DnnModelLowering dnnModelLowerPipeline(&pm);
  if (SetLowerTarget.getValue() == "HostWParallel") {
    dnnModelLowerPipeline.setGenHostWParallel();
  } else if (SetLowerTarget.getValue() == "HostWoParallel") {
    dnnModelLowerPipeline.setGenHostWoParallel();
  } else if (SetLowerTarget.getValue() == "NVPTX") {
    dnnModelLowerPipeline.setGenNVPTX();
  }
  dnnModelLowerPipeline.registerAllPass();

  // ---------------------------------------------------------------------
  // Run all passes
  // ---------------------------------------------------------------------
  if (mlir::failed(pm.run(*MlirModule))) { return -1; }

  // for debug purpose
  if (ShowMlir.getValue()) { MlirModule->dump(); }
}