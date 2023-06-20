#ifdef NNCV_ENABLE_ANTLR

#include "nncv/compiler/Frontend/TenLangParser.hpp"

namespace nncv {
namespace compiler {
namespace frontend {

//===----------------------------------------------------------------------===//
// The visitor is for generating MLIR form CST(concrete synatic tree) directly.
//
// Before start to implement this mlir builder. Read the material form MLIR
// official site first:
// 1. MLIR Lang Ref
//    https://mlir.llvm.org/docs/LangRef/
// 2. Defining Dialect Attributes and Types
//    https://mlir.llvm.org/docs/DefiningDialects/AttributesAndTypes/
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// sourceFile:
//	packageClause eos ((functionDecl | declaration) eos)* EOF;
//
// packageClause: At Package Assign StringLiteral;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitSourceFile(AutoTenV1Parser::SourceFileContext* ctx) {
  return visitChildren(ctx);
}

std::any AutoTen2MlirVisitor::visitStructType(AutoTenV1Parser::StructTypeContext* ctx) {
  return visitChildren(ctx);
}

//===----------------------------------------------------------------------===//
// varDecl: Var (varSpec | LeftParen (varSpec eos)* RightParen);
//
// varSpec:
//	identifierList (
//		type_ (Assign expressionList)?
//		| Assign expressionList
//	);
// Note: !!! This syntactic is from Golang. Here, Aten just support single var
// declaration. Such as `var a int = 1;`. `var a, b int = 1, 2;` is not support.
// var a Tensor<1, 2, 3, int>;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitVarDecl(AutoTenV1Parser::VarDeclContext* ctx) {
  return visitChildren(ctx);
}

//===----------------------------------------------------------------------===//
// The listener is for generating AST.
//===----------------------------------------------------------------------===//

void AutoTenListener::enterSourceFile(AutoTenV1Parser::SourceFileContext* ctx) {}

void AutoTenListener::exitSourceFile(AutoTenV1Parser::SourceFileContext* ctx) {}

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