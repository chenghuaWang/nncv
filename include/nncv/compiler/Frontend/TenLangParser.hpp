#ifndef NNCV_COMPILER_TEN_LANG_PARSER_HPP_
#define NNCV_COMPILER_TEN_LANG_PARSER_HPP_

#include "AutoTenV1Parser.h"
#include "AutoTenV1ParserBaseVisitor.h"
#include "AutoTenV1ParserListener.h"
#include "AutoTenV1Lexer.h"

#include "nncv/compiler/Frontend/TenLangAst.hpp"
#include "nncv/compiler/Utils/SymbolRef.hpp"

#include "mlir/IR/Attributes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Verifier.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/ScopedHashTable.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/Support/raw_ostream.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"

#include "nncv/compiler/Frontend/CodeGenCtx.hpp"

using namespace antlrcpp;

enum AutoTenParserType {
  Antlr = 0,
  Builtin = 1,
};

#ifdef NNCV_ENABLE_ANTLR

namespace nncv {
namespace compiler {
namespace frontend {

void insertAllIoMethods(mlir::ModuleOp& module, mlir::OpBuilder& builder, mlir::Location& loc);
void buildIoPrintCallOp(mlir::ModuleOp& module, mlir::OpBuilder& builder, mlir::Location& loc,
                        mlir::ValueRange& vr);
mlir::Value buildClockCallOp(mlir::ModuleOp& module, mlir::OpBuilder& builder, mlir::Location& loc,
                             mlir::ValueRange& vr);

class VisitorParserReturn;

class AutoTen2MlirVisitor : public AutoTenV1ParserBaseVisitor {
 public:
  AutoTen2MlirVisitor(const std::string& fileName, mlir::MLIRContext& context)
      : m_Lexer(nullptr), m_OpBuilder(&context), m_FileName(fileName) {
    m_TheModule = mlir::ModuleOp::create(m_OpBuilder.getUnknownLoc());
    m_curSymbolTable = utils::AtenSymbolTable::getInstance().getSymbolRefOfModule(fileName);
    m_parseState = parseState::kNone;
  }

  inline mlir::ModuleOp getModule() { return m_TheModule; }

 private:
  enum class parseState { kTypeDecl, kNone };

  parseState m_parseState;
  std::string m_curParsingTypeDeclName;  ///< record current parsing Type Decl Name

  ParserState Ps;

 private:
  AutoTenV1Lexer m_Lexer;
  mlir::ModuleOp m_TheModule;
  mlir::OpBuilder m_OpBuilder;
  std::string m_FileName;

  utils::AtenSymbolRef* m_curSymbolTable;

  inline mlir::Location loc(int line, int row) {
    return mlir::FileLineColLoc::get(m_OpBuilder.getStringAttr(m_FileName), line, row);
  }

  // Utilities functions
  llvm::SmallVector<mlir::Value, 4> castAtenArithToMlirArith(
      llvm::SmallVector<mlir::Value, 4>& valueArry);

  VisitorParserReturn parseSlice_(AutoTenV1Parser::Slice_Context* ctx, VisitorParserReturn& value);

  VisitorParserReturn parseIndex_(AutoTenV1Parser::IndexContext* ctx, VisitorParserReturn& value);

  VisitorParserReturn parseArgument(AutoTenV1Parser::ArgumentsContext* ctx,
                                    VisitorParserReturn& value);

  inline llvm::SmallVector<mlir::Value, 2> autoTypeCastSolver(mlir::Value& v1, mlir::Value& v2,
                                                              int32_t castType);

  //===----------------------------------------------------------------------===//
  // Override visitor functions in the AutoTenV1ParserVisitor
  //===----------------------------------------------------------------------===//
  std::any visitSourceFile(AutoTenV1Parser::SourceFileContext* ctx) override;

  std::any visitPackageClause(AutoTenV1Parser::PackageClauseContext* ctx) override;

  std::any visitImportClasue(AutoTenV1Parser::ImportClasueContext* ctx) override;

  std::any visitVarDecl(AutoTenV1Parser::VarDeclContext* ctx) override;

  std::any visitTypeDecl(AutoTenV1Parser::TypeDeclContext* ctx) override;

  std::any visitExpressionList(AutoTenV1Parser::ExpressionListContext* ctx) override;

  std::any visitExpression(AutoTenV1Parser::ExpressionContext* ctx) override;

  std::any visitPrimaryExpr(AutoTenV1Parser::PrimaryExprContext* ctx) override;

  std::any visitOperand(AutoTenV1Parser::OperandContext* ctx) override;

  std::any visitLiteral(AutoTenV1Parser::LiteralContext* ctx) override;

  std::any visitBasicLit(AutoTenV1Parser::BasicLitContext* ctx) override;

  std::any visitOperandName(AutoTenV1Parser::OperandNameContext* ctx) override;

  std::any visitIdentifierList(AutoTenV1Parser::IdentifierListContext* ctx) override;

  std::any visitQualifiedIdent(AutoTenV1Parser::QualifiedIdentContext* ctx) override;

  std::any visitBlock(AutoTenV1Parser::BlockContext* ctx) override;

  //===----------------------------------------------------------------------===//
  // Process All Statements
  //===----------------------------------------------------------------------===//
  std::any visitStatement(AutoTenV1Parser::StatementContext* ctx) override;

  std::any visitReturnStmt(AutoTenV1Parser::ReturnStmtContext* ctx) override;

  std::any visitSimpleStmt(AutoTenV1Parser::SimpleStmtContext* ctx) override;

  std::any visitAssignment(AutoTenV1Parser::AssignmentContext* ctx) override;

  std::any visitIfStmt(AutoTenV1Parser::IfStmtContext* ctx) override;

  std::any visitBreakStmt(AutoTenV1Parser::BreakStmtContext* ctx) override;

  std::any visitForStmt(AutoTenV1Parser::ForStmtContext* ctx) override;

  std::any visitPforStmt(AutoTenV1Parser::PforStmtContext* ctx) override;

  std::any visitShortVarDecl(AutoTenV1Parser::ShortVarDeclContext* ctx) override;

  std::any visitIncDecStmt(AutoTenV1Parser::IncDecStmtContext* ctx) override;

  std::any visitWhileStmt(AutoTenV1Parser::WhileStmtContext* ctx) override;

  //===----------------------------------------------------------------------===//
  // Process types and atrributes
  //===----------------------------------------------------------------------===//
  std::any visitDeclaration(AutoTenV1Parser::DeclarationContext* ctx) override;

  std::any visitType_(AutoTenV1Parser::Type_Context* ctx) override;

  std::any visitTypeLit(AutoTenV1Parser::TypeLitContext* ctx) override;

  std::any visitTypeName(AutoTenV1Parser::TypeNameContext* ctx) override;

  std::any visitArrayType(AutoTenV1Parser::ArrayTypeContext* ctx) override;

  std::any visitStructType(AutoTenV1Parser::StructTypeContext* ctx) override;

  std::any visitPointerType(AutoTenV1Parser::PointerTypeContext* ctx) override;

  std::any visitMapType(AutoTenV1Parser::MapTypeContext* ctx) override;

  std::any visitTensorType(AutoTenV1Parser::TensorTypeContext* ctx) override;

  //===----------------------------------------------------------------------===//
  // Method to process function declarations
  //===----------------------------------------------------------------------===//
  std::any visitFunctionDecl(AutoTenV1Parser::FunctionDeclContext* ctx) override;

  std::any visitSignature(AutoTenV1Parser::SignatureContext* ctx) override;

  std::any visitParameters(AutoTenV1Parser::ParametersContext* ctx) override;

  //===----------------------------------------------------------------------===//
  // Method to process type, mactch type or cast type.
  //===----------------------------------------------------------------------===//
};

class AutoTenListener : public AutoTenV1ParserListener {
  int m_Indent;
  inline void Indent() {
    for (int i = 0; i < m_Indent; i++) std::cout << "    ";
  }

  // stack for listener

  // The context and Symbol Table
  std::string m_CurPakageName;

 public:
  AutoTenListener() : m_Indent(0) {}

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
      : m_Type(AutoTenParserType::Antlr), m_AntlrParser(_at) {}

  void dump();

 private:
  AutoTenParserType m_Type;
  AutoTenV1Parser& m_AntlrParser;
};

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv

namespace nncv {
namespace compiler {
namespace frontend {

//===----------------------------------------------------------------------===//
// Helper class for Antlr visitor models' return.
//
// This class is a wrapper of visitor pattern's return, will make judge the return
// type less suffer.
//===----------------------------------------------------------------------===//
class VisitorParserReturn;
enum class VisitorParserReturnType {
  kMlirValue,
  kMlirType,

  kStringLiteral,
  kIntLiteral, /*all int literal will return as int64*/
  kFloatLiteral,
  kBooleanLiteral,

  kStringLiteralWMlirValue,
  kIntLiteralWMlirValue, /*all int literal will return as int64*/
  kFloatLiteralWMlirValue,
  kBooleanLiteralWMlirValue,

  kAtenTypeDeclare,
  kAttribute,
  kParametersAndReturn, /*for function decl and function call*/
  kNone,
};

enum class VisitorParserAtenTypeDeclType {
  kInt1,
  kInt8,
  kInt16,
  kInt32,
  kInt64,
  kFloat32,
  kFloat64,
  kBool,
  kTensor,
  kChar,
  kString,
  kMap,
  kSlice,
  kStruct,
  kFunc,
  kArray,
  kPtr,
};

struct VisitorParserAtenTypeDecl {
  VisitorParserAtenTypeDecl(
      std::pair<mlir::Type, std::vector<VisitorParserReturn>> p,
      VisitorParserAtenTypeDeclType type = VisitorParserAtenTypeDeclType::kTensor)
      : tensorPayload(p), type(type) {}

  std::pair<mlir::Type, std::vector<VisitorParserReturn>> tensorPayload;  ///< for tensor use only
  std::pair<mlir::Type, uint32_t> arrayPayload;                           ///< for array use only
  mlir::Type ptrPayload;                                                  ///< for Ptr use only
  VisitorParserAtenTypeDeclType type;
};

class VisitorParserReturn {
 public:
  VisitorParserReturn() : type(VisitorParserReturnType::kNone){};
  VisitorParserReturn(const std::string& str)
      : value(str), type(VisitorParserReturnType::kStringLiteral) {}
  VisitorParserReturn(int64_t value) : value(value), type(VisitorParserReturnType::kIntLiteral) {}
  VisitorParserReturn(mlir::Value value, const std::string& str)
      : value(value), strLiteral(str), type(VisitorParserReturnType::kStringLiteralWMlirValue) {}
  VisitorParserReturn(mlir::Value& value)
      : value(value), type(VisitorParserReturnType::kMlirValue) {}
  VisitorParserReturn(mlir::Type& value) : value(value), type(VisitorParserReturnType::kMlirType) {}
  VisitorParserReturn(VisitorParserAtenTypeDecl value)
      : value(value), type(VisitorParserReturnType::kAtenTypeDeclare) {}
  VisitorParserReturn(mlir::Value mlirValue, int64_t value)
      : value(mlirValue), intLiteral(value), type(VisitorParserReturnType::kIntLiteralWMlirValue) {}
  VisitorParserReturn(mlir::Attribute& attr)
      : value(attr), type(VisitorParserReturnType::kAttribute) {}
  VisitorParserReturn(FuncParameterAndReturn& attr)
      : value(attr), type(VisitorParserReturnType::kParametersAndReturn) {}

 public:
  inline bool isa(VisitorParserReturnType t) { return type == t; }
  inline VisitorParserReturnType getType() { return type; };

  template<typename T>
  inline T getValue() {
    return std::any_cast<T>(value);
  };

  inline std::any getRawValue() { return value; }

 private:
  std::any value;
  std::string strLiteral;
  int64_t intLiteral;
  double floatLiteral;
  VisitorParserReturnType type;
};

#define HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(width_n)                                               \
  if (!theVarSpec->Assign()) {                                                                     \
    /*if var declaration has no assign. Then attach a empty value to it. 0 by default.*/           \
    mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(                                \
        location,                                                                                  \
        mlir::aten::IntAttr::get(mlir::aten::IntType::get(m_OpBuilder.getContext(),                \
                                                          /*width*/ width_n, /*isSigned*/ true),   \
                                 0));                                                              \
    mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));                                   \
    return VisitorParserReturn(value);                                                             \
  } else {                                                                                         \
    /*                                                                                             \
    // expression has value;                                                                       \
    // 1) expression may be `var a int8 = 1;` then, in expression a constant builder will be       \
    // called in expression.                                                                       \
    // 2) expression may be `var a int8 = c + d;` then, in expression a add builder will be        \
    // called in expression.                                                                       \
    */                                                                                             \
    /* get the expression value */                                                                 \
    auto exprAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->expressionList()));        \
    /* if this expr return a mlir::Value. We just need to record this value;*/                     \
    if (exprAny.isa(VisitorParserReturnType::kMlirValue)) {                                        \
      auto v = exprAny.getValue<mlir::Value>();                                                    \
      if (v.getType().cast<mlir::aten::IntType>().getWidth() != width_n) { /*FIXME throw error*/   \
      }                                                                                            \
      mlir::failed(m_SymbolTable.declare(symbolName, v, ctx));                                     \
      return VisitorParserReturn(v);                                                               \
    }                                                                                              \
    /*if the return is just a int literal. We use `ConstantOp` to create one*/                     \
    if (exprAny.isa(VisitorParserReturnType::kIntLiteral)) {                                       \
      mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(                              \
          location,                                                                                \
          mlir::aten::IntAttr::get(mlir::aten::IntType::get(m_OpBuilder.getContext(),              \
                                                            /*width*/ width_n, /*isSigned*/ true), \
                                   exprAny.getValue<int64_t>()));                                  \
      mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));                                 \
      return VisitorParserReturn(value);                                                           \
    }                                                                                              \
    /* FIXME: throw error*/                                                                        \
    return VisitorParserReturn();                                                                  \
  }

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