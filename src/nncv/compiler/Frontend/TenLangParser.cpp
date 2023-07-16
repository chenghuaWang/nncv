#ifdef NNCV_ENABLE_ANTLR

#include "nncv/compiler/Dialects/AutoTen/IR/Dialect.hpp"

#include "nncv/compiler/Frontend/TenLangParser.hpp"
#include "nncv/compiler/Utils/CliFormatOutput.hpp"

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
  std::string symbolName = std::any_cast<std::string>(
      visit(theVarSpec->identifierList()));  // TODO identifier list on working
  // get the identifier list's position
  mlir::Location location = loc(theVarSpec->identifierList()->getStart()->getLine(),
                                theVarSpec->identifierList()->getStart()->getCharPositionInLine());
  // build values.
  __AtenType4Visitor__ atv = std::any_cast<__AtenType4Visitor__>(visit(theVarSpec->type_()));
  switch (atv.type) {
    case kInt8: {
      if (!theVarSpec->Assign()) {
        // if var delare has no assgin. Then attatch a empty value to it. 0 by default.
        mlir::Value value =
            m_OpBuilder.create<mlir::arith::ConstantOp>(location, m_OpBuilder.getI8IntegerAttr(0));
        mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
        return 0;
      } else {
        // expression has value;
        // 1) expression may be `var a int8 = 1;` then, in expression a constant builder will be
        // called in expression.
        // 2) expression may be `var a int8 = c + d;` then, in expression a add builder will be
        // called in expression.
        // Anyway, the only thing visit(expression) will returned is Value or error(null).
        mlir::failed(m_SymbolTable.declare(
            symbolName, std::any_cast<mlir::Value>(visit(theVarSpec->expressionList())), ctx));
        return 0;
      }
    }
    case kInt16: {
      if (!theVarSpec->Assign()) {
        mlir::Value value =
            m_OpBuilder.create<mlir::arith::ConstantOp>(location, m_OpBuilder.getI16IntegerAttr(0));
        mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
        return 0;
      } else {
        mlir::failed(m_SymbolTable.declare(
            symbolName, std::any_cast<mlir::Value>(visit(theVarSpec->expressionList())), ctx));
        return 0;
      }
    }
    case kInt32: {
      if (!theVarSpec->Assign()) {
        mlir::Value value =
            m_OpBuilder.create<mlir::arith::ConstantOp>(location, m_OpBuilder.getI32IntegerAttr(0));
        mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
        return 0;
      } else {
        mlir::failed(m_SymbolTable.declare(
            symbolName, std::any_cast<mlir::Value>(visit(theVarSpec->expressionList())), ctx));
        return 0;
      }
    }
    case kInt64: {
      if (!theVarSpec->Assign()) {
        mlir::Value value =
            m_OpBuilder.create<mlir::arith::ConstantOp>(location, m_OpBuilder.getI64IntegerAttr(0));
        mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
        return 0;
      } else {
        mlir::failed(m_SymbolTable.declare(
            symbolName, std::any_cast<mlir::Value>(visit(theVarSpec->expressionList())), ctx));
        return 0;
      }
    }
    case kFloat32: {
      if (!theVarSpec->Assign()) {
        mlir::Value value =
            m_OpBuilder.create<mlir::arith::ConstantOp>(location, m_OpBuilder.getF32FloatAttr(0));
        mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
        return 0;
      } else {
        mlir::failed(m_SymbolTable.declare(
            symbolName, std::any_cast<mlir::Value>(visit(theVarSpec->expressionList())), ctx));
        return 0;
      }
    }
    case kFloat64: {
      if (!theVarSpec->Assign()) {
        mlir::Value value =
            m_OpBuilder.create<mlir::arith::ConstantOp>(location, m_OpBuilder.getF64FloatAttr(0));
        mlir::failed(m_SymbolTable.declare(symbolName, value, ctx));
        return 0;
      } else {
        mlir::failed(m_SymbolTable.declare(
            symbolName, std::any_cast<mlir::Value>(visit(theVarSpec->expressionList())), ctx));
        return 0;
      }
    }
    case kMap: {
      return 0;
    }
    case kArray: {
      return 0;
    }
    case kSlice: {
      return 0;
    }
    case kString: {
      return 0;
    }
    case kChar: {
      return 0;
    }
    case kFunc: {
      return 0;
    }
    case kStruct: {
      return 0;
    }
    case kTensor: {
      std::tuple<mlir::Type, std::vector<mlir::Value>> payload =
          std::any_cast<std::tuple<mlir::Type, std::vector<mlir::Value>>>(atv.payload);
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
          return 0;
        }
      }
    }
  }
  return 0;
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
  std::vector<mlir::Value> dimsExpr;
  if (ctx->Less()) {
    for (auto item : ctx->expression()) {
      dimsExpr.emplace_back(std::any_cast<mlir::Value>(visit(item)));
    }
  }
  // return tuple<type, dimsExpr> for [VarDecl/ShortDecl] to use. The [VarDecl/ShortDecl] will
  // consider the expression behind the tensor type. Such as `a := Tensor<10, 10, int32>{...}`. If
  // args in `a := Tensor<arg1, arg2, int32>` is not  constant, it will use `tensor::EmptyOp` or
  // `tensor::GenerateOp` to create tensor. Otherwise, tensor will be made constant using Dense
  // Attribute in `builtin` dialect.
  return __AtenType4Visitor__(std::tuple<mlir::Type, std::vector<mlir::Value>>{type, dimsExpr},
                              AtenType::kTensor);
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
    return nullptr;
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
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryArithOp>(
            location,
            mlir::aten::BinaryArithPredictAttr::get(m_OpBuilder.getContext(),
                                                    mlir::aten::BinaryArithPredict::Mul),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.Div: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryArithOp>(
            location,
            mlir::aten::BinaryArithPredictAttr::get(m_OpBuilder.getContext(),
                                                    mlir::aten::BinaryArithPredict::Div),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.Mod: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryArithOp>(
            location,
            mlir::aten::BinaryArithPredictAttr::get(m_OpBuilder.getContext(),
                                                    mlir::aten::BinaryArithPredict::Mod),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.LeftShift: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryLogicOp>(
            location,
            mlir::aten::BinaryLogicPredictAttr::get(m_OpBuilder.getContext(),
                                                    mlir::aten::BinaryLogicPredict::ShlOp),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.RightShift: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryLogicOp>(
            location,
            mlir::aten::BinaryLogicPredictAttr::get(m_OpBuilder.getContext(),
                                                    mlir::aten::BinaryLogicPredict::ShrOp),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.And: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryLogicOp>(
            location,
            mlir::aten::BinaryLogicPredictAttr::get(m_OpBuilder.getContext(),
                                                    mlir::aten::BinaryLogicPredict::AndOp),
            lhsValue, rhsValue);
        return retValue;
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
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryArithOp>(
            location,
            mlir::aten::BinaryArithPredictAttr::get(m_OpBuilder.getContext(),
                                                    mlir::aten::BinaryArithPredict::Add),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.Minus: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryArithOp>(
            location,
            mlir::aten::BinaryArithPredictAttr::get(m_OpBuilder.getContext(),
                                                    mlir::aten::BinaryArithPredict::Sub),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.Or: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryLogicOp>(
            location,
            mlir::aten::BinaryLogicPredictAttr::get(m_OpBuilder.getContext(),
                                                    mlir::aten::BinaryLogicPredict::OrOp),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.Caret: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryLogicOp>(
            location,
            mlir::aten::BinaryLogicPredictAttr::get(m_OpBuilder.getContext(),
                                                    mlir::aten::BinaryLogicPredict::XorOp),
            lhsValue, rhsValue);
        return retValue;
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
            mlir::aten::CmpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpPredicate::Equl),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.NotEqual: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpPredicate::Nequal),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.Less: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpPredicate::Less),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.LessEqual: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpPredicate::Lesseq),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.Greater: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpPredicate::Greater),
            lhsValue, rhsValue);
        return retValue;
      }
      case m_Lexer.GreaterEqual: {
        mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
            location,
            mlir::aten::CmpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpPredicate::Greatereq),
            lhsValue, rhsValue);
        return retValue;
      }
    }
  }
  // expression AndAnd expression
  else if (ctx->AndAnd()) {
    mlir::Value lhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[0]));
    mlir::Value rhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[1]));

    mlir::Location location = loc(ctx->AndAnd()->getSymbol()->getLine(),
                                  ctx->AndAnd()->getSymbol()->getCharPositionInLine());

    mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryLogicOp>(
        location,
        mlir::aten::BinaryLogicPredictAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::BinaryLogicPredict::AndAndOp),
        lhsValue, rhsValue);
  }
  // expression OrOr expression;
  else if (ctx->OrOr()) {
    mlir::Value lhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[0]));
    mlir::Value rhsValue = std::any_cast<mlir::Value>(visit(ctx->expression()[1]));

    mlir::Location location = loc(ctx->AndAnd()->getSymbol()->getLine(),
                                  ctx->AndAnd()->getSymbol()->getCharPositionInLine());

    mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinaryLogicOp>(
        location,
        mlir::aten::BinaryLogicPredictAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::BinaryLogicPredict::OrOrOp),
        lhsValue, rhsValue);
  }
  return 0;
}

std::any AutoTen2MlirVisitor::visitIdentifierList(AutoTenV1Parser::IdentifierListContext* ctx) {
  // TODO
  if (ctx->Identifier().size() != 1) {
    utils::CliFormatOutput::ErrorAt(
        m_FileName, ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine(),
        "Identifier.size() != 1. nncv-c synatic only support single Identifier in one line.");
    return nullptr;
  }
  return ctx->Identifier()[0]->getText();
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