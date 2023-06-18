#ifdef NNCV_ENABLE_ANTLR

#include "nncv/compiler/Frontend/TenLangParser.hpp"

namespace nncv {
namespace compiler {
namespace frontend {

std::any AutoTenVisitor::visitSourceFile(AutoTenV1Parser::SourceFileContext* ctx) {
  visit(ctx->packageClause());
}

void AutoTenParser::dump() {}

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv

#else

namespace nncv {
namespace compiler {
namespace frontend {}
}  // namespace compiler
}  // namespace nncv

#endif