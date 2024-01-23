#include "nncv/compiler/Pipeline/Frontend.hpp"
#include "nncv/compiler/Conversion/AtenToMlir/AtenToMlir.h"
#include "nncv/compiler/Dialects/AutoTen/Transforms/Passes.hpp"

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
    if (m_showCst) { std::cout << tree->toStringTree(true) << "\n"; }
    if (m_dumpMlir) {
      frontend::AutoTen2MlirVisitor visitor(m_CurrentFilePath, m_Context);
      visitor.visit(tree);
      m_Module = visitor.getModule();

      if (mlir::verify(m_Module->getOperation()).failed()) {
        printf("[ Erro ] MLIR Self verify failed\n");
        exit(-1);
      }

      // Two stage Lowering
      mlir::PassManager pm(m_Module.get()->getName());
      // stage 1
      {
        // Aten-lang High level optimization

        mlir::nncv::aten::createAtenLangHighLevelOptimizePipeline(pm);

        pm.addPass(mlir::nncv::createConvertAtenToMlirPass());
        if (mlir::failed(pm.run(*m_Module))) {
          printf("[ Erro ] When doing aten-lang [high level optimization; aten to mlir lowering] "
                 "at stage 2\n");
          exit(-1);
        }
      }
      // stage 2
      {
        // Closure
        pm.clear();
        pm.addPass(mlir::nncv::createConvertAtenToMlirPass(true));
        pm.run(*m_Module);
        // if (mlir::failed()) {
        //   printf("[ Erro ] When doing aten-lang [high level optimization; aten to mlir lowering]
        //   "
        //          "at stage 2\n");
        //   exit(-1);
        // }
      }
      m_Module->dump();
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