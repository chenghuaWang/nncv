
// Generated from ./AutoTenV1Parser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "AutoTenV1ParserVisitor.h"


namespace antlrcpp {

/**
 * This class provides an empty implementation of AutoTenV1ParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  AutoTenV1ParserBaseVisitor : public AutoTenV1ParserVisitor {
public:

  virtual std::any visitSourceFile(AutoTenV1Parser::SourceFileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportClasue(AutoTenV1Parser::ImportClasueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackageClause(AutoTenV1Parser::PackageClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompileFlags(AutoTenV1Parser::CompileFlagsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(AutoTenV1Parser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeDecl(AutoTenV1Parser::TypeDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSpec(AutoTenV1Parser::TypeSpecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_(AutoTenV1Parser::Type_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTensorType(AutoTenV1Parser::TensorTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBuiltinType(AutoTenV1Parser::BuiltinTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeName(AutoTenV1Parser::TypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeLit(AutoTenV1Parser::TypeLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(AutoTenV1Parser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayLength(AutoTenV1Parser::ArrayLengthContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementType(AutoTenV1Parser::ElementTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPointerType(AutoTenV1Parser::PointerTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImplType(AutoTenV1Parser::ImplTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSliceType(AutoTenV1Parser::SliceTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMapType(AutoTenV1Parser::MapTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodSpec(AutoTenV1Parser::MethodSpecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionType(AutoTenV1Parser::FunctionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(AutoTenV1Parser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarSpec(AutoTenV1Parser::VarSpecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSignature(AutoTenV1Parser::SignatureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitResult(AutoTenV1Parser::ResultContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameters(AutoTenV1Parser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndex(AutoTenV1Parser::IndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSlice_(AutoTenV1Parser::Slice_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeAssertion(AutoTenV1Parser::TypeAssertionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(AutoTenV1Parser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodExpr(AutoTenV1Parser::MethodExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterDecl(AutoTenV1Parser::ParameterDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(AutoTenV1Parser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpr(AutoTenV1Parser::PrimaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConversion(AutoTenV1Parser::ConversionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNonNamedType(AutoTenV1Parser::NonNamedTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperand(AutoTenV1Parser::OperandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionList(AutoTenV1Parser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierList(AutoTenV1Parser::IdentifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(AutoTenV1Parser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicLit(AutoTenV1Parser::BasicLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperandName(AutoTenV1Parser::OperandNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualifiedIdent(AutoTenV1Parser::QualifiedIdentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompositeLit(AutoTenV1Parser::CompositeLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralType(AutoTenV1Parser::LiteralTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralValue(AutoTenV1Parser::LiteralValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementList(AutoTenV1Parser::ElementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyedElement(AutoTenV1Parser::KeyedElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKey(AutoTenV1Parser::KeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement(AutoTenV1Parser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructType(AutoTenV1Parser::StructTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFieldDecl(AutoTenV1Parser::FieldDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmbeddedField(AutoTenV1Parser::EmbeddedFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionLit(AutoTenV1Parser::FunctionLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDecl(AutoTenV1Parser::FunctionDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(AutoTenV1Parser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementList(AutoTenV1Parser::StatementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(AutoTenV1Parser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleStmt(AutoTenV1Parser::SimpleStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStmt(AutoTenV1Parser::ExpressionStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIncDecStmt(AutoTenV1Parser::IncDecStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(AutoTenV1Parser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign_op(AutoTenV1Parser::Assign_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShortVarDecl(AutoTenV1Parser::ShortVarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyStmt(AutoTenV1Parser::EmptyStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLabeledStmt(AutoTenV1Parser::LabeledStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStmt(AutoTenV1Parser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStmt(AutoTenV1Parser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStmt(AutoTenV1Parser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGotoStmt(AutoTenV1Parser::GotoStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFallthroughStmt(AutoTenV1Parser::FallthroughStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(AutoTenV1Parser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSwitchStmt(AutoTenV1Parser::SwitchStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprSwitchStmt(AutoTenV1Parser::ExprSwitchStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprCaseClause(AutoTenV1Parser::ExprCaseClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprSwitchCase(AutoTenV1Parser::ExprSwitchCaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSwitchStmt(AutoTenV1Parser::TypeSwitchStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSwitchGuard(AutoTenV1Parser::TypeSwitchGuardContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeCaseClause(AutoTenV1Parser::TypeCaseClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSwitchCase(AutoTenV1Parser::TypeSwitchCaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeList(AutoTenV1Parser::TypeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStmt(AutoTenV1Parser::ForStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPforStmt(AutoTenV1Parser::PforStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPforClause(AutoTenV1Parser::PforClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForClause(AutoTenV1Parser::ForClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStmt(AutoTenV1Parser::WhileStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDoWhileStmt(AutoTenV1Parser::DoWhileStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEos(AutoTenV1Parser::EosContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace antlrcpp
