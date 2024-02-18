/**
 * @file main.cpp
 * @author chenghua Wang (chenghua.wang.edu@domain.com)
 * @brief Parse command line and do some actions.
 * @version 0.1
 * @date 2023-05-19
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

#include "mlir/Debug/Counter.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
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
#include "mlir/InitAllPasses.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Pipeline/Frontend.hpp"
#include "nncv/compiler/Pipeline/DnnModelLowering.hpp"
#include "nncv/compiler/Pipeline/AtenBackendLowering.hpp"
#include "nncv/compiler/Utils/PlatformCtx.hpp"
#include "nncv/compiler/Utils/MlirIo.hpp"

#include "nncv/compiler/Runner/InitJit.hpp"

llvm::cl::opt<std::string> InputFilename(llvm::cl::Positional, llvm::cl::desc("<input file>"),
                                         llvm::cl::Optional);
llvm::cl::opt<bool> ShowCst("show-cst", llvm::cl::desc("<show CST>"), llvm::cl::Optional);
llvm::cl::opt<bool> OnlyShowAtenIR("aten-ir", llvm::cl::desc("<generate Aten IR>"),
                                   llvm::cl::Optional);
llvm::cl::opt<bool> OnlyShowBuiltInMlir("built-in-mlir", llvm::cl::desc("<generate Builtin MLIR>"),
                                        llvm::cl::Optional);
llvm::cl::opt<bool> OnlyShowLlvmIR("llvm-ir", llvm::cl::desc("<generate llvm ir>"),
                                   llvm::cl::Optional);
llvm::cl::opt<bool> GetPlatformInfoOnly("get-platform-info-only",
                                        llvm::cl::desc("<get platform infomation only>"),
                                        llvm::cl::Optional);
llvm::cl::opt<std::string> SetLowerTarget("target", llvm::cl::desc("<to target>"),
                                          llvm::cl::Optional);
llvm::cl::opt<std::string> OutputFilename("o", llvm::cl::desc("<output file>"), llvm::cl::Optional);
llvm::cl::opt<bool> VmMode("vm", llvm::cl::desc("<set nncv-c as vm>"), llvm::cl::Optional);
llvm::cl::opt<bool> RunDirectly("run", llvm::cl::desc("<run a .aten file directly>"),
                                llvm::cl::Optional);
llvm::cl::opt<bool> WarpC("warp-c-interface", llvm::cl::desc("<warp c interface>"),
                          llvm::cl::Optional);
llvm::cl::opt<std::string> ConfigFilePathOption("config-file-path",
                                                llvm::cl::desc("<config file path>"),
                                                llvm::cl::Optional);
llvm::cl::opt<bool> WPoly("wpoly", llvm::cl::desc("<using polyhedral method>"), llvm::cl::Optional);
llvm::cl::opt<bool> WOmp("womp", llvm::cl::desc("<using open mp>"), llvm::cl::Optional);
llvm::cl::opt<std::string> GenConfigFileOnly("gen-config-file-only",
                                             llvm::cl::desc("<Just gen a config file for model>"),
                                             llvm::cl::Optional);

void LoadMLIRDialects(mlir::MLIRContext& context) {
  context
      .loadDialect<mlir::arith::ArithDialect, mlir::memref::MemRefDialect, mlir::func::FuncDialect,
                   mlir::bufferization::BufferizationDialect, mlir::linalg::LinalgDialect,
                   mlir::ml_program::MLProgramDialect, mlir::cf::ControlFlowDialect,
                   mlir::affine::AffineDialect, mlir::scf::SCFDialect, mlir::tensor::TensorDialect,
                   mlir::vector::VectorDialect, mlir::LLVM::LLVMDialect>();
  mlir::registerLLVMDialectTranslation(context);
}

void parseCLIOptions(int argc, char* argv[]) {
  mlir::MlirOptMainConfig config = mlir::MlirOptMainConfig::createFromCLOptions();
  llvm::cl::ParseCommandLineOptions(argc, argv);
}

int main(int argc, char* argv[]) {
  // init dialect
  mlir::DialectRegistry registry;
  mlir::registerAllDialects(registry);
  mlir::registerAllPasses();
  mlir::MlirOptMainConfig::registerCLOptions(registry);

  // ---------------------------------------------------------------------
  //  Preparation for cli.
  // ---------------------------------------------------------------------
  mlir::registerAsmPrinterCLOptions();
  mlir::registerMLIRContextCLOptions();
  mlir::registerPassManagerCLOptions();

  llvm::cl::SetVersionPrinter([](llvm::raw_ostream& OS) { OS << VERSION_STR; });
  mlir::registerDefaultTimingManagerCLOptions();
  mlir::tracing::DebugCounter::registerCLOptions();
  parseCLIOptions(argc, argv);

  // detecting platform
  nncv::compiler::utils::PlatformCtxInit(GetPlatformInfoOnly.getValue());
  nncv::compiler::utils::PlatformCtx::getInstance().init();
  nncv::compiler::utils::PlatformCtx::getInstance().SetConfigFilePath(
      ConfigFilePathOption.getValue());
  nncv::compiler::utils::PlatformCtx::getInstance().InitFromConfigFile();
  if (GetPlatformInfoOnly.getValue() == true) { exit(0); }

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
    fr.setInputFilePath(InputFilename.getValue());
    fr.setShowCst(ShowCst.getValue());
    fr.setBuiltinMlir(OnlyShowBuiltInMlir.getValue());
    fr.setGenAtenIR(OnlyShowAtenIR.getValue());
    if (!OutputFilename.getValue().empty()) { fr.setOutputFilePath(OutputFilename.getValue()); }
    fr.run();

    nncv::compiler::pipeline::AtenBackendLoweringPipeline ablp(MlirContext, MlirModule);
    if (!OutputFilename.getValue().empty()) { ablp.setOutputFilePath(OutputFilename.getValue()); }
    ablp.setShowLlvmIR(OnlyShowLlvmIR.getValue());
    ablp.setDierectlyRun(RunDirectly.getValue());
    ablp.setWPoly(WPoly.getValue());
    ablp.setWOmp(WOmp.getValue());
    if (SetLowerTarget.getValue() == "NVPTX") {
      ablp.setGenNative(false);
      ablp.setGenNVPTX(true);
    } else {
      ablp.setGenNative(true);
      ablp.setGenNVPTX(false);
    }
    ablp.run();

    if (RunDirectly.getValue()) {
      // the code follow is for run aten's llvm ir in jit
      nncv::runner::NncvJit Jit;
      // set module
      Jit.setModuleOp(&MlirModule);
      // Run jit
      if (Jit.run()) {
        exit(0);
      } else {
        exit(-1);
      }
    }

  } else if (SuffixStr == "nncv" || SuffixStr == "mlir") {
    (void)nncv::compiler::utils::ImportMlirModuleFromFile(MlirModule, &MlirContext, CurFilePath);

    ///< Below for NNCV
    // Start to lower all
    if (SetLowerTarget.empty() && GenConfigFileOnly.empty()) { return 0; }

    mlir::PassManager pm(MlirModule.get()->getName());

    // ---------------------------------------------------------------------
    //  Middle end. Register Some Pass for optimize and lowering.
    // ---------------------------------------------------------------------
    nncv::pipeline::DnnModelLowering dnnModelLowerPipeline(MlirContext, MlirModule);
    dnnModelLowerPipeline.setWarpC(WarpC.getValue());
    if (SetLowerTarget.getValue() == "HostWParallel") {
      dnnModelLowerPipeline.setGenHostWParallel();
    } else if (SetLowerTarget.getValue() == "HostWoParallel") {
      dnnModelLowerPipeline.setGenHostWoParallel();
    } else if (SetLowerTarget.getValue() == "NVPTX") {
      dnnModelLowerPipeline.setGenNVPTX();
    }
    if (!OutputFilename.getValue().empty()) {
      dnnModelLowerPipeline.setOutputFilePath(OutputFilename.getValue());
    }
    if (!GenConfigFileOnly.getValue().empty()) {
      dnnModelLowerPipeline.setGenConfigFileOnly(true);
      dnnModelLowerPipeline.setGenConfigFilePath(GenConfigFileOnly.getValue());
    } else {
      dnnModelLowerPipeline.setGenConfigFileOnly(false);
    }
    dnnModelLowerPipeline.run();
  } else if (SuffixStr == "nvm") {
    if (!VmMode.getValue()) {
      printf("[ Erro ] The input is .nvm file, but -vm flag for nncv-c is not set\n");
      exit(-1);
    }
    // the code follow is for run aten's llvm ir in jit
    nncv::runner::NncvJit Jit;
    Jit.setFilePath(InputFilename.getValue());
    // Run jit
    if (Jit.run()) {
      exit(0);
    } else {
      exit(-1);
    }
  }
}
