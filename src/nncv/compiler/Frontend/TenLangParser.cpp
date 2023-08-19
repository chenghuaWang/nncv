#include "nncv/compiler/Dialects/AutoTen/IR/AtenAttrs.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"
#ifdef NNCV_ENABLE_ANTLR

#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"

#include "nncv/compiler/Frontend/TenLangParser.hpp"
#include "nncv/compiler/Utils/CliFormatOutput.hpp"

#include "nncv/compiler/Frontend/CodeGenCtx.hpp"

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
  visit(ctx->packageClause());
  auto functionDeclCtxs = ctx->functionDecl();
  auto declarationCtxs = ctx->declaration();
  for (auto& item : functionDeclCtxs) { visit(item); }
  for (auto& item : declarationCtxs) { visit(item); }
  // TODO
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// functionDecl: compileFlags* Public? Function Identifier signature block?;
// compileFlags:
// At Identifier (.Identifier)* (
// 	Assign (True_ | False_ | expression)
// )?;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitFunctionDecl(AutoTenV1Parser::FunctionDeclContext* ctx) {
  // eats and load all compile flags to func decl.
  auto compileFlagsCtxs = ctx->compileFlags();
  nncv::compiler::frontend::FuncCompilerFlag funcFlags;
  for (auto& item : compileFlagsCtxs) {
    auto identifier = item->Identifier();
    // gather key string.
    std::string sig;
    for (auto& ids : identifier) { sig += ids->getText(); }

    // gather value
    if (item->True_()) {
      if (!funcFlags.setFlagsKV(sig, true)) {
        // TODO emit error.
      }
    } else if (item->False_()) {
      if (!funcFlags.setFlagsKV(sig, false)) {
        // TODO emit error.
      }
    } else {
      // TODO
    }
  }
}

//===----------------------------------------------------------------------===//
// packageClause: At Package Assign StringLiteral;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitPackageClause(AutoTenV1Parser::PackageClauseContext* ctx) {
  std::string pkgName = ctx->StringLiteral()->toString();
  // change the module name in mlir to package name.
  m_TheModule.setName("pk_" + pkgName);
  // create a symbol table for the package(module or to say).
  if (utils::AtenSymbolTable::getInstance()->getSymbolRefOfModule(pkgName) == nullptr) {
    utils::AtenSymbolTable::getInstance()->createSymbolRefOfModule(pkgName);
  }
  return VisitorParserReturn();
}

std::any AutoTen2MlirVisitor::visitStructType(AutoTenV1Parser::StructTypeContext* ctx) {
  // TODO
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
//
// When a var is defined. It will be add to symbol table(global or region). The
// region symbol table is block based(such as function, if, while, case)
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitVarDecl(AutoTenV1Parser::VarDeclContext* ctx) {
  auto varSpec = ctx->varSpec();

  // check var spec blocks is 1 or not
  if (varSpec.size() != 1) {
    utils::CliFormatOutput::ErrorAt(
        m_FileName, ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
        "varSpec.size() != 1. nncv-c synatic only support single variable specifier, such as `var "
        "a int32;`. The [LeftParen (varSpec eos)* RightParen] pattern is not support yet.");
  }
  auto theVarSpec = varSpec[0];

  // get the symbol name in identifier list.
  auto symbolNameAny = std::any_cast<VisitorParserReturn>(
      visit(theVarSpec->identifierList()));  // TODO identifier list on working
  std::string symbolName;
  if (symbolNameAny.isa(VisitorParserReturnType::kStringLiteral)) {
    symbolName = symbolNameAny.getValue<std::string>();
  } else {
    // FIXME: throw error at location
  }

  // get the identifier list's position
  mlir::Location location = loc(theVarSpec->identifierList()->getStart()->getLine(),
                                theVarSpec->identifierList()->getStart()->getCharPositionInLine());

  // build values.
  auto atvAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->type_()));

  if (!atvAny.isa(VisitorParserReturnType::kAtenTypeDeclare)) {
    // FIXME: throw error
  }
  auto atv = atvAny.getValue<VisitorParserAtenTypeDecl>();
  switch (atv.type) {
    case VisitorParserAtenTypeDeclType::kInt8: {
      HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(8)
    }
    case VisitorParserAtenTypeDeclType::kInt16: {
      HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(16)
    }
    case VisitorParserAtenTypeDeclType::kInt32: {
      HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(32)
    }
    case VisitorParserAtenTypeDeclType::kInt64: {
      HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(64);
    }
    case VisitorParserAtenTypeDeclType::kFloat32: {
      if (!theVarSpec->Assign()) {
        mlir::Value value =
            m_OpBuilder.create<mlir::aten::ConstantOp>(location, m_OpBuilder.getF32FloatAttr(0.f));
        mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
        return VisitorParserReturn(value);
      } else {
        auto exprAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->expressionList()));
        /* if this expr return a mlir::Value. We just need to record this value;*/
        if (exprAny.isa(VisitorParserReturnType::kMlirValue)) {
          auto v = exprAny.getValue<mlir::Value>();

          // if value's type is mismatch with Float32
          // TODO do cast.

          mlir::failed(m_SymbolTable.declare(symbolName, v, ctx));
          return VisitorParserReturn(v);
        }
        /*if the return is just a int literal. We use `ConstantOp` to create one*/
        if (exprAny.isa(VisitorParserReturnType::kFloatLiteral)
            || exprAny.isa(VisitorParserReturnType::kIntLiteral)) {
          float f = 0.f;
          if (exprAny.isa(VisitorParserReturnType::kFloatLiteral)) {
            f = exprAny.getValue<float>();
          } else if (exprAny.isa(VisitorParserReturnType::kIntLiteral)) {
            f = exprAny.getValue<int64_t>();
          }
          mlir::Value value =
              m_OpBuilder.create<mlir::aten::ConstantOp>(location, m_OpBuilder.getF32FloatAttr(f));
          mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
          return VisitorParserReturn(value);
        }
        /* FIXME: throw error*/
        return VisitorParserReturn();
      }
    }
    case VisitorParserAtenTypeDeclType::kFloat64: {
      if (!theVarSpec->Assign()) {
        mlir::Value value =
            m_OpBuilder.create<mlir::aten::ConstantOp>(location, m_OpBuilder.getF64FloatAttr(0.f));
        mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
        return VisitorParserReturn(value);
      } else {
        auto exprAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->expressionList()));
        /* if this expr return a mlir::Value. We just need to record this value;*/
        if (exprAny.isa(VisitorParserReturnType::kMlirValue)) {
          auto v = exprAny.getValue<mlir::Value>();

          // if value's type is mismatch with Float64
          // TODO do cast.

          mlir::failed(m_SymbolTable.declare(symbolName, v, ctx));
          return VisitorParserReturn(v);
        }
        /*if the return is just a int literal. We use `ConstantOp` to create one*/
        if (exprAny.isa(VisitorParserReturnType::kFloatLiteral)
            || exprAny.isa(VisitorParserReturnType::kIntLiteral)) {
          float f = 0.f;
          if (exprAny.isa(VisitorParserReturnType::kFloatLiteral)) {
            f = exprAny.getValue<float>();
          } else if (exprAny.isa(VisitorParserReturnType::kIntLiteral)) {
            f = exprAny.getValue<int64_t>();
          }
          mlir::Value value =
              m_OpBuilder.create<mlir::aten::ConstantOp>(location, m_OpBuilder.getF64FloatAttr(f));
          mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
          return VisitorParserReturn(value);
        }
        /* FIXME: throw error*/
        return VisitorParserReturn();
      }
    }
    case VisitorParserAtenTypeDeclType::kMap: {
      // TODO
      return VisitorParserReturn();
    }
    case VisitorParserAtenTypeDeclType::kArray: {
      // get the Element type and length
      auto payload = atv.arrayPayload;
      auto ty = payload.first;
      auto len = payload.second;
      // create all values.
      if (!theVarSpec->Assign()) {
        // init types with default attribute if they don't have a assign.
        // TODO
      } else {
        // TODO
      }
      return VisitorParserReturn();
    }
    case VisitorParserAtenTypeDeclType::kPtr: {
      auto pointeeType = atv.ptrPayload;
      if (!theVarSpec->Assign()) {
        auto ptrAttr = mlir::aten::NilAttr::get(m_OpBuilder.getContext(), pointeeType);
        mlir::Value value =
            m_OpBuilder.create<mlir::aten::ConstantOp>(location, pointeeType, ptrAttr);
        mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
        return VisitorParserReturn(value);
      } else {
        auto exprAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->expressionList()));
        if (exprAny.isa(VisitorParserReturnType::kMlirValue)) {
          auto value = exprAny.getValue<mlir::Value>();

          if (!value.isa<mlir::aten::PointerType>()) {
            // FIXME throw error.
          }

          mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
          return VisitorParserReturn(value);
        }
      }
      return VisitorParserReturn();
    }
    case kSlice: {
      return VisitorParserReturn();
    }
    case kString: {
      return VisitorParserReturn();
    }
    case kChar: {
      return VisitorParserReturn();
    }
    case kFunc: {
      return VisitorParserReturn();
    }
    case kStruct: {
      return VisitorParserReturn();
    }
    case kTensor: {
      auto payload = atv.tensorPayload;
      if (std::get<1>(payload).size() == 0) {
        // TODO
      } else {
        if (theVarSpec->Assign()) {
          // TODO
        } else {
          // TODO Pass correct value to empty op. Use mlir::tensor::empty method to build the value.
          // TODO register value to the table it belong to.
          // https://mlir.llvm.org/docs/Dialects/TensorOps/#tensorempty-tensoremptyop
          // mlir::Value value = m_OpBuilder.create<mlir::tensor::EmptyOp>(location);
          // return value;
          return VisitorParserReturn();
        }
      }
    }
  }
  return VisitorParserReturn();
}
//===----------------------------------------------------------------------===//
// mapType: Map LeftBracket type_ RightBracket elementType;
//
// Note: this function will just return the mlir::Type defination of a dictionary.
// What this function do:
// 1. visit type_
// 2. visit elementType
// 3. zip type_ and elementType as dictionary.
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitMapType(AutoTenV1Parser::MapTypeContext* ctx) {
  // TODO create a dictionary type for Aten.
  return visitChildren(ctx);
}

//===----------------------------------------------------------------------===//
// tensorType:
// 	Tensor (
// 		Less expression (Comma expression)* Comma (
// 			Float32
// 			| Float64
// 			| Int32
// 			| Int64
// 		) Greater
// 	)?;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitTensorType(AutoTenV1Parser::TensorTypeContext* ctx) {
  // parse type
  mlir::Type type;
  if (ctx->Float32()) {
    type = m_OpBuilder.getF32Type();
  } else if (ctx->Float64()) {
    type = m_OpBuilder.getF64Type();
  } else if (ctx->Int32()) {
    type = m_OpBuilder.getI32Type();
  } else if (ctx->Int64()) {
    type = m_OpBuilder.getI64Type();
  }
  // parse shape
  std::vector<VisitorParserReturn> dimsExpr;
  if (ctx->Less()) {
    for (auto item : ctx->expression()) {
      dimsExpr.emplace_back(std::any_cast<VisitorParserReturn>(visit(item)));
    }
  }
  // return tuple<type, dimsExpr> for [VarDecl/ShortDecl] to use. The [VarDecl/ShortDecl] will
  // consider the expression behind the tensor type. Such as `a := Tensor<10, 10, int32>{...}`. If
  // args in `a := Tensor<arg1, arg2, int32>` is not  constant, it will use `tensor::EmptyOp` or
  // `tensor::GenerateOp` to create tensor. Otherwise, tensor will be made constant using Dense
  // Attribute in `builtin` dialect.
  return VisitorParserReturn(
      VisitorParserAtenTypeDecl({type, dimsExpr}, VisitorParserAtenTypeDeclType::kTensor));
}

//===----------------------------------------------------------------------===//
// expressionList: expression (Comma expression)*;
//
// Note: I only support single expression here. So the expression.size() should be 1
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitExpressionList(AutoTenV1Parser::ExpressionListContext* ctx) {
  if (ctx->expression().size() != 1) {
    utils::CliFormatOutput::ErrorAt(
        m_FileName, ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
        "expression.size() != 1. nncv-c synatic only support single expression in one line.");
    return VisitorParserReturn();
  }
  return visit(ctx->expression()[0]);
}

//===----------------------------------------------------------------------===//
// expression:
// 	primaryExpr
// 	| unary_op = (Plus | Minus | Not | Caret | Star | And) expression
// 	| expression mul_op = (
// 		Star
// 		| Div
// 		| Mod
// 		| LeftShift
// 		| RightShift
// 		| And
// 	) expression
// 	| expression add_op = (Plus | Minus | Or | Caret) expression
// 	| expression rel_op = (
// 		Equal
// 		| NotEqual
// 		| Less
// 		| LessEqual
// 		| Greater
// 		| GreaterEqual
// 	) expression
// 	| expression AndAnd expression
// 	| expression OrOr expression;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitExpression(AutoTenV1Parser::ExpressionContext* ctx) {
  // primaryExpr
  if (ctx->primaryExpr()) {
    // TODO
    return visit(ctx->primaryExpr());
  }
  // unary_op = (Plus | Minus | Not | Caret | Star | And) expression
  else if (ctx->unary_op) {
    // TODO
  }
  // expression mul_op = (Star|Div|Mod|LeftShift|RightShift|And)expression
  else if (ctx->mul_op) {
    auto mulOpType = ctx->mul_op->getType();
    mlir::Value lhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[0]));
    mlir::Value rhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[1]));

    mlir::Location location = loc(ctx->mul_op->getLine(), ctx->mul_op->getCharPositionInLine());

    switch (mulOpType) {
      case m_Lexer.Star: {
        // TODO bulder is incorrect.
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
            location,
            mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::BinOpPredicate::Mul),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.Div: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
            location,
            mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::BinOpPredicate::Div),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.Mod: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
            location,
            mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::BinOpPredicate::Mod),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.LeftShift: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::ShiftOp>(location, lhsValue, rhsValue,
                                                                       m_OpBuilder.getUnitAttr());
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.RightShift: {
        mlir::Value retValue =
            m_OpBuilder.create<mlir::aten::ShiftOp>(location, lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.And: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
            location,
            mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::BinOpPredicate::And),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
    }
  }
  // expression add_op = (Plus|Minus|Or|Caret) expression
  else if (ctx->add_op) {
    auto addOpType = ctx->add_op->getType();
    mlir::Value lhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[0]));
    mlir::Value rhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[1]));

    mlir::Location location = loc(ctx->add_op->getLine(), ctx->add_op->getCharPositionInLine());
    switch (addOpType) {
      case m_Lexer.Plus: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
            location,
            mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::BinOpPredicate::Add),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.Minus: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
            location,
            mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::BinOpPredicate::Sub),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.Or: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
            location,
            mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::BinOpPredicate::Or),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.Caret: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
            location,
            mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::BinOpPredicate::Xor),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
    }
  }
  // expression rel_op = (Equal|NotEqual|Less|LessEqual|Greater|GreaterEqual) expression
  else if (ctx->rel_op) {
    auto relOpType = ctx->add_op->getType();
    mlir::Value lhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[0]));
    mlir::Value rhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[1]));

    mlir::Location location = loc(ctx->rel_op->getLine(), ctx->rel_op->getCharPositionInLine());

    switch (relOpType) {
      case m_Lexer.Equal: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::CmpOpPredicate::eq),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.NotEqual: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::CmpOpPredicate::ne),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.Less: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::CmpOpPredicate::lt),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.LessEqual: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::CmpOpPredicate::le),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.Greater: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::CmpOpPredicate::gt),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
      case m_Lexer.GreaterEqual: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::CmpOpPredicate::ge),
            lhsValue, rhsValue);
        return VisitorParserReturn(retValue);
      }
    }
  }
  // expression AndAnd expression
  else if (ctx->AndAnd()) {
    mlir::Value lhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[0]));
    mlir::Value rhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[1]));

    mlir::Location location = loc(ctx->AndAnd()->getSymbol()->getLine(),
                                  ctx->AndAnd()->getSymbol()->getCharPositionInLine());

    mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
        location,
        mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                            mlir::aten::BinOpPredicate::LogicAnd),
        lhsValue, rhsValue);

    return VisitorParserReturn(retValue);
  }
  // expression OrOr expression;
  else if (ctx->OrOr()) {
    mlir::Value lhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[0]));
    mlir::Value rhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[1]));

    mlir::Location location = loc(ctx->AndAnd()->getSymbol()->getLine(),
                                  ctx->AndAnd()->getSymbol()->getCharPositionInLine());

    mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
        location,
        mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                            mlir::aten::BinOpPredicate::LogicOr),
        lhsValue, rhsValue);

    return VisitorParserReturn(retValue);
  }
  return VisitorParserReturn();
  ;
}

std::any AutoTen2MlirVisitor::visitIdentifierList(AutoTenV1Parser::IdentifierListContext* ctx) {
  // TODO
  if (ctx->Identifier().size() != 1) {
    utils::CliFormatOutput::ErrorAt(
        m_FileName, ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
        "Identifier.size() != 1. nncv-c synatic only support single Identifier in one line.");
    return VisitorParserReturn();
    ;
  }
  return VisitorParserReturn(ctx->Identifier()[0]->getText());
}

//===----------------------------------------------------------------------===//
// The listener is for generating AST.
//
// Reference: https://zhuanlan.zhihu.com/p/369250644
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