
// Generated from ../AutoTenV1Parser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "AutoTenV1ParserListener.h"


namespace antlrcpp {

/**
 * This class provides an empty implementation of AutoTenV1ParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  AutoTenV1ParserBaseListener : public AutoTenV1ParserListener {
public:

  virtual void enterSourceFile(AutoTenV1Parser::SourceFileContext * /*ctx*/) override { }
  virtual void exitSourceFile(AutoTenV1Parser::SourceFileContext * /*ctx*/) override { }

  virtual void enterPackageClause(AutoTenV1Parser::PackageClauseContext * /*ctx*/) override { }
  virtual void exitPackageClause(AutoTenV1Parser::PackageClauseContext * /*ctx*/) override { }

  virtual void enterCompileFlags(AutoTenV1Parser::CompileFlagsContext * /*ctx*/) override { }
  virtual void exitCompileFlags(AutoTenV1Parser::CompileFlagsContext * /*ctx*/) override { }

  virtual void enterDeclaration(AutoTenV1Parser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(AutoTenV1Parser::DeclarationContext * /*ctx*/) override { }

  virtual void enterTypeDecl(AutoTenV1Parser::TypeDeclContext * /*ctx*/) override { }
  virtual void exitTypeDecl(AutoTenV1Parser::TypeDeclContext * /*ctx*/) override { }

  virtual void enterTypeSpec(AutoTenV1Parser::TypeSpecContext * /*ctx*/) override { }
  virtual void exitTypeSpec(AutoTenV1Parser::TypeSpecContext * /*ctx*/) override { }

  virtual void enterType_(AutoTenV1Parser::Type_Context * /*ctx*/) override { }
  virtual void exitType_(AutoTenV1Parser::Type_Context * /*ctx*/) override { }

  virtual void enterBuiltinType(AutoTenV1Parser::BuiltinTypeContext * /*ctx*/) override { }
  virtual void exitBuiltinType(AutoTenV1Parser::BuiltinTypeContext * /*ctx*/) override { }

  virtual void enterTypeName(AutoTenV1Parser::TypeNameContext * /*ctx*/) override { }
  virtual void exitTypeName(AutoTenV1Parser::TypeNameContext * /*ctx*/) override { }

  virtual void enterTypeLit(AutoTenV1Parser::TypeLitContext * /*ctx*/) override { }
  virtual void exitTypeLit(AutoTenV1Parser::TypeLitContext * /*ctx*/) override { }

  virtual void enterArrayType(AutoTenV1Parser::ArrayTypeContext * /*ctx*/) override { }
  virtual void exitArrayType(AutoTenV1Parser::ArrayTypeContext * /*ctx*/) override { }

  virtual void enterArrayLength(AutoTenV1Parser::ArrayLengthContext * /*ctx*/) override { }
  virtual void exitArrayLength(AutoTenV1Parser::ArrayLengthContext * /*ctx*/) override { }

  virtual void enterElementType(AutoTenV1Parser::ElementTypeContext * /*ctx*/) override { }
  virtual void exitElementType(AutoTenV1Parser::ElementTypeContext * /*ctx*/) override { }

  virtual void enterPointerType(AutoTenV1Parser::PointerTypeContext * /*ctx*/) override { }
  virtual void exitPointerType(AutoTenV1Parser::PointerTypeContext * /*ctx*/) override { }

  virtual void enterImplType(AutoTenV1Parser::ImplTypeContext * /*ctx*/) override { }
  virtual void exitImplType(AutoTenV1Parser::ImplTypeContext * /*ctx*/) override { }

  virtual void enterSliceType(AutoTenV1Parser::SliceTypeContext * /*ctx*/) override { }
  virtual void exitSliceType(AutoTenV1Parser::SliceTypeContext * /*ctx*/) override { }

  virtual void enterMapType(AutoTenV1Parser::MapTypeContext * /*ctx*/) override { }
  virtual void exitMapType(AutoTenV1Parser::MapTypeContext * /*ctx*/) override { }

  virtual void enterMethodSpec(AutoTenV1Parser::MethodSpecContext * /*ctx*/) override { }
  virtual void exitMethodSpec(AutoTenV1Parser::MethodSpecContext * /*ctx*/) override { }

  virtual void enterFunctionType(AutoTenV1Parser::FunctionTypeContext * /*ctx*/) override { }
  virtual void exitFunctionType(AutoTenV1Parser::FunctionTypeContext * /*ctx*/) override { }

  virtual void enterVarDecl(AutoTenV1Parser::VarDeclContext * /*ctx*/) override { }
  virtual void exitVarDecl(AutoTenV1Parser::VarDeclContext * /*ctx*/) override { }

  virtual void enterVarSpec(AutoTenV1Parser::VarSpecContext * /*ctx*/) override { }
  virtual void exitVarSpec(AutoTenV1Parser::VarSpecContext * /*ctx*/) override { }

  virtual void enterSignature(AutoTenV1Parser::SignatureContext * /*ctx*/) override { }
  virtual void exitSignature(AutoTenV1Parser::SignatureContext * /*ctx*/) override { }

  virtual void enterResult(AutoTenV1Parser::ResultContext * /*ctx*/) override { }
  virtual void exitResult(AutoTenV1Parser::ResultContext * /*ctx*/) override { }

  virtual void enterParameters(AutoTenV1Parser::ParametersContext * /*ctx*/) override { }
  virtual void exitParameters(AutoTenV1Parser::ParametersContext * /*ctx*/) override { }

  virtual void enterIndex(AutoTenV1Parser::IndexContext * /*ctx*/) override { }
  virtual void exitIndex(AutoTenV1Parser::IndexContext * /*ctx*/) override { }

  virtual void enterSlice_(AutoTenV1Parser::Slice_Context * /*ctx*/) override { }
  virtual void exitSlice_(AutoTenV1Parser::Slice_Context * /*ctx*/) override { }

  virtual void enterTypeAssertion(AutoTenV1Parser::TypeAssertionContext * /*ctx*/) override { }
  virtual void exitTypeAssertion(AutoTenV1Parser::TypeAssertionContext * /*ctx*/) override { }

  virtual void enterArguments(AutoTenV1Parser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(AutoTenV1Parser::ArgumentsContext * /*ctx*/) override { }

  virtual void enterMethodExpr(AutoTenV1Parser::MethodExprContext * /*ctx*/) override { }
  virtual void exitMethodExpr(AutoTenV1Parser::MethodExprContext * /*ctx*/) override { }

  virtual void enterParameterDecl(AutoTenV1Parser::ParameterDeclContext * /*ctx*/) override { }
  virtual void exitParameterDecl(AutoTenV1Parser::ParameterDeclContext * /*ctx*/) override { }

  virtual void enterExpression(AutoTenV1Parser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(AutoTenV1Parser::ExpressionContext * /*ctx*/) override { }

  virtual void enterPrimaryExpr(AutoTenV1Parser::PrimaryExprContext * /*ctx*/) override { }
  virtual void exitPrimaryExpr(AutoTenV1Parser::PrimaryExprContext * /*ctx*/) override { }

  virtual void enterConversion(AutoTenV1Parser::ConversionContext * /*ctx*/) override { }
  virtual void exitConversion(AutoTenV1Parser::ConversionContext * /*ctx*/) override { }

  virtual void enterNonNamedType(AutoTenV1Parser::NonNamedTypeContext * /*ctx*/) override { }
  virtual void exitNonNamedType(AutoTenV1Parser::NonNamedTypeContext * /*ctx*/) override { }

  virtual void enterOperand(AutoTenV1Parser::OperandContext * /*ctx*/) override { }
  virtual void exitOperand(AutoTenV1Parser::OperandContext * /*ctx*/) override { }

  virtual void enterExpressionList(AutoTenV1Parser::ExpressionListContext * /*ctx*/) override { }
  virtual void exitExpressionList(AutoTenV1Parser::ExpressionListContext * /*ctx*/) override { }

  virtual void enterIdentifierList(AutoTenV1Parser::IdentifierListContext * /*ctx*/) override { }
  virtual void exitIdentifierList(AutoTenV1Parser::IdentifierListContext * /*ctx*/) override { }

  virtual void enterLiteral(AutoTenV1Parser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(AutoTenV1Parser::LiteralContext * /*ctx*/) override { }

  virtual void enterBasicLit(AutoTenV1Parser::BasicLitContext * /*ctx*/) override { }
  virtual void exitBasicLit(AutoTenV1Parser::BasicLitContext * /*ctx*/) override { }

  virtual void enterOperandName(AutoTenV1Parser::OperandNameContext * /*ctx*/) override { }
  virtual void exitOperandName(AutoTenV1Parser::OperandNameContext * /*ctx*/) override { }

  virtual void enterQualifiedIdent(AutoTenV1Parser::QualifiedIdentContext * /*ctx*/) override { }
  virtual void exitQualifiedIdent(AutoTenV1Parser::QualifiedIdentContext * /*ctx*/) override { }

  virtual void enterCompositeLit(AutoTenV1Parser::CompositeLitContext * /*ctx*/) override { }
  virtual void exitCompositeLit(AutoTenV1Parser::CompositeLitContext * /*ctx*/) override { }

  virtual void enterLiteralType(AutoTenV1Parser::LiteralTypeContext * /*ctx*/) override { }
  virtual void exitLiteralType(AutoTenV1Parser::LiteralTypeContext * /*ctx*/) override { }

  virtual void enterLiteralValue(AutoTenV1Parser::LiteralValueContext * /*ctx*/) override { }
  virtual void exitLiteralValue(AutoTenV1Parser::LiteralValueContext * /*ctx*/) override { }

  virtual void enterElementList(AutoTenV1Parser::ElementListContext * /*ctx*/) override { }
  virtual void exitElementList(AutoTenV1Parser::ElementListContext * /*ctx*/) override { }

  virtual void enterKeyedElement(AutoTenV1Parser::KeyedElementContext * /*ctx*/) override { }
  virtual void exitKeyedElement(AutoTenV1Parser::KeyedElementContext * /*ctx*/) override { }

  virtual void enterKey(AutoTenV1Parser::KeyContext * /*ctx*/) override { }
  virtual void exitKey(AutoTenV1Parser::KeyContext * /*ctx*/) override { }

  virtual void enterElement(AutoTenV1Parser::ElementContext * /*ctx*/) override { }
  virtual void exitElement(AutoTenV1Parser::ElementContext * /*ctx*/) override { }

  virtual void enterStructType(AutoTenV1Parser::StructTypeContext * /*ctx*/) override { }
  virtual void exitStructType(AutoTenV1Parser::StructTypeContext * /*ctx*/) override { }

  virtual void enterFieldDecl(AutoTenV1Parser::FieldDeclContext * /*ctx*/) override { }
  virtual void exitFieldDecl(AutoTenV1Parser::FieldDeclContext * /*ctx*/) override { }

  virtual void enterEmbeddedField(AutoTenV1Parser::EmbeddedFieldContext * /*ctx*/) override { }
  virtual void exitEmbeddedField(AutoTenV1Parser::EmbeddedFieldContext * /*ctx*/) override { }

  virtual void enterFunctionLit(AutoTenV1Parser::FunctionLitContext * /*ctx*/) override { }
  virtual void exitFunctionLit(AutoTenV1Parser::FunctionLitContext * /*ctx*/) override { }

  virtual void enterFunctionDecl(AutoTenV1Parser::FunctionDeclContext * /*ctx*/) override { }
  virtual void exitFunctionDecl(AutoTenV1Parser::FunctionDeclContext * /*ctx*/) override { }

  virtual void enterBlock(AutoTenV1Parser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(AutoTenV1Parser::BlockContext * /*ctx*/) override { }

  virtual void enterStatementList(AutoTenV1Parser::StatementListContext * /*ctx*/) override { }
  virtual void exitStatementList(AutoTenV1Parser::StatementListContext * /*ctx*/) override { }

  virtual void enterStatement(AutoTenV1Parser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(AutoTenV1Parser::StatementContext * /*ctx*/) override { }

  virtual void enterSimpleStmt(AutoTenV1Parser::SimpleStmtContext * /*ctx*/) override { }
  virtual void exitSimpleStmt(AutoTenV1Parser::SimpleStmtContext * /*ctx*/) override { }

  virtual void enterExpressionStmt(AutoTenV1Parser::ExpressionStmtContext * /*ctx*/) override { }
  virtual void exitExpressionStmt(AutoTenV1Parser::ExpressionStmtContext * /*ctx*/) override { }

  virtual void enterIncDecStmt(AutoTenV1Parser::IncDecStmtContext * /*ctx*/) override { }
  virtual void exitIncDecStmt(AutoTenV1Parser::IncDecStmtContext * /*ctx*/) override { }

  virtual void enterAssignment(AutoTenV1Parser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(AutoTenV1Parser::AssignmentContext * /*ctx*/) override { }

  virtual void enterAssign_op(AutoTenV1Parser::Assign_opContext * /*ctx*/) override { }
  virtual void exitAssign_op(AutoTenV1Parser::Assign_opContext * /*ctx*/) override { }

  virtual void enterShortVarDecl(AutoTenV1Parser::ShortVarDeclContext * /*ctx*/) override { }
  virtual void exitShortVarDecl(AutoTenV1Parser::ShortVarDeclContext * /*ctx*/) override { }

  virtual void enterEmptyStmt(AutoTenV1Parser::EmptyStmtContext * /*ctx*/) override { }
  virtual void exitEmptyStmt(AutoTenV1Parser::EmptyStmtContext * /*ctx*/) override { }

  virtual void enterLabeledStmt(AutoTenV1Parser::LabeledStmtContext * /*ctx*/) override { }
  virtual void exitLabeledStmt(AutoTenV1Parser::LabeledStmtContext * /*ctx*/) override { }

  virtual void enterReturnStmt(AutoTenV1Parser::ReturnStmtContext * /*ctx*/) override { }
  virtual void exitReturnStmt(AutoTenV1Parser::ReturnStmtContext * /*ctx*/) override { }

  virtual void enterBreakStmt(AutoTenV1Parser::BreakStmtContext * /*ctx*/) override { }
  virtual void exitBreakStmt(AutoTenV1Parser::BreakStmtContext * /*ctx*/) override { }

  virtual void enterContinueStmt(AutoTenV1Parser::ContinueStmtContext * /*ctx*/) override { }
  virtual void exitContinueStmt(AutoTenV1Parser::ContinueStmtContext * /*ctx*/) override { }

  virtual void enterGotoStmt(AutoTenV1Parser::GotoStmtContext * /*ctx*/) override { }
  virtual void exitGotoStmt(AutoTenV1Parser::GotoStmtContext * /*ctx*/) override { }

  virtual void enterFallthroughStmt(AutoTenV1Parser::FallthroughStmtContext * /*ctx*/) override { }
  virtual void exitFallthroughStmt(AutoTenV1Parser::FallthroughStmtContext * /*ctx*/) override { }

  virtual void enterIfStmt(AutoTenV1Parser::IfStmtContext * /*ctx*/) override { }
  virtual void exitIfStmt(AutoTenV1Parser::IfStmtContext * /*ctx*/) override { }

  virtual void enterSwitchStmt(AutoTenV1Parser::SwitchStmtContext * /*ctx*/) override { }
  virtual void exitSwitchStmt(AutoTenV1Parser::SwitchStmtContext * /*ctx*/) override { }

  virtual void enterExprSwitchStmt(AutoTenV1Parser::ExprSwitchStmtContext * /*ctx*/) override { }
  virtual void exitExprSwitchStmt(AutoTenV1Parser::ExprSwitchStmtContext * /*ctx*/) override { }

  virtual void enterExprCaseClause(AutoTenV1Parser::ExprCaseClauseContext * /*ctx*/) override { }
  virtual void exitExprCaseClause(AutoTenV1Parser::ExprCaseClauseContext * /*ctx*/) override { }

  virtual void enterExprSwitchCase(AutoTenV1Parser::ExprSwitchCaseContext * /*ctx*/) override { }
  virtual void exitExprSwitchCase(AutoTenV1Parser::ExprSwitchCaseContext * /*ctx*/) override { }

  virtual void enterTypeSwitchStmt(AutoTenV1Parser::TypeSwitchStmtContext * /*ctx*/) override { }
  virtual void exitTypeSwitchStmt(AutoTenV1Parser::TypeSwitchStmtContext * /*ctx*/) override { }

  virtual void enterTypeSwitchGuard(AutoTenV1Parser::TypeSwitchGuardContext * /*ctx*/) override { }
  virtual void exitTypeSwitchGuard(AutoTenV1Parser::TypeSwitchGuardContext * /*ctx*/) override { }

  virtual void enterTypeCaseClause(AutoTenV1Parser::TypeCaseClauseContext * /*ctx*/) override { }
  virtual void exitTypeCaseClause(AutoTenV1Parser::TypeCaseClauseContext * /*ctx*/) override { }

  virtual void enterTypeSwitchCase(AutoTenV1Parser::TypeSwitchCaseContext * /*ctx*/) override { }
  virtual void exitTypeSwitchCase(AutoTenV1Parser::TypeSwitchCaseContext * /*ctx*/) override { }

  virtual void enterTypeList(AutoTenV1Parser::TypeListContext * /*ctx*/) override { }
  virtual void exitTypeList(AutoTenV1Parser::TypeListContext * /*ctx*/) override { }

  virtual void enterForStmt(AutoTenV1Parser::ForStmtContext * /*ctx*/) override { }
  virtual void exitForStmt(AutoTenV1Parser::ForStmtContext * /*ctx*/) override { }

  virtual void enterForClause(AutoTenV1Parser::ForClauseContext * /*ctx*/) override { }
  virtual void exitForClause(AutoTenV1Parser::ForClauseContext * /*ctx*/) override { }

  virtual void enterWhileStmt(AutoTenV1Parser::WhileStmtContext * /*ctx*/) override { }
  virtual void exitWhileStmt(AutoTenV1Parser::WhileStmtContext * /*ctx*/) override { }

  virtual void enterDoWhileStmt(AutoTenV1Parser::DoWhileStmtContext * /*ctx*/) override { }
  virtual void exitDoWhileStmt(AutoTenV1Parser::DoWhileStmtContext * /*ctx*/) override { }

  virtual void enterEos(AutoTenV1Parser::EosContext * /*ctx*/) override { }
  virtual void exitEos(AutoTenV1Parser::EosContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace antlrcpp
