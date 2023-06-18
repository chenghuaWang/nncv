#ifndef NNCV_COMPILER_TEN_LANG_PARSER_HPP_
#define NNCV_COMPILER_TEN_LANG_PARSER_HPP_

#include "nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserBaseVisitor.h"

using namespace antlrcpp;

enum AutoTenPaserType {
  Antlr = 0,
  Builtin = 1,
};

#ifdef NNCV_ENABLE_ANTLR

namespace nncv {
namespace compiler {
namespace frontend {

/**
 * @brief The auto tensor visiotr is only for antlr.
 *
 */
class AutoTenVisitor : public AutoTenV1ParserBaseVisitor {
 public:
  virtual std::any visitSourceFile(AutoTenV1Parser::SourceFileContext* ctx) override;

 private:
  // TODO symbol table / method-struct table / some global flags.
};

/**
 * @brief If AutoTenParser is using antlr backend, there is no need to generate a AST. The Parse
 * tree of Antlr is a superset of AST. And the infomation is enough for generating MLIR.
 *
 */
class AutoTenParser {
 public:
  explicit AutoTenParser(AutoTenV1Parser& _at)
      : m_Type(AutoTenPaserType::Antlr), m_AntlrParser(_at) {}

  void dump();

 private:
  AutoTenPaserType m_Type;
  AutoTenV1Parser& m_AntlrParser;
};

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv

#else

namespace nncv {
namespace compiler {
namespace fronted {}
}  // namespace compiler
}  // namespace nncv

#endif

#endif  //! NNCV_COMPILER_TEN_LANG_PARSER_HPP_