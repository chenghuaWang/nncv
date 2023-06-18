#include "nncv/compiler/Frontend/TenLangLexer.hpp"
#include "nncv/compiler/Frontend/TenLangParser.hpp"
#include "nncv/compiler/Pipeline/Frontend.hpp"

#include <fstream>

namespace nncv {
namespace compiler {
namespace pipeline {

void FrontendPipeline::Do() {
#ifdef NNCV_ENABLE_ANTLR
  auto ino = std::ifstream("");

  if (ino.is_open()) {
    // TODO
  }

  antlr4::ANTLRInputStream input(ino);
  AutoTenV1Lexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  AutoTenV1Parser parser(&tokens);
  antlr4::tree::ParseTree* tree = parser.sourceFile();
  frontend::AutoTenVisitor ir;
  ir.visit(tree);
  ino.close();
  // TODO pass MLIR in AutoTenVisitor to next pipeline.
#endif
}

}  // namespace pipeline
}  // namespace compiler
}  // namespace nncv