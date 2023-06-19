#ifndef NNCV_COMPILER_TEN_LANG_PARSER_HPP_
#define NNCV_COMPILER_TEN_LANG_PARSER_HPP_

#include "nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserBaseListener.h"

#include "nncv/compiler/Frontend/TenLangAst.hpp"

#include <stack>

using namespace antlrcpp;

enum AutoTenPaserType {
  Antlr = 0,
  Builtin = 1,
};

#ifdef NNCV_ENABLE_ANTLR

namespace nncv {
namespace compiler {
namespace frontend {

class AutoTenListener : public AutoTenV1ParserListener {
  AutoTenListener() : m_Indent(0) {}
  int m_Indent;
  inline void Indent() {
    for (int i = 0; i < m_Indent; i++) std::cout << "    ";
  }

  // stack for listener

  // The context and Symbol Table
  std::string m_CurPakageName;

 public:
  void enterSourceFile(AutoTenV1Parser::SourceFileContext* ctx) override;
  void exitSourceFile(AutoTenV1Parser::SourceFileContext* ctx) override;

  void enterPackageClause(AutoTenV1Parser::PackageClauseContext* ctx) override{};
  void exitPackageClause(AutoTenV1Parser::PackageClauseContext* ctx) override{};

  void enterCompileFlags(AutoTenV1Parser::CompileFlagsContext* ctx) override{};
  void exitCompileFlags(AutoTenV1Parser::CompileFlagsContext* ctx) override{};

  void enterDeclaration(AutoTenV1Parser::DeclarationContext* ctx) override{};
  void exitDeclaration(AutoTenV1Parser::DeclarationContext* ctx) override{};

  void enterTypeDecl(AutoTenV1Parser::TypeDeclContext* ctx) override{};
  void exitTypeDecl(AutoTenV1Parser::TypeDeclContext* ctx) override{};

  void enterTypeSpec(AutoTenV1Parser::TypeSpecContext* ctx) override{};
  void exitTypeSpec(AutoTenV1Parser::TypeSpecContext* ctx) override{};

  void enterType_(AutoTenV1Parser::Type_Context* ctx) override{};
  void exitType_(AutoTenV1Parser::Type_Context* ctx) override{};

  void enterBuiltinType(AutoTenV1Parser::BuiltinTypeContext* ctx) override{};
  void exitBuiltinType(AutoTenV1Parser::BuiltinTypeContext* ctx) override{};

  void enterTypeName(AutoTenV1Parser::TypeNameContext* ctx) override{};
  void exitTypeName(AutoTenV1Parser::TypeNameContext* ctx) override{};

  void enterTypeLit(AutoTenV1Parser::TypeLitContext* ctx) override{};
  void exitTypeLit(AutoTenV1Parser::TypeLitContext* ctx) override{};

  void enterArrayType(AutoTenV1Parser::ArrayTypeContext* ctx) override{};
  void exitArrayType(AutoTenV1Parser::ArrayTypeContext* ctx) override{};

  void enterArrayLength(AutoTenV1Parser::ArrayLengthContext* ctx) override{};
  void exitArrayLength(AutoTenV1Parser::ArrayLengthContext* ctx) override{};

  void enterElementType(AutoTenV1Parser::ElementTypeContext* ctx) override{};
  void exitElementType(AutoTenV1Parser::ElementTypeContext* ctx) override{};

  void enterPointerType(AutoTenV1Parser::PointerTypeContext* ctx) override{};
  void exitPointerType(AutoTenV1Parser::PointerTypeContext* ctx) override{};

  void enterImplType(AutoTenV1Parser::ImplTypeContext* ctx) override{};
  void exitImplType(AutoTenV1Parser::ImplTypeContext* ctx) override{};

  void enterSliceType(AutoTenV1Parser::SliceTypeContext* ctx) override{};
  void exitSliceType(AutoTenV1Parser::SliceTypeContext* ctx) override{};

  void enterMapType(AutoTenV1Parser::MapTypeContext* ctx) override{};
  void exitMapType(AutoTenV1Parser::MapTypeContext* ctx) override{};

  void enterMethodSpec(AutoTenV1Parser::MethodSpecContext* ctx) override{};
  void exitMethodSpec(AutoTenV1Parser::MethodSpecContext* ctx) override{};

  void enterFunctionType(AutoTenV1Parser::FunctionTypeContext* ctx) override{};
  void exitFunctionType(AutoTenV1Parser::FunctionTypeContext* ctx) override{};

  void enterVarDecl(AutoTenV1Parser::VarDeclContext* ctx) override{};
  void exitVarDecl(AutoTenV1Parser::VarDeclContext* ctx) override{};

  void enterVarSpec(AutoTenV1Parser::VarSpecContext* ctx) override{};
  void exitVarSpec(AutoTenV1Parser::VarSpecContext* ctx) override{};

  void enterSignature(AutoTenV1Parser::SignatureContext* ctx) override{};
  void exitSignature(AutoTenV1Parser::SignatureContext* ctx) override{};

  void enterResult(AutoTenV1Parser::ResultContext* ctx) override{};
  void exitResult(AutoTenV1Parser::ResultContext* ctx) override{};

  void enterParameters(AutoTenV1Parser::ParametersContext* ctx) override{};
  void exitParameters(AutoTenV1Parser::ParametersContext* ctx) override{};

  void enterIndex(AutoTenV1Parser::IndexContext* ctx) override{};
  void exitIndex(AutoTenV1Parser::IndexContext* ctx) override{};

  void enterSlice_(AutoTenV1Parser::Slice_Context* ctx) override{};
  void exitSlice_(AutoTenV1Parser::Slice_Context* ctx) override{};

  void enterTypeAssertion(AutoTenV1Parser::TypeAssertionContext* ctx) override{};
  void exitTypeAssertion(AutoTenV1Parser::TypeAssertionContext* ctx) override{};

  void enterArguments(AutoTenV1Parser::ArgumentsContext* ctx) override{};
  void exitArguments(AutoTenV1Parser::ArgumentsContext* ctx) override{};

  void enterMethodExpr(AutoTenV1Parser::MethodExprContext* ctx) override{};
  void exitMethodExpr(AutoTenV1Parser::MethodExprContext* ctx) override{};

  void enterParameterDecl(AutoTenV1Parser::ParameterDeclContext* ctx) override{};
  void exitParameterDecl(AutoTenV1Parser::ParameterDeclContext* ctx) override{};

  void enterExpression(AutoTenV1Parser::ExpressionContext* ctx) override{};
  void exitExpression(AutoTenV1Parser::ExpressionContext* ctx) override{};

  void enterPrimaryExpr(AutoTenV1Parser::PrimaryExprContext* ctx) override{};
  void exitPrimaryExpr(AutoTenV1Parser::PrimaryExprContext* ctx) override{};

  void enterConversion(AutoTenV1Parser::ConversionContext* ctx) override{};
  void exitConversion(AutoTenV1Parser::ConversionContext* ctx) override{};

  void enterNonNamedType(AutoTenV1Parser::NonNamedTypeContext* ctx) override{};
  void exitNonNamedType(AutoTenV1Parser::NonNamedTypeContext* ctx) override{};

  void enterOperand(AutoTenV1Parser::OperandContext* ctx) override{};
  void exitOperand(AutoTenV1Parser::OperandContext* ctx) override{};

  void enterExpressionList(AutoTenV1Parser::ExpressionListContext* ctx) override{};
  void exitExpressionList(AutoTenV1Parser::ExpressionListContext* ctx) override{};

  void enterIdentifierList(AutoTenV1Parser::IdentifierListContext* ctx) override{};
  void exitIdentifierList(AutoTenV1Parser::IdentifierListContext* ctx) override{};

  void enterLiteral(AutoTenV1Parser::LiteralContext* ctx) override{};
  void exitLiteral(AutoTenV1Parser::LiteralContext* ctx) override{};

  void enterBasicLit(AutoTenV1Parser::BasicLitContext* ctx) override{};
  void exitBasicLit(AutoTenV1Parser::BasicLitContext* ctx) override{};

  void enterOperandName(AutoTenV1Parser::OperandNameContext* ctx) override{};
  void exitOperandName(AutoTenV1Parser::OperandNameContext* ctx) override{};

  void enterQualifiedIdent(AutoTenV1Parser::QualifiedIdentContext* ctx) override{};
  void exitQualifiedIdent(AutoTenV1Parser::QualifiedIdentContext* ctx) override{};

  void enterCompositeLit(AutoTenV1Parser::CompositeLitContext* ctx) override{};
  void exitCompositeLit(AutoTenV1Parser::CompositeLitContext* ctx) override{};

  void enterLiteralType(AutoTenV1Parser::LiteralTypeContext* ctx) override{};
  void exitLiteralType(AutoTenV1Parser::LiteralTypeContext* ctx) override{};

  void enterLiteralValue(AutoTenV1Parser::LiteralValueContext* ctx) override{};
  void exitLiteralValue(AutoTenV1Parser::LiteralValueContext* ctx) override{};

  void enterElementList(AutoTenV1Parser::ElementListContext* ctx) override{};
  void exitElementList(AutoTenV1Parser::ElementListContext* ctx) override{};

  void enterKeyedElement(AutoTenV1Parser::KeyedElementContext* ctx) override{};
  void exitKeyedElement(AutoTenV1Parser::KeyedElementContext* ctx) override{};

  void enterKey(AutoTenV1Parser::KeyContext* ctx) override{};
  void exitKey(AutoTenV1Parser::KeyContext* ctx) override{};

  void enterElement(AutoTenV1Parser::ElementContext* ctx) override{};
  void exitElement(AutoTenV1Parser::ElementContext* ctx) override{};

  void enterStructType(AutoTenV1Parser::StructTypeContext* ctx) override{};
  void exitStructType(AutoTenV1Parser::StructTypeContext* ctx) override{};

  void enterFieldDecl(AutoTenV1Parser::FieldDeclContext* ctx) override{};
  void exitFieldDecl(AutoTenV1Parser::FieldDeclContext* ctx) override{};

  void enterEmbeddedField(AutoTenV1Parser::EmbeddedFieldContext* ctx) override{};
  void exitEmbeddedField(AutoTenV1Parser::EmbeddedFieldContext* ctx) override{};

  void enterFunctionLit(AutoTenV1Parser::FunctionLitContext* ctx) override{};
  void exitFunctionLit(AutoTenV1Parser::FunctionLitContext* ctx) override{};

  void enterFunctionDecl(AutoTenV1Parser::FunctionDeclContext* ctx) override{};
  void exitFunctionDecl(AutoTenV1Parser::FunctionDeclContext* ctx) override{};

  void enterBlock(AutoTenV1Parser::BlockContext* ctx) override{};
  void exitBlock(AutoTenV1Parser::BlockContext* ctx) override{};

  void enterStatementList(AutoTenV1Parser::StatementListContext* ctx) override{};
  void exitStatementList(AutoTenV1Parser::StatementListContext* ctx) override{};

  void enterStatement(AutoTenV1Parser::StatementContext* ctx) override{};
  void exitStatement(AutoTenV1Parser::StatementContext* ctx) override{};

  void enterSimpleStmt(AutoTenV1Parser::SimpleStmtContext* ctx) override{};
  void exitSimpleStmt(AutoTenV1Parser::SimpleStmtContext* ctx) override{};

  void enterExpressionStmt(AutoTenV1Parser::ExpressionStmtContext* ctx) override{};
  void exitExpressionStmt(AutoTenV1Parser::ExpressionStmtContext* ctx) override{};

  void enterIncDecStmt(AutoTenV1Parser::IncDecStmtContext* ctx) override{};
  void exitIncDecStmt(AutoTenV1Parser::IncDecStmtContext* ctx) override{};

  void enterAssignment(AutoTenV1Parser::AssignmentContext* ctx) override{};
  void exitAssignment(AutoTenV1Parser::AssignmentContext* ctx) override{};

  void enterAssign_op(AutoTenV1Parser::Assign_opContext* ctx) override{};
  void exitAssign_op(AutoTenV1Parser::Assign_opContext* ctx) override{};

  void enterShortVarDecl(AutoTenV1Parser::ShortVarDeclContext* ctx) override{};
  void exitShortVarDecl(AutoTenV1Parser::ShortVarDeclContext* ctx) override{};

  void enterEmptyStmt(AutoTenV1Parser::EmptyStmtContext* ctx) override{};
  void exitEmptyStmt(AutoTenV1Parser::EmptyStmtContext* ctx) override{};

  void enterLabeledStmt(AutoTenV1Parser::LabeledStmtContext* ctx) override{};
  void exitLabeledStmt(AutoTenV1Parser::LabeledStmtContext* ctx) override{};

  void enterReturnStmt(AutoTenV1Parser::ReturnStmtContext* ctx) override{};
  void exitReturnStmt(AutoTenV1Parser::ReturnStmtContext* ctx) override{};

  void enterBreakStmt(AutoTenV1Parser::BreakStmtContext* ctx) override{};
  void exitBreakStmt(AutoTenV1Parser::BreakStmtContext* ctx) override{};

  void enterContinueStmt(AutoTenV1Parser::ContinueStmtContext* ctx) override{};
  void exitContinueStmt(AutoTenV1Parser::ContinueStmtContext* ctx) override{};

  void enterGotoStmt(AutoTenV1Parser::GotoStmtContext* ctx) override{};
  void exitGotoStmt(AutoTenV1Parser::GotoStmtContext* ctx) override{};

  void enterFallthroughStmt(AutoTenV1Parser::FallthroughStmtContext* ctx) override{};
  void exitFallthroughStmt(AutoTenV1Parser::FallthroughStmtContext* ctx) override{};

  void enterIfStmt(AutoTenV1Parser::IfStmtContext* ctx) override{};
  void exitIfStmt(AutoTenV1Parser::IfStmtContext* ctx) override{};

  void enterSwitchStmt(AutoTenV1Parser::SwitchStmtContext* ctx) override{};
  void exitSwitchStmt(AutoTenV1Parser::SwitchStmtContext* ctx) override{};

  void enterExprSwitchStmt(AutoTenV1Parser::ExprSwitchStmtContext* ctx) override{};
  void exitExprSwitchStmt(AutoTenV1Parser::ExprSwitchStmtContext* ctx) override{};

  void enterExprCaseClause(AutoTenV1Parser::ExprCaseClauseContext* ctx) override{};
  void exitExprCaseClause(AutoTenV1Parser::ExprCaseClauseContext* ctx) override{};

  void enterExprSwitchCase(AutoTenV1Parser::ExprSwitchCaseContext* ctx) override{};
  void exitExprSwitchCase(AutoTenV1Parser::ExprSwitchCaseContext* ctx) override{};

  void enterTypeSwitchStmt(AutoTenV1Parser::TypeSwitchStmtContext* ctx) override{};
  void exitTypeSwitchStmt(AutoTenV1Parser::TypeSwitchStmtContext* ctx) override{};

  void enterTypeSwitchGuard(AutoTenV1Parser::TypeSwitchGuardContext* ctx) override{};
  void exitTypeSwitchGuard(AutoTenV1Parser::TypeSwitchGuardContext* ctx) override{};

  void enterTypeCaseClause(AutoTenV1Parser::TypeCaseClauseContext* ctx) override{};
  void exitTypeCaseClause(AutoTenV1Parser::TypeCaseClauseContext* ctx) override{};

  void enterTypeSwitchCase(AutoTenV1Parser::TypeSwitchCaseContext* ctx) override{};
  void exitTypeSwitchCase(AutoTenV1Parser::TypeSwitchCaseContext* ctx) override{};

  void enterTypeList(AutoTenV1Parser::TypeListContext* ctx) override{};
  void exitTypeList(AutoTenV1Parser::TypeListContext* ctx) override{};

  void enterForStmt(AutoTenV1Parser::ForStmtContext* ctx) override{};
  void exitForStmt(AutoTenV1Parser::ForStmtContext* ctx) override{};

  void enterForClause(AutoTenV1Parser::ForClauseContext* ctx) override{};
  void exitForClause(AutoTenV1Parser::ForClauseContext* ctx) override{};

  void enterWhileStmt(AutoTenV1Parser::WhileStmtContext* ctx) override{};
  void exitWhileStmt(AutoTenV1Parser::WhileStmtContext* ctx) override{};

  void enterDoWhileStmt(AutoTenV1Parser::DoWhileStmtContext* ctx) override{};
  void exitDoWhileStmt(AutoTenV1Parser::DoWhileStmtContext* ctx) override{};

  void enterEos(AutoTenV1Parser::EosContext* ctx) override{};
  void exitEos(AutoTenV1Parser::EosContext* ctx) override{};

  virtual void visitTerminal(antlr4::tree::TerminalNode* node) override{};
  virtual void visitErrorNode(antlr4::tree::ErrorNode* node) override{};
  virtual void enterEveryRule(antlr4::ParserRuleContext* ctx) override{};
  virtual void exitEveryRule(antlr4::ParserRuleContext* ctx) override{};
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