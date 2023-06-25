#include "nncv/compiler/Pipeline/Frontend.hpp"

#include <fstream>

namespace nncv {
namespace compiler {
namespace pipeline {

void FrontendPipeline::Do() {
#ifdef NNCV_ENABLE_ANTLR
  auto ino = std::ifstream(m_CurrentFilePath);

  if (!ino.good()) {
    // TODO
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
    m_Module->dump();
  }
  ino.close();
#endif
}

}  // namespace pipeline
}  // namespace compiler
}  // namespace nncv