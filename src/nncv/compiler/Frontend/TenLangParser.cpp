#ifdef NNCV_ENABLE_ANTLR

#include "llvm/ADT/SmallVector.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenAttrs.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
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
  // get the location
  mlir::Location location = loc(ctx->Function()->getSymbol()->getLine(),
                                ctx->Function()->getSymbol()->getCharPositionInLine());

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
        // FIXME emit error.
      }
    } else if (item->False_()) {
      if (!funcFlags.setFlagsKV(sig, false)) {
        // FIXME emit error.
      }
    } else {
      auto strRetValue = std::any_cast<VisitorParserReturn>(visit(item->expression()));
      if (!strRetValue.isa(VisitorParserReturnType::kStringLiteral)) {
        // FIXME emit error
      }
      if (!funcFlags.setFlagsKV(sig, strRetValue.getValue<std::string>())) {
        // FIXME emit error
      }
    }
  }

  // public ?
  bool isPublic = false;
  if (ctx->Public()) { isPublic = true; }

  // eats Function
  visit(ctx->Function());

  // identifier
  std::string funcName = ctx->Identifier()->getText();

  // signature
  auto payload = std::any_cast<VisitorParserReturn>(visit(ctx->signature()))
                     .getValue<FuncParameterAndReturn>();

  // check current state. And set flags. generate Op with/o block.
  // generate function type first
  llvm::SmallVector<mlir::Type, 4> paraTypes;
  for (auto& item : payload.parameters) { paraTypes.emplace_back(std::get<1>(item)); }
  auto funcTy = mlir::aten::FuncType::get(m_OpBuilder.getContext(), paraTypes,
                                          std::get<1>(payload.ret), /*varArg*/ false);

  llvm::SmallVector<mlir::DictionaryAttr, 4> _ub;

  // TODO
  if (ctx->block()) {
    // TODO symbol table stack push

    // symbol table stack pop
  } else /*no function body*/ {
    // TODO WAIT: Support Package and Function rename
    auto op = m_OpBuilder.create<mlir::aten::FuncOp>(
        location, funcName, funcTy, funcFlags.genNamedAttrs(m_OpBuilder.getContext()), _ub);
    if (isPublic) {
      mlir::SymbolTable::setSymbolVisibility(op, mlir::SymbolTable::Visibility::Public);

    } else {
      mlir::SymbolTable::setSymbolVisibility(op, mlir::SymbolTable::Visibility::Private);
    }
    m_TheModule.push_back(op);
  }
  // no need to register to symbol table. Using mlir's symbol table is enough.
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// signature: parameters ArrowReturnType result | parameters;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitSignature(AutoTenV1Parser::SignatureContext* ctx) {
  auto payload = std::any_cast<VisitorParserReturn>(visit(ctx->parameters()))
                     .getValue<FuncParameterAndReturn>();

  // TODO parse result.
  if (ctx->ArrowReturnType()) {
    mlir::Type resultTy = mlir::aten::VoidType();
  } else {
  }

  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// parameters:
//	LeftParen (parameterDecl (Comma parameterDecl)* Comma?)? RightParen;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitParameters(AutoTenV1Parser::ParametersContext* ctx) {
  visit(ctx->LeftParen());

  FuncParameterAndReturn payload;

  auto paras = ctx->parameterDecl();
  for (auto item : paras) {
    auto ty = std::any_cast<VisitorParserReturn>(item->type_()).getValue<mlir::Type>();
    std::string name;
    bool hasIdentifier = false;

    if (item->Ellipsis()) {
      // FIXME throw error, not support yet.
    }
    if (item->identifierList()) {
      name = std::any_cast<VisitorParserReturn>(item->identifierList()).getValue<std::string>();
    }
    payload.parameters.emplace_back(name, ty, /*has identifier*/ hasIdentifier);
  }

  visit(ctx->RightParen());

  return VisitorParserReturn(payload);
}

//===----------------------------------------------------------------------===//
// typeDecl:
// 	Type (typeSpec | LeftParen (typeSpec eos)* RightParen);
//
// typeSpec: Identifier Assign? type_;
//
// NOTE: type only for struct and impl two types
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitTypeDecl(AutoTenV1Parser::TypeDeclContext* ctx) {
  visit(ctx->Type());
  if (ctx->typeSpec().size() != 1 || ctx->typeSpec()[0]->Assign()) {
    // FIXME: throw error
  } else {
    std::string name = ctx->typeSpec()[0]->Identifier()->getText();

    m_curParsingTypeDeclName = name;
    m_parseState = parseState::kTypeDecl;

    auto type = std::any_cast<VisitorParserReturn>(visit(ctx->typeSpec()[0]->type_()));
    // case 1. process struct type
    if (type.isa(VisitorParserReturnType::kMlirType)) {
      // build a inner declaration
      m_OpBuilder.create<mlir::aten::MakeStructSymbol>(
          loc(ctx->typeSpec()[0]->getStart()->getLine(),
              ctx->typeSpec()[0]->getStart()->getCharPositionInLine()),
          name, type.getValue<mlir::Type>());
    }
    // TODO case 2. process impl type.
  }
  return VisitorParserReturn();
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

//===----------------------------------------------------------------------===//
// structType:
// 	Struct LeftBrace (Public? fieldDecl eos)* RightBrace;
//
// fieldDecl: (identifierList type_ | embeddedField) tag = StringLiteral?;
//
// NOTE: This `visitStructType` function will only be visited when struct is declaring.
//
// return: VisitorParserReturn(mlir::Type);
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitStructType(AutoTenV1Parser::StructTypeContext* ctx) {
  visit(ctx->Struct());
  visit(ctx->LeftBrace());

  llvm::SmallVector<mlir::Type, 8> tys;
  utils::AtenStructSymbolPayload symbolPayload;

  for (auto item : ctx->fieldDecl()) {
    bool isPublic = (item->parent->getText() == "pub");
    std::string varName =
        std::any_cast<VisitorParserReturn>(item->identifierList()).getValue<std::string>();
    mlir::Type ty = std::any_cast<VisitorParserReturn>(item->type_()).getValue<mlir::Type>();
    tys.emplace_back(ty);

    // insert to this lang's symbol table
    symbolPayload.argumentsLists.emplace_back(
        std::tuple<std::string, mlir::Type, bool>{varName, ty, isPublic});
  }
  visit(ctx->RightBrace());
  auto ty = mlir::aten::StructType::get(m_OpBuilder.getContext(), tys, "un-named", true);
  m_curSymbolTable->registerStructSymbol(m_curParsingTypeDeclName, symbolPayload);
  m_parseState = parseState::kNone;
  return VisitorParserReturn(ty);
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
    case VisitorParserAtenTypeDeclType::kBool: {
      // HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(8)
    }
    case VisitorParserAtenTypeDeclType::kInt1: {
      // HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(8)
    }
    case VisitorParserAtenTypeDeclType::kInt8: {
      // HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(8)
    }
    case VisitorParserAtenTypeDeclType::kInt16: {
      // HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(16)
    }
    case VisitorParserAtenTypeDeclType::kInt32: {
      // HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(32)
    }
    case VisitorParserAtenTypeDeclType::kInt64: {
      // HANDLE_VISITOR_PARSER_FOR_INT_WIDTH(64);
    }
    case VisitorParserAtenTypeDeclType::kFloat32: {
      if (!theVarSpec->Assign()) {
        mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(
            location, mlir::Float32Type::get(m_OpBuilder.getContext()),
            m_OpBuilder.getF32FloatAttr(0.f));
        m_curSymbolTable->registerVarSymbol(symbolName, value);  // FIXME error info
        return VisitorParserReturn(value);
      } else {
        auto exprAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->expressionList()));
        /* if this expr return a mlir::Value. We just need to record this value;*/
        if (exprAny.isa(VisitorParserReturnType::kMlirValue)) {
          auto v = exprAny.getValue<mlir::Value>();

          // if value's type is mismatch with Float32
          // TODO do cast.

          m_curSymbolTable->registerVarSymbol(symbolName, v);  // FIXME error info
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
          mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(
              location, mlir::Float32Type::get(m_OpBuilder.getContext()),
              m_OpBuilder.getF32FloatAttr(f));
          m_curSymbolTable->registerVarSymbol(symbolName, value);  // FIXME error info
          return VisitorParserReturn(value);
        }
        /* FIXME: throw error*/
        return VisitorParserReturn();
      }
    }
    case VisitorParserAtenTypeDeclType::kFloat64: {
      if (!theVarSpec->Assign()) {
        mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(
            location, mlir::Float64Type::get(m_OpBuilder.getContext()),
            m_OpBuilder.getF64FloatAttr(0.f));
        m_curSymbolTable->registerVarSymbol(symbolName, value);  // FIXME error info
        return VisitorParserReturn(value);
      } else {
        auto exprAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->expressionList()));
        /* if this expr return a mlir::Value. We just need to record this value;*/
        if (exprAny.isa(VisitorParserReturnType::kMlirValue)) {
          auto v = exprAny.getValue<mlir::Value>();

          // if value's type is mismatch with Float64
          // TODO do cast.

          m_curSymbolTable->registerVarSymbol(symbolName, v);  // FIXME error info
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
          mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(
              location, mlir::Float64Type::get(m_OpBuilder.getContext()),
              m_OpBuilder.getF64FloatAttr(f));
          m_curSymbolTable->registerVarSymbol(symbolName, value);  // FIXME error info
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
      auto arrayTy = mlir::aten::ArrayType::get(m_OpBuilder.getContext(), ty, len);
      // create all values.
      if (!theVarSpec->Assign()) {
        // init types with default attribute if they don't have a assign.
        mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(
            location, arrayTy,
            mlir::aten::ConstArrayAttr::get(
                arrayTy, mlir::aten::WithoutInitAttr::get(m_OpBuilder.getContext(), arrayTy)));
        m_curSymbolTable->registerVarSymbol(symbolName, value);  // FIXME error info
        return VisitorParserReturn(value);
      } else {
        // expressionList->expression->primaryExpr->operand->literal->compositeLit->
        auto res = visit(theVarSpec->expressionList());
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
        m_curSymbolTable->registerVarSymbol(symbolName, value);  // FIXME error info
        return VisitorParserReturn(value);
      } else {
        auto exprAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->expressionList()));
        if (exprAny.isa(VisitorParserReturnType::kMlirValue)) {
          auto value = exprAny.getValue<mlir::Value>();

          if (!value.getType().isa<mlir::aten::PointerType>()) {
            // FIXME throw error.
          }

          m_curSymbolTable->registerVarSymbol(symbolName, value);  // FIXME error info
          return VisitorParserReturn(value);
        }
      }
      return VisitorParserReturn();
    }
    case VisitorParserAtenTypeDeclType::kSlice: {
      return VisitorParserReturn();
    }
    case VisitorParserAtenTypeDeclType::kString: {
      return VisitorParserReturn();
    }
    case VisitorParserAtenTypeDeclType::kChar: {
      return VisitorParserReturn();
    }
    case VisitorParserAtenTypeDeclType::kFunc: {
      return VisitorParserReturn();
    }
    case VisitorParserAtenTypeDeclType::kStruct: {
      return VisitorParserReturn();
    }
    case VisitorParserAtenTypeDeclType::kTensor: {
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
//
// NOTE:
// `var b Tensor;` is decrepit.
// You can only decl a Tensor by `var a Tensor<shape, type>`
// If you want to create a dynamic tensor, use `nncv.tensor(shape, nncv.type)` function.
// And tensor is the first class of aten-lang, you don't need to free the mem of tensor
// yourself. The mem bufferization will do everything for you.
//
// return: VisitorParserReturn(mlir::Type);
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitTensorType(AutoTenV1Parser::TensorTypeContext* ctx) {
  // check if has shape, type
  if (!ctx->Less()) {
    // FIXME: throw error.
  }
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
  llvm::SmallVector<int64_t, 4> shape;
  for (auto item : dimsExpr) {
    if (item.isa(VisitorParserReturnType::kIntLiteral)) {
      shape.emplace_back(item.getValue<int64_t>());
    }
  }
  auto ty = mlir::RankedTensorType::get(shape, type);
  return VisitorParserReturn(ty);
}

//===----------------------------------------------------------------------===//
// expressionList: expression (Comma expression)*;
//
// Note: I only support single expression here. So the expression.size() should be 1
//
// Note: If you want to parse value to array, such as `a int[] = {1, 2, 3}`. The
// expression list should be parsed by array/tensor itself, not this function.
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
}

std::any AutoTen2MlirVisitor::visitIdentifierList(AutoTenV1Parser::IdentifierListContext* ctx) {
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
// Identifier Dot Identifier;
//
// A type in a package. Such as `cv.image` and `cv.image` is a class defined
// in `cv` package.
//
// NOTE: for now, just support single level package. Which means package.package.struct
// is not support.
//
// NOTE: Qualified Identifier is only used in `visitTypeName` func. So there is no
// need to add this type to `VisitorParserReturn`.
//
// return: llvm::SmallVector<llvm::StringRef, 2>
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitQualifiedIdent(AutoTenV1Parser::QualifiedIdentContext* ctx) {
  llvm::SmallVector<llvm::StringRef, 2> ans;
  ans.emplace_back(ctx->Identifier()[0]->getText());
  ans.emplace_back(ctx->Identifier()[1]->getText());
  return ans;
}

//===----------------------------------------------------------------------===//
// type_:
//	typeName
//	| typeLit
//	| LeftParen type_ RightParen
//	| builtinType;
//
// return: VisitorParserReturn(mlir::type)
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitType_(AutoTenV1Parser::Type_Context* ctx) {
  if (ctx->typeName()) {
    llvm::SmallVector<llvm::StringRef, 2> symbolName =
        std::any_cast<llvm::SmallVector<llvm::StringRef, 2>>(ctx->typeName());
    // NOTE: case 1. recursive struct ref. No need to check symbol table. Just create a StructSelf
    // class.
    if (symbolName.size() == 1 && symbolName[0] == m_curParsingTypeDeclName) {
      auto ty = mlir::aten::StructSelfType::get(
          m_OpBuilder.getContext(),
          mlir::StringAttr::get(m_OpBuilder.getContext(), m_curParsingTypeDeclName));
      return VisitorParserReturn(ty);
    }
    // other cases.
    // TODO check the module look up table to get the correct symbol type.
  } else if (ctx->typeLit()) {
    return visit(ctx->typeLit());
  } else if (ctx->LeftParen()) {
    // will not impl.
  } else if (ctx->builtinType()) {
    if (ctx->builtinType()->Int8()) {
      auto ty = mlir::aten::IntType::get(m_OpBuilder.getContext(), 8, /*bool isSigned*/ true);
      return VisitorParserReturn(ty);
    }
    if (ctx->builtinType()->Int16()) {
      auto ty = mlir::aten::IntType::get(m_OpBuilder.getContext(), 16, /*bool isSigned*/ true);
      return VisitorParserReturn(ty);
    }
    if (ctx->builtinType()->Int32()) {
      auto ty = mlir::aten::IntType::get(m_OpBuilder.getContext(), 32, /*bool isSigned*/ true);
      return VisitorParserReturn(ty);
    }
    if (ctx->builtinType()->Int64()) {
      auto ty = mlir::aten::IntType::get(m_OpBuilder.getContext(), 64, /*bool isSigned*/ true);
      return VisitorParserReturn(ty);
    }
    if (ctx->builtinType()->Float32()) {
      auto ty = mlir::Float32Type::get(m_OpBuilder.getContext());
      return VisitorParserReturn(ty);
    }
    if (ctx->builtinType()->Float64()) {
      auto ty = mlir::Float64Type::get(m_OpBuilder.getContext());
      return VisitorParserReturn(ty);
    }
    if (ctx->builtinType()->Bool()) {
      auto ty = mlir::aten::BoolType::get(m_OpBuilder.getContext());
      return VisitorParserReturn(ty);
    }
    if (ctx->builtinType()->String()) {
      auto ty = mlir::aten::ArrayType::get(
          m_OpBuilder.getContext(),
          mlir::aten::CharType::get(m_OpBuilder.getContext(), 16, /*utf*/ true), 0);
      // delay sizeT refactor.
      return VisitorParserReturn(ty);
    }
    if (ctx->builtinType()->Char()) {
      auto ty = mlir::aten::CharType::get(m_OpBuilder.getContext(), 16, /*utf*/ true);
      return VisitorParserReturn(ty);
    }
    if (ctx->builtinType()->Void()) {
      auto ty = mlir::aten::VoidType::get(m_OpBuilder.getContext());
      return VisitorParserReturn(ty);
    }
    if (ctx->builtinType()->tensorType()) { return visit(ctx->builtinType()->tensorType()); }
  }
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// typeLit:
// 	arrayType
// 	| structType
// 	| pointerType
// 	| functionType
// 	| implType
// 	| sliceType
// 	| mapType;
//
// return: VisitorParserReturn(mlir::Type | impl flags);
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitTypeLit(AutoTenV1Parser::TypeLitContext* ctx) {
  if (ctx->arrayType()) { return visit(ctx->arrayType()); }
  if (ctx->structType()) { return visit(ctx->structType()); }
  if (ctx->pointerType()) { return visit(ctx->pointerType()); }
  // TODO
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// arrayType: LeftBracket arrayLength RightBracket elementType;
//
// NOTE: To be simplified. Array type do not support length infer. Such as `a [...]int = {1, 2, 3}`
//
// return: return: VisitorParserReturn(mlir::Type);
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitArrayType(AutoTenV1Parser::ArrayTypeContext* ctx) {
  visit(ctx->LeftBracket());
  auto len = std::any_cast<VisitorParserReturn>(visit(ctx->arrayLength()->expression()));
  visit(ctx->RightBracket());
  auto tyOfArray = std::any_cast<VisitorParserReturn>(visit(ctx->elementType()->type_()));
  // check the len is int64_t
  if (len.isa(VisitorParserReturnType::kIntLiteral)
      && tyOfArray.isa(VisitorParserReturnType::kMlirType)) {
    auto ty = mlir::aten::ArrayType::get(m_OpBuilder.getContext(), tyOfArray.getValue<mlir::Type>(),
                                         (uint64_t)len.getValue<int64_t>());
    return VisitorParserReturn(ty);
  } else {
    // FIXME error
  }
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// pointerType: Star type_;
//
// return: return: VisitorParserReturn(mlir::Type);
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitPointerType(AutoTenV1Parser::PointerTypeContext* ctx) {
  auto resType = std::any_cast<VisitorParserReturn>(visit(ctx->type_()));
  if (resType.isa(VisitorParserReturnType::kMlirType)) {
    auto ty =
        mlir::aten::PointerType::get(m_OpBuilder.getContext(), resType.getValue<mlir::Type>());
    return VisitorParserReturn(ty);
  } else {
    // FIXME: throw error.
  }
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// typeName: qualifiedIdent | Identifier;
//
// return: llvm::SmallVector<llvm::StringRef, 2>
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitTypeName(AutoTenV1Parser::TypeNameContext* ctx) {
  if (ctx->qualifiedIdent()) {
    return visit(ctx->qualifiedIdent());
  } else {
    llvm::SmallVector<llvm::StringRef, 2> ans;
    ans.emplace_back(ctx->Identifier()->getText());
    return ans;
  }
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