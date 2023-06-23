#ifdef NNCV_ENABLE_ANTLR

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"

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
      // TODO register value to the table it belong to.
      mlir::Value value = m_OpBuilder.create<mlir::arith::ConstantIntOp>(
          location, std::any_cast<int8_t>(atv.payload), 8);
      return value;
    }
    case kInt16: {
      // TODO register value to the table it belong to.
      mlir::Value value = m_OpBuilder.create<mlir::arith::ConstantIntOp>(
          location, std::any_cast<int16_t>(atv.payload), 16);
      return value;
    }
    case kInt32: {
      // TODO register value to the table it belong to.
      mlir::Value value = m_OpBuilder.create<mlir::arith::ConstantIntOp>(
          location, std::any_cast<int32_t>(atv.payload), 32);
      return value;
    }
    case kInt64: {
      // TODO register value to the table it belong to.
      mlir::Value value = m_OpBuilder.create<mlir::arith::ConstantIntOp>(
          location, std::any_cast<int64_t>(atv.payload), 64);
      return value;
    }
    case kFloat32: {
      // TODO register value to the table it belong to.
      mlir::Value value = m_OpBuilder.create<mlir::arith::ConstantFloatOp>(
          location, std::any_cast<float>(atv.payload), 32);
      return value;
    }
    case kFloat64: {
      {
        // TODO register value to the table it belong to.
        mlir::Value value = m_OpBuilder.create<mlir::arith::ConstantFloatOp>(
            location, std::any_cast<double>(atv.payload), 64);
        return value;
      }
    }
    case kMap:
    case kArray:
    case kSlice:
    case kString:
    case kChar:
    case kFunc:
    case kStruct:
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
          mlir::Value value = m_OpBuilder.create<mlir::tensor::EmptyOp>(location);
          return value;
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
  // `tensor::GenerateOp` to create tensor. Otherwise, tensor will be made constant.
  return __AtenType4Visitor__(std::tuple<mlir::Type, std::vector<mlir::Value>>{type, dimsExpr},
                              AtenType::kTensor);
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