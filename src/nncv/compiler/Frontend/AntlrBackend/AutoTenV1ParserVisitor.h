
// Generated from ./AutoTenV1Parser.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "AutoTenV1Parser.h"


namespace antlrcpp {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by AutoTenV1Parser.
 */
class  AutoTenV1ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by AutoTenV1Parser.
   */
    virtual std::any visitSourceFile(AutoTenV1Parser::SourceFileContext *context) = 0;

    virtual std::any visitPackageClause(AutoTenV1Parser::PackageClauseContext *context) = 0;

    virtual std::any visitCompileFlags(AutoTenV1Parser::CompileFlagsContext *context) = 0;

    virtual std::any visitDeclaration(AutoTenV1Parser::DeclarationContext *context) = 0;

    virtual std::any visitTypeDecl(AutoTenV1Parser::TypeDeclContext *context) = 0;

    virtual std::any visitTypeSpec(AutoTenV1Parser::TypeSpecContext *context) = 0;

    virtual std::any visitType_(AutoTenV1Parser::Type_Context *context) = 0;

    virtual std::any visitTensorType(AutoTenV1Parser::TensorTypeContext *context) = 0;

    virtual std::any visitBuiltinType(AutoTenV1Parser::BuiltinTypeContext *context) = 0;

    virtual std::any visitTypeName(AutoTenV1Parser::TypeNameContext *context) = 0;

    virtual std::any visitTypeLit(AutoTenV1Parser::TypeLitContext *context) = 0;

    virtual std::any visitArrayType(AutoTenV1Parser::ArrayTypeContext *context) = 0;

    virtual std::any visitArrayLength(AutoTenV1Parser::ArrayLengthContext *context) = 0;

    virtual std::any visitElementType(AutoTenV1Parser::ElementTypeContext *context) = 0;

    virtual std::any visitPointerType(AutoTenV1Parser::PointerTypeContext *context) = 0;

    virtual std::any visitImplType(AutoTenV1Parser::ImplTypeContext *context) = 0;

    virtual std::any visitSliceType(AutoTenV1Parser::SliceTypeContext *context) = 0;

    virtual std::any visitMapType(AutoTenV1Parser::MapTypeContext *context) = 0;

    virtual std::any visitMethodSpec(AutoTenV1Parser::MethodSpecContext *context) = 0;

    virtual std::any visitFunctionType(AutoTenV1Parser::FunctionTypeContext *context) = 0;

    virtual std::any visitVarDecl(AutoTenV1Parser::VarDeclContext *context) = 0;

    virtual std::any visitVarSpec(AutoTenV1Parser::VarSpecContext *context) = 0;

    virtual std::any visitSignature(AutoTenV1Parser::SignatureContext *context) = 0;

    virtual std::any visitResult(AutoTenV1Parser::ResultContext *context) = 0;

    virtual std::any visitParameters(AutoTenV1Parser::ParametersContext *context) = 0;

    virtual std::any visitIndex(AutoTenV1Parser::IndexContext *context) = 0;

    virtual std::any visitSlice_(AutoTenV1Parser::Slice_Context *context) = 0;

    virtual std::any visitTypeAssertion(AutoTenV1Parser::TypeAssertionContext *context) = 0;

    virtual std::any visitArguments(AutoTenV1Parser::ArgumentsContext *context) = 0;

    virtual std::any visitMethodExpr(AutoTenV1Parser::MethodExprContext *context) = 0;

    virtual std::any visitParameterDecl(AutoTenV1Parser::ParameterDeclContext *context) = 0;

    virtual std::any visitExpression(AutoTenV1Parser::ExpressionContext *context) = 0;

    virtual std::any visitPrimaryExpr(AutoTenV1Parser::PrimaryExprContext *context) = 0;

    virtual std::any visitConversion(AutoTenV1Parser::ConversionContext *context) = 0;

    virtual std::any visitNonNamedType(AutoTenV1Parser::NonNamedTypeContext *context) = 0;

    virtual std::any visitOperand(AutoTenV1Parser::OperandContext *context) = 0;

    virtual std::any visitExpressionList(AutoTenV1Parser::ExpressionListContext *context) = 0;

    virtual std::any visitIdentifierList(AutoTenV1Parser::IdentifierListContext *context) = 0;

    virtual std::any visitLiteral(AutoTenV1Parser::LiteralContext *context) = 0;

    virtual std::any visitBasicLit(AutoTenV1Parser::BasicLitContext *context) = 0;

    virtual std::any visitOperandName(AutoTenV1Parser::OperandNameContext *context) = 0;

    virtual std::any visitQualifiedIdent(AutoTenV1Parser::QualifiedIdentContext *context) = 0;

    virtual std::any visitCompositeLit(AutoTenV1Parser::CompositeLitContext *context) = 0;

    virtual std::any visitLiteralType(AutoTenV1Parser::LiteralTypeContext *context) = 0;

    virtual std::any visitLiteralValue(AutoTenV1Parser::LiteralValueContext *context) = 0;

    virtual std::any visitElementList(AutoTenV1Parser::ElementListContext *context) = 0;

    virtual std::any visitKeyedElement(AutoTenV1Parser::KeyedElementContext *context) = 0;

    virtual std::any visitKey(AutoTenV1Parser::KeyContext *context) = 0;

    virtual std::any visitElement(AutoTenV1Parser::ElementContext *context) = 0;

    virtual std::any visitStructType(AutoTenV1Parser::StructTypeContext *context) = 0;

    virtual std::any visitFieldDecl(AutoTenV1Parser::FieldDeclContext *context) = 0;

    virtual std::any visitEmbeddedField(AutoTenV1Parser::EmbeddedFieldContext *context) = 0;

    virtual std::any visitFunctionLit(AutoTenV1Parser::FunctionLitContext *context) = 0;

    virtual std::any visitFunctionDecl(AutoTenV1Parser::FunctionDeclContext *context) = 0;

    virtual std::any visitBlock(AutoTenV1Parser::BlockContext *context) = 0;

    virtual std::any visitStatementList(AutoTenV1Parser::StatementListContext *context) = 0;

    virtual std::any visitStatement(AutoTenV1Parser::StatementContext *context) = 0;

    virtual std::any visitSimpleStmt(AutoTenV1Parser::SimpleStmtContext *context) = 0;

    virtual std::any visitExpressionStmt(AutoTenV1Parser::ExpressionStmtContext *context) = 0;

    virtual std::any visitIncDecStmt(AutoTenV1Parser::IncDecStmtContext *context) = 0;

    virtual std::any visitAssignment(AutoTenV1Parser::AssignmentContext *context) = 0;

    virtual std::any visitAssign_op(AutoTenV1Parser::Assign_opContext *context) = 0;

    virtual std::any visitShortVarDecl(AutoTenV1Parser::ShortVarDeclContext *context) = 0;

    virtual std::any visitEmptyStmt(AutoTenV1Parser::EmptyStmtContext *context) = 0;

    virtual std::any visitLabeledStmt(AutoTenV1Parser::LabeledStmtContext *context) = 0;

    virtual std::any visitReturnStmt(AutoTenV1Parser::ReturnStmtContext *context) = 0;

    virtual std::any visitBreakStmt(AutoTenV1Parser::BreakStmtContext *context) = 0;

    virtual std::any visitContinueStmt(AutoTenV1Parser::ContinueStmtContext *context) = 0;

    virtual std::any visitGotoStmt(AutoTenV1Parser::GotoStmtContext *context) = 0;

    virtual std::any visitFallthroughStmt(AutoTenV1Parser::FallthroughStmtContext *context) = 0;

    virtual std::any visitIfStmt(AutoTenV1Parser::IfStmtContext *context) = 0;

    virtual std::any visitSwitchStmt(AutoTenV1Parser::SwitchStmtContext *context) = 0;

    virtual std::any visitExprSwitchStmt(AutoTenV1Parser::ExprSwitchStmtContext *context) = 0;

    virtual std::any visitExprCaseClause(AutoTenV1Parser::ExprCaseClauseContext *context) = 0;

    virtual std::any visitExprSwitchCase(AutoTenV1Parser::ExprSwitchCaseContext *context) = 0;

    virtual std::any visitTypeSwitchStmt(AutoTenV1Parser::TypeSwitchStmtContext *context) = 0;

    virtual std::any visitTypeSwitchGuard(AutoTenV1Parser::TypeSwitchGuardContext *context) = 0;

    virtual std::any visitTypeCaseClause(AutoTenV1Parser::TypeCaseClauseContext *context) = 0;

    virtual std::any visitTypeSwitchCase(AutoTenV1Parser::TypeSwitchCaseContext *context) = 0;

    virtual std::any visitTypeList(AutoTenV1Parser::TypeListContext *context) = 0;

    virtual std::any visitForStmt(AutoTenV1Parser::ForStmtContext *context) = 0;

    virtual std::any visitPforStmt(AutoTenV1Parser::PforStmtContext *context) = 0;

    virtual std::any visitForClause(AutoTenV1Parser::ForClauseContext *context) = 0;

    virtual std::any visitWhileStmt(AutoTenV1Parser::WhileStmtContext *context) = 0;

    virtual std::any visitDoWhileStmt(AutoTenV1Parser::DoWhileStmtContext *context) = 0;

    virtual std::any visitEos(AutoTenV1Parser::EosContext *context) = 0;


};

}  // namespace antlrcpp
