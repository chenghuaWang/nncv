#include "nncv/compiler/Pipeline/Frontend.hpp"
#include "mlir/Conversion/BufferizationToMemRef/BufferizationToMemRef.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Transforms/Passes.h"
#include "nncv/compiler/Conversion/AtenToMlir/AtenToMlir.h"
#include "nncv/compiler/Dialects/AutoTen/Transforms/Passes.hpp"
#include "nncv/compiler/Utils/MlirIo.hpp"

#include <fstream>

namespace nncv {
namespace compiler {
namespace pipeline {

void FrontendPipeline::run() {
  // judge the file type
  std::string SuffixStr = m_CurrentFilePath.substr(m_CurrentFilePath.find_last_of('.') + 1);
  if (SuffixStr == "aten") {
#ifdef NNCV_ENABLE_ANTLR
    auto ino = std::ifstream(m_CurrentFilePath);

    if (!ino.good()) {
      printf("[ Erro ] Cant't Open File %s\n", m_CurrentFilePath.c_str());
      exit(-1);
    }

    antlr4::ANTLRInputStream input(ino);
    AutoTenV1Lexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    AutoTenV1Parser parser(&tokens);
    antlrcpp::AutoTenV1Parser::SourceFileContext* tree = parser.sourceFile();
    ///< Show CST
    if (m_showCst) {
      std::cout << tree->toStringTree(true) << "\n";
      exit(0);
    }

    frontend::AutoTen2MlirVisitor visitor(m_CurrentFilePath, m_Context);
    visitor.visit(tree);
    m_Module = visitor.getModule();

    if (mlir::verify(m_Module->getOperation()).failed()) {
      printf("[ Erro ] MLIR Self verify failed\n");
      exit(-1);
    }

    mlir::PassManager pm(m_Module.get()->getName());
    // High level aten ir optimization
    {
      mlir::nncv::aten::createAtenLangHighLevelOptimizePipeline(pm);
      pm.addPass(mlir::createCanonicalizerPass());
      pm.addPass(mlir::createCSEPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] When doing aten-lang [high level optimization]\n");
        exit(-1);
      }
    }

    ///< Show Aten IR
    if (m_genAtenIR) {
      if (!m_OutputFilePath.empty()) {
        compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
      } else {
        m_Module->dump();
      }
      exit(0);
    }

    // 3 stage Lowering
    // stage 1
    {
      // Aten-lang High level optimization
      pm.clear();
      pm.addPass(mlir::nncv::createConvertAtenToMlirPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] When doing aten-lang [high level optimization; aten to mlir lowering] "
               "at stage 1(partial to mlir pass)\n");
        exit(-1);
      }
    }
    // stage 2
    {
      // Closure
      pm.clear();
      pm.addPass(mlir::nncv::createConvertAtenToMlirPass(true));
      pm.addPass(mlir::createCanonicalizerPass());
      pm.addPass(mlir::createCSEPass());

      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] When doing aten-lang [high level optimization; aten to mlir lowering]"
               "at stage 2(all to mlir pass)\n");
        exit(-1);
      }
    }
    // final fine tunning pass
    {
      pm.clear();
      pm.addPass(mlir::nncv::aten::createEliminateRedundantLoadStoreForScfConditionalPass());
      pm.addPass(mlir::createLoopInvariantCodeMotionPass());
      pm.addPass(mlir::createCanonicalizerPass());
      pm.addPass(mlir::createCSEPass());
      if (mlir::failed(pm.run(*m_Module))) {
        printf("[ Erro ] When doing aten-lang [high level optimization; aten to mlir lowering]"
               "at stage 3(final fine tunning pass)\n");
        exit(-1);
      }
    }
    // deallocation
    // {
    //   pm.clear();
    //   pm.addNestedPass<mlir::func::FuncOp>(mlir::bufferization::createBufferDeallocationPass());
    //   if (mlir::failed(pm.run(*m_Module))) {
    //     printf("[ Erro ] When doing aten-lang [high level optimization; aten to mlir lowering]"
    //            "at auto deallocation\n");
    //     exit(-1);
    //   }
    // }
    if (m_genBuiltinMlir) {
      if (!m_OutputFilePath.empty()) {
        compiler::utils::SaveMlirModuleToFile(m_Module, m_OutputFilePath);
      } else {
        m_Module->dump();
      }
      exit(0);
    }
    ino.close();
#endif
  } else {
    printf("[ Erro ] Can't Open File with %s Suffix.(Support .aten/.nncv)\n", SuffixStr.c_str());
    exit(-1);
  }
}

}  // namespace pipeline
}  // namespace compiler
}  // namespace nncv