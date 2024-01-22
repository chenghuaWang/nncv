
// Generated from ./AutoTenV1Parser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "AutoTenV1Parser.h"


namespace antlrcpp {

/**
 * This interface defines an abstract listener for a parse tree produced by AutoTenV1Parser.
 */
class  AutoTenV1ParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterSourceFile(AutoTenV1Parser::SourceFileContext *ctx) = 0;
  virtual void exitSourceFile(AutoTenV1Parser::SourceFileContext *ctx) = 0;

  virtual void enterPackageClause(AutoTenV1Parser::PackageClauseContext *ctx) = 0;
  virtual void exitPackageClause(AutoTenV1Parser::PackageClauseContext *ctx) = 0;

  virtual void enterCompileFlags(AutoTenV1Parser::CompileFlagsContext *ctx) = 0;
  virtual void exitCompileFlags(AutoTenV1Parser::CompileFlagsContext *ctx) = 0;

  virtual void enterDeclaration(AutoTenV1Parser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(AutoTenV1Parser::DeclarationContext *ctx) = 0;

  virtual void enterTypeDecl(AutoTenV1Parser::TypeDeclContext *ctx) = 0;
  virtual void exitTypeDecl(AutoTenV1Parser::TypeDeclContext *ctx) = 0;

  virtual void enterTypeSpec(AutoTenV1Parser::TypeSpecContext *ctx) = 0;
  virtual void exitTypeSpec(AutoTenV1Parser::TypeSpecContext *ctx) = 0;

  virtual void enterType_(AutoTenV1Parser::Type_Context *ctx) = 0;
  virtual void exitType_(AutoTenV1Parser::Type_Context *ctx) = 0;

  virtual void enterTensorType(AutoTenV1Parser::TensorTypeContext *ctx) = 0;
  virtual void exitTensorType(AutoTenV1Parser::TensorTypeContext *ctx) = 0;

  virtual void enterBuiltinType(AutoTenV1Parser::BuiltinTypeContext *ctx) = 0;
  virtual void exitBuiltinType(AutoTenV1Parser::BuiltinTypeContext *ctx) = 0;

  virtual void enterTypeName(AutoTenV1Parser::TypeNameContext *ctx) = 0;
  virtual void exitTypeName(AutoTenV1Parser::TypeNameContext *ctx) = 0;

  virtual void enterTypeLit(AutoTenV1Parser::TypeLitContext *ctx) = 0;
  virtual void exitTypeLit(AutoTenV1Parser::TypeLitContext *ctx) = 0;

  virtual void enterArrayType(AutoTenV1Parser::ArrayTypeContext *ctx) = 0;
  virtual void exitArrayType(AutoTenV1Parser::ArrayTypeContext *ctx) = 0;

  virtual void enterArrayLength(AutoTenV1Parser::ArrayLengthContext *ctx) = 0;
  virtual void exitArrayLength(AutoTenV1Parser::ArrayLengthContext *ctx) = 0;

  virtual void enterElementType(AutoTenV1Parser::ElementTypeContext *ctx) = 0;
  virtual void exitElementType(AutoTenV1Parser::ElementTypeContext *ctx) = 0;

  virtual void enterPointerType(AutoTenV1Parser::PointerTypeContext *ctx) = 0;
  virtual void exitPointerType(AutoTenV1Parser::PointerTypeContext *ctx) = 0;

  virtual void enterImplType(AutoTenV1Parser::ImplTypeContext *ctx) = 0;
  virtual void exitImplType(AutoTenV1Parser::ImplTypeContext *ctx) = 0;

  virtual void enterSliceType(AutoTenV1Parser::SliceTypeContext *ctx) = 0;
  virtual void exitSliceType(AutoTenV1Parser::SliceTypeContext *ctx) = 0;

  virtual void enterMapType(AutoTenV1Parser::MapTypeContext *ctx) = 0;
  virtual void exitMapType(AutoTenV1Parser::MapTypeContext *ctx) = 0;

  virtual void enterMethodSpec(AutoTenV1Parser::MethodSpecContext *ctx) = 0;
  virtual void exitMethodSpec(AutoTenV1Parser::MethodSpecContext *ctx) = 0;

  virtual void enterFunctionType(AutoTenV1Parser::FunctionTypeContext *ctx) = 0;
  virtual void exitFunctionType(AutoTenV1Parser::FunctionTypeContext *ctx) = 0;

  virtual void enterVarDecl(AutoTenV1Parser::VarDeclContext *ctx) = 0;
  virtual void exitVarDecl(AutoTenV1Parser::VarDeclContext *ctx) = 0;

  virtual void enterVarSpec(AutoTenV1Parser::VarSpecContext *ctx) = 0;
  virtual void exitVarSpec(AutoTenV1Parser::VarSpecContext *ctx) = 0;

  virtual void enterSignature(AutoTenV1Parser::SignatureContext *ctx) = 0;
  virtual void exitSignature(AutoTenV1Parser::SignatureContext *ctx) = 0;

  virtual void enterResult(AutoTenV1Parser::ResultContext *ctx) = 0;
  virtual void exitResult(AutoTenV1Parser::ResultContext *ctx) = 0;

  virtual void enterParameters(AutoTenV1Parser::ParametersContext *ctx) = 0;
  virtual void exitParameters(AutoTenV1Parser::ParametersContext *ctx) = 0;

  virtual void enterIndex(AutoTenV1Parser::IndexContext *ctx) = 0;
  virtual void exitIndex(AutoTenV1Parser::IndexContext *ctx) = 0;

  virtual void enterSlice_(AutoTenV1Parser::Slice_Context *ctx) = 0;
  virtual void exitSlice_(AutoTenV1Parser::Slice_Context *ctx) = 0;

  virtual void enterTypeAssertion(AutoTenV1Parser::TypeAssertionContext *ctx) = 0;
  virtual void exitTypeAssertion(AutoTenV1Parser::TypeAssertionContext *ctx) = 0;

  virtual void enterArguments(AutoTenV1Parser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(AutoTenV1Parser::ArgumentsContext *ctx) = 0;

  virtual void enterMethodExpr(AutoTenV1Parser::MethodExprContext *ctx) = 0;
  virtual void exitMethodExpr(AutoTenV1Parser::MethodExprContext *ctx) = 0;

  virtual void enterParameterDecl(AutoTenV1Parser::ParameterDeclContext *ctx) = 0;
  virtual void exitParameterDecl(AutoTenV1Parser::ParameterDeclContext *ctx) = 0;

  virtual void enterExpression(AutoTenV1Parser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(AutoTenV1Parser::ExpressionContext *ctx) = 0;

  virtual void enterPrimaryExpr(AutoTenV1Parser::PrimaryExprContext *ctx) = 0;
  virtual void exitPrimaryExpr(AutoTenV1Parser::PrimaryExprContext *ctx) = 0;

  virtual void enterConversion(AutoTenV1Parser::ConversionContext *ctx) = 0;
  virtual void exitConversion(AutoTenV1Parser::ConversionContext *ctx) = 0;

  virtual void enterNonNamedType(AutoTenV1Parser::NonNamedTypeContext *ctx) = 0;
  virtual void exitNonNamedType(AutoTenV1Parser::NonNamedTypeContext *ctx) = 0;

  virtual void enterOperand(AutoTenV1Parser::OperandContext *ctx) = 0;
  virtual void exitOperand(AutoTenV1Parser::OperandContext *ctx) = 0;

  virtual void enterExpressionList(AutoTenV1Parser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(AutoTenV1Parser::ExpressionListContext *ctx) = 0;

  virtual void enterIdentifierList(AutoTenV1Parser::IdentifierListContext *ctx) = 0;
  virtual void exitIdentifierList(AutoTenV1Parser::IdentifierListContext *ctx) = 0;

  virtual void enterLiteral(AutoTenV1Parser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(AutoTenV1Parser::LiteralContext *ctx) = 0;

  virtual void enterBasicLit(AutoTenV1Parser::BasicLitContext *ctx) = 0;
  virtual void exitBasicLit(AutoTenV1Parser::BasicLitContext *ctx) = 0;

  virtual void enterOperandName(AutoTenV1Parser::OperandNameContext *ctx) = 0;
  virtual void exitOperandName(AutoTenV1Parser::OperandNameContext *ctx) = 0;

  virtual void enterQualifiedIdent(AutoTenV1Parser::QualifiedIdentContext *ctx) = 0;
  virtual void exitQualifiedIdent(AutoTenV1Parser::QualifiedIdentContext *ctx) = 0;

  virtual void enterCompositeLit(AutoTenV1Parser::CompositeLitContext *ctx) = 0;
  virtual void exitCompositeLit(AutoTenV1Parser::CompositeLitContext *ctx) = 0;

  virtual void enterLiteralType(AutoTenV1Parser::LiteralTypeContext *ctx) = 0;
  virtual void exitLiteralType(AutoTenV1Parser::LiteralTypeContext *ctx) = 0;

  virtual void enterLiteralValue(AutoTenV1Parser::LiteralValueContext *ctx) = 0;
  virtual void exitLiteralValue(AutoTenV1Parser::LiteralValueContext *ctx) = 0;

  virtual void enterElementList(AutoTenV1Parser::ElementListContext *ctx) = 0;
  virtual void exitElementList(AutoTenV1Parser::ElementListContext *ctx) = 0;

  virtual void enterKeyedElement(AutoTenV1Parser::KeyedElementContext *ctx) = 0;
  virtual void exitKeyedElement(AutoTenV1Parser::KeyedElementContext *ctx) = 0;

  virtual void enterKey(AutoTenV1Parser::KeyContext *ctx) = 0;
  virtual void exitKey(AutoTenV1Parser::KeyContext *ctx) = 0;

  virtual void enterElement(AutoTenV1Parser::ElementContext *ctx) = 0;
  virtual void exitElement(AutoTenV1Parser::ElementContext *ctx) = 0;

  virtual void enterStructType(AutoTenV1Parser::StructTypeContext *ctx) = 0;
  virtual void exitStructType(AutoTenV1Parser::StructTypeContext *ctx) = 0;

  virtual void enterFieldDecl(AutoTenV1Parser::FieldDeclContext *ctx) = 0;
  virtual void exitFieldDecl(AutoTenV1Parser::FieldDeclContext *ctx) = 0;

  virtual void enterEmbeddedField(AutoTenV1Parser::EmbeddedFieldContext *ctx) = 0;
  virtual void exitEmbeddedField(AutoTenV1Parser::EmbeddedFieldContext *ctx) = 0;

  virtual void enterFunctionLit(AutoTenV1Parser::FunctionLitContext *ctx) = 0;
  virtual void exitFunctionLit(AutoTenV1Parser::FunctionLitContext *ctx) = 0;

  virtual void enterFunctionDecl(AutoTenV1Parser::FunctionDeclContext *ctx) = 0;
  virtual void exitFunctionDecl(AutoTenV1Parser::FunctionDeclContext *ctx) = 0;

  virtual void enterBlock(AutoTenV1Parser::BlockContext *ctx) = 0;
  virtual void exitBlock(AutoTenV1Parser::BlockContext *ctx) = 0;

  virtual void enterStatementList(AutoTenV1Parser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(AutoTenV1Parser::StatementListContext *ctx) = 0;

  virtual void enterStatement(AutoTenV1Parser::StatementContext *ctx) = 0;
  virtual void exitStatement(AutoTenV1Parser::StatementContext *ctx) = 0;

  virtual void enterSimpleStmt(AutoTenV1Parser::SimpleStmtContext *ctx) = 0;
  virtual void exitSimpleStmt(AutoTenV1Parser::SimpleStmtContext *ctx) = 0;

  virtual void enterExpressionStmt(AutoTenV1Parser::ExpressionStmtContext *ctx) = 0;
  virtual void exitExpressionStmt(AutoTenV1Parser::ExpressionStmtContext *ctx) = 0;

  virtual void enterIncDecStmt(AutoTenV1Parser::IncDecStmtContext *ctx) = 0;
  virtual void exitIncDecStmt(AutoTenV1Parser::IncDecStmtContext *ctx) = 0;

  virtual void enterAssignment(AutoTenV1Parser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(AutoTenV1Parser::AssignmentContext *ctx) = 0;

  virtual void enterAssign_op(AutoTenV1Parser::Assign_opContext *ctx) = 0;
  virtual void exitAssign_op(AutoTenV1Parser::Assign_opContext *ctx) = 0;

  virtual void enterShortVarDecl(AutoTenV1Parser::ShortVarDeclContext *ctx) = 0;
  virtual void exitShortVarDecl(AutoTenV1Parser::ShortVarDeclContext *ctx) = 0;

  virtual void enterEmptyStmt(AutoTenV1Parser::EmptyStmtContext *ctx) = 0;
  virtual void exitEmptyStmt(AutoTenV1Parser::EmptyStmtContext *ctx) = 0;

  virtual void enterLabeledStmt(AutoTenV1Parser::LabeledStmtContext *ctx) = 0;
  virtual void exitLabeledStmt(AutoTenV1Parser::LabeledStmtContext *ctx) = 0;

  virtual void enterReturnStmt(AutoTenV1Parser::ReturnStmtContext *ctx) = 0;
  virtual void exitReturnStmt(AutoTenV1Parser::ReturnStmtContext *ctx) = 0;

  virtual void enterBreakStmt(AutoTenV1Parser::BreakStmtContext *ctx) = 0;
  virtual void exitBreakStmt(AutoTenV1Parser::BreakStmtContext *ctx) = 0;

  virtual void enterContinueStmt(AutoTenV1Parser::ContinueStmtContext *ctx) = 0;
  virtual void exitContinueStmt(AutoTenV1Parser::ContinueStmtContext *ctx) = 0;

  virtual void enterGotoStmt(AutoTenV1Parser::GotoStmtContext *ctx) = 0;
  virtual void exitGotoStmt(AutoTenV1Parser::GotoStmtContext *ctx) = 0;

  virtual void enterFallthroughStmt(AutoTenV1Parser::FallthroughStmtContext *ctx) = 0;
  virtual void exitFallthroughStmt(AutoTenV1Parser::FallthroughStmtContext *ctx) = 0;

  virtual void enterIfStmt(AutoTenV1Parser::IfStmtContext *ctx) = 0;
  virtual void exitIfStmt(AutoTenV1Parser::IfStmtContext *ctx) = 0;

  virtual void enterSwitchStmt(AutoTenV1Parser::SwitchStmtContext *ctx) = 0;
  virtual void exitSwitchStmt(AutoTenV1Parser::SwitchStmtContext *ctx) = 0;

  virtual void enterExprSwitchStmt(AutoTenV1Parser::ExprSwitchStmtContext *ctx) = 0;
  virtual void exitExprSwitchStmt(AutoTenV1Parser::ExprSwitchStmtContext *ctx) = 0;

  virtual void enterExprCaseClause(AutoTenV1Parser::ExprCaseClauseContext *ctx) = 0;
  virtual void exitExprCaseClause(AutoTenV1Parser::ExprCaseClauseContext *ctx) = 0;

  virtual void enterExprSwitchCase(AutoTenV1Parser::ExprSwitchCaseContext *ctx) = 0;
  virtual void exitExprSwitchCase(AutoTenV1Parser::ExprSwitchCaseContext *ctx) = 0;

  virtual void enterTypeSwitchStmt(AutoTenV1Parser::TypeSwitchStmtContext *ctx) = 0;
  virtual void exitTypeSwitchStmt(AutoTenV1Parser::TypeSwitchStmtContext *ctx) = 0;

  virtual void enterTypeSwitchGuard(AutoTenV1Parser::TypeSwitchGuardContext *ctx) = 0;
  virtual void exitTypeSwitchGuard(AutoTenV1Parser::TypeSwitchGuardContext *ctx) = 0;

  virtual void enterTypeCaseClause(AutoTenV1Parser::TypeCaseClauseContext *ctx) = 0;
  virtual void exitTypeCaseClause(AutoTenV1Parser::TypeCaseClauseContext *ctx) = 0;

  virtual void enterTypeSwitchCase(AutoTenV1Parser::TypeSwitchCaseContext *ctx) = 0;
  virtual void exitTypeSwitchCase(AutoTenV1Parser::TypeSwitchCaseContext *ctx) = 0;

  virtual void enterTypeList(AutoTenV1Parser::TypeListContext *ctx) = 0;
  virtual void exitTypeList(AutoTenV1Parser::TypeListContext *ctx) = 0;

  virtual void enterForStmt(AutoTenV1Parser::ForStmtContext *ctx) = 0;
  virtual void exitForStmt(AutoTenV1Parser::ForStmtContext *ctx) = 0;

  virtual void enterPforStmt(AutoTenV1Parser::PforStmtContext *ctx) = 0;
  virtual void exitPforStmt(AutoTenV1Parser::PforStmtContext *ctx) = 0;

  virtual void enterForClause(AutoTenV1Parser::ForClauseContext *ctx) = 0;
  virtual void exitForClause(AutoTenV1Parser::ForClauseContext *ctx) = 0;

  virtual void enterWhileStmt(AutoTenV1Parser::WhileStmtContext *ctx) = 0;
  virtual void exitWhileStmt(AutoTenV1Parser::WhileStmtContext *ctx) = 0;

  virtual void enterDoWhileStmt(AutoTenV1Parser::DoWhileStmtContext *ctx) = 0;
  virtual void exitDoWhileStmt(AutoTenV1Parser::DoWhileStmtContext *ctx) = 0;

  virtual void enterEos(AutoTenV1Parser::EosContext *ctx) = 0;
  virtual void exitEos(AutoTenV1Parser::EosContext *ctx) = 0;


};

}  // namespace antlrcpp
