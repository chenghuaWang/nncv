#include <string>
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "nncv/compiler/Utils/SymbolRef.hpp"
#ifdef NNCV_ENABLE_ANTLR

#include "llvm/ADT/SmallVector.h"

#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenAttrs.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Frontend/TenLangParser.hpp"
#include "nncv/compiler/Utils/CliFormatOutput.hpp"

namespace nncv {
namespace compiler {
namespace frontend {

// Utilities

llvm::SmallVector<mlir::Value, 4> AutoTen2MlirVisitor::castAtenArithToMlirArith(
    llvm::SmallVector<mlir::Value, 4>& valueArry) {
  llvm::SmallVector<mlir::Value, 4> res;

  for (const auto item : valueArry) {
    if (item.getType().isa<mlir::IndexType>()) {
      res.emplace_back(item);
    } else {
      // the input is not mlir::index. Then, build a aten::CastOp
      // casting aten::IntType to mlir::IndexType
      mlir::Value value = m_OpBuilder.create<mlir::aten::CastOp>(
          item.getLoc(),
          /*result type*/ mlir::IndexType::get(m_OpBuilder.getContext()),
          /*predict*/
          mlir::aten::CastPredicateAttr::get(m_OpBuilder.getContext(),
                                             mlir::aten::CastPredicate::int_to_mlir_index),
          /*input*/ item);
      res.emplace_back(value);
    }
  }
  return res;
}

//===----------------------------------------------------------------------===//
// slice_:
// 	LeftBracket (
// 		expression? Colon expression?
// 		| expression? Colon expression Colon expression
// 		| expression
// 	) (
// 		Comma (
// 			expression? Colon expression?
// 			| expression? Colon expression Colon expression
// 			| expression
// 		)
// 	)* RightBracket;
//
// FIXME: Now, Just support: expression Comma expression Comma ...
//===----------------------------------------------------------------------===//
VisitorParserReturn AutoTen2MlirVisitor::parseSlice_(AutoTenV1Parser::Slice_Context* ctx,
                                                     VisitorParserReturn& value) {
  auto _value = value.getValue<mlir::Value>();

  int __line = ctx->LeftBracket()->getSymbol()->getLine();
  int __col = ctx->LeftBracket()->getSymbol()->getCharPositionInLine();

  mlir::Location location = loc(__line, __col);

  llvm::SmallVector<mlir::Value, 4> indexArray;

  Ps.PushSliceStmt();
  for (const auto item : ctx->expression()) {
    indexArray.emplace_back(
        std::any_cast<VisitorParserReturn>(visit(item)).getValue<mlir::Value>());
  }
  Ps.Pop();

  auto castedIdnexArray = castAtenArithToMlirArith(indexArray);

  if (Ps.IsInAssignStmt()
      && (_value.getType().isa<mlir::MemRefType>()
          || _value.getType().isa<mlir::UnrankedMemRefType>())) {
    Ps.SetCurSliceIndex(castedIdnexArray);
    return value;
  }

  if (_value.getType().isa<mlir::MemRefType>()
      || _value.getType().isa<mlir::UnrankedMemRefType>()) {
    // 1. cast all aten's type to mlir's builtin index type. (castAtenArithToMlirArith).
    // 2. create memref load op. Will return arith value.
    mlir::Value retValue =
        m_OpBuilder.create<mlir::memref::LoadOp>(location, _value, castedIdnexArray);
    return VisitorParserReturn(retValue);
  }

  return VisitorParserReturn();
}

VisitorParserReturn AutoTen2MlirVisitor::parseIndex_(AutoTenV1Parser::IndexContext* ctx,
                                                     VisitorParserReturn& value) {
  auto _value = value.getValue<mlir::Value>();

  int __line = ctx->LeftBracket()->getSymbol()->getLine();
  int __col = ctx->LeftBracket()->getSymbol()->getCharPositionInLine();

  mlir::Location location = loc(__line, __col);

  llvm::SmallVector<mlir::Value, 4> indexArray;

  Ps.PushSliceStmt();
  indexArray.emplace_back(
      std::any_cast<VisitorParserReturn>(visit(ctx->expression())).getValue<mlir::Value>());
  Ps.Pop();

  auto castedIdnexArray = castAtenArithToMlirArith(indexArray);

  if (Ps.IsInAssignStmt()
      && (_value.getType().isa<mlir::MemRefType>()
          || _value.getType().isa<mlir::UnrankedMemRefType>())) {
    Ps.SetCurSliceIndex(castedIdnexArray);
    return value;
  }

  if (_value.getType().isa<mlir::MemRefType>()
      || _value.getType().isa<mlir::UnrankedMemRefType>()) {
    // 1. cast all aten's type to mlir's builtin index type. (castAtenArithToMlirArith).
    // 2. create memref load op. Will return arith value.
    mlir::Value retValue =
        m_OpBuilder.create<mlir::memref::LoadOp>(location, _value, castedIdnexArray);
    return VisitorParserReturn(retValue);
  }

  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// arguments:
// 	LeftParen (
// 		(expressionList | nonNamedType (Comma expressionList)?) Ellipsis? Comma?
// 	)? RightParen;
//
// This stmt for function call.
//===----------------------------------------------------------------------===//
VisitorParserReturn AutoTen2MlirVisitor::parseArgument(AutoTenV1Parser::ArgumentsContext* ctx,
                                                       VisitorParserReturn& value) {
  int __line = ctx->LeftParen()->getSymbol()->getLine();
  int __col = ctx->LeftParen()->getSymbol()->getCharPositionInLine();
  mlir::Location location = loc(__line, __col);

  auto funcName = value.getValue<std::string>();

  // auto funcSymbol = m_curSymbolTable->getFuncSymbol(funcName);
  // using mlir own lookup table instead.
  auto funcOp = mlir::cast<mlir::aten::FuncOp>(*m_TheModule.lookupSymbol(funcName));

  llvm::SmallVector<mlir::Value, 4> args;
  for (const auto item : ctx->expressionList()->expression()) {
    auto ret = std::any_cast<VisitorParserReturn>(visit(item)).getValue<mlir::Value>();
    args.emplace_back(ret);
  }

  auto op = m_OpBuilder.create<mlir::aten::CallOp>(location, funcOp, args);

  // get return result and return.
  if (op.getNumResults()) {
    mlir::Value result = op->getResult(0);
    return VisitorParserReturn(result);
  } else {
    return VisitorParserReturn();
  }
}

// auto cast v1 type and v2 type to the same type.
// !!! mlir::Index should be casted manully, not in this function !!!
inline llvm::SmallVector<mlir::Value, 2> AutoTen2MlirVisitor::autoTypeCastSolver(mlir::Value& v1,
                                                                                 mlir::Value& v2) {
  auto type1 = v1.getType();
  auto type2 = v2.getType();

  llvm::SmallVector<mlir::Value> result;

  // case 1. int32 and float32. case int32 to float32
  if (type1.isa<mlir::aten::IntType>() && type2.isa<mlir::Float32Type>()) {
    mlir::Value value = m_OpBuilder.create<mlir::aten::CastOp>(
        v1.getLoc(), type2,
        mlir::aten::CastPredicateAttr::get(m_OpBuilder.getContext(),
                                           mlir::aten::CastPredicate::int_to_float),
        v1);
    result.emplace_back(value);
    result.emplace_back(v2);
    return result;
  }
  if ((type1.isa<mlir::Float32Type>() && type2.isa<mlir::aten::IntType>())) {
    mlir::Value value = m_OpBuilder.create<mlir::aten::CastOp>(
        v2.getLoc(), type2,
        mlir::aten::CastPredicateAttr::get(m_OpBuilder.getContext(),
                                           mlir::aten::CastPredicate::int_to_float),
        v2);
    result.emplace_back(v1);
    result.emplace_back(value);
    return result;
  }

  // case 2.
  // TODO

  result.emplace_back(v1);
  result.emplace_back(v2);
  return result;
}

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
  for (auto& item : declarationCtxs) { visit(item); }
  for (auto& item : functionDeclCtxs) { visit(item); }
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
  int __line = ctx->Function()->getSymbol()->getLine();
  int __row = ctx->Function()->getSymbol()->getCharPositionInLine();
  // get the location
  mlir::Location location = loc(__line, __row);

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
        printf("[ Erro ] %d:%d Key: %s is not supported or can not be apllied to Boolean.\n",
               __line, __row, sig.c_str());
        exit(-1);
      }
    } else if (item->False_()) {
      if (!funcFlags.setFlagsKV(sig, false)) {
        printf("[ Erro ] %d:%d Key: %s is not supported or can not be apllied to Boolean.\n",
               __line, __row, sig.c_str());
        exit(-1);
      }
    } else {
      auto strRetValue = std::any_cast<VisitorParserReturn>(visit(item->expression()));
      if (!strRetValue.isa(VisitorParserReturnType::kStringLiteral)) {
        printf("[ Erro ] %d:%d You'r trying to assign a value with non-string type.\n", __line,
               __row);
        exit(-1);
      }
      if (!funcFlags.setFlagsKV(sig, strRetValue.getValue<std::string>())) {
        printf("[ Erro ] %d:%d Key: %s has no option %s\n", __line, __row, sig.c_str(),
               strRetValue.getValue<std::string>().c_str());
        exit(-1);
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

  llvm::SmallVector<mlir::DictionaryAttr> _ub;
  llvm::SmallVector<mlir::NamedAttribute> _attrs;

  auto extraEx = mlir::aten::ExtFuncAttr::get(m_OpBuilder.getContext(),
                                              funcFlags.genDictAttrs(m_OpBuilder.getContext()));

  if (ctx->block()) {
    m_OpBuilder.setInsertionPointToEnd(m_TheModule.getBody());

    // TODO WAIT: Support Package and Function rename

    // Generate a fucntion operator
    auto op = m_OpBuilder.create<mlir::aten::FuncOp>(location, funcName, funcTy, _attrs, _ub);
    op.setExtraAttrsAttr(extraEx);

    // Register function symbol to Global Symbol Table
    utils::AtenFunctionSymbolPayload __payload;
    __payload.funcScope = utils::AtenFunctionType::kGeneral;
    __payload.funcType = funcTy;
    __payload.funcOp = op;
    m_curSymbolTable->registerFuncSymbol(funcName, __payload);

    if (isPublic) {
      mlir::SymbolTable::setSymbolVisibility(op, mlir::SymbolTable::Visibility::Public);
      op.setPublic();
    } else {
      mlir::SymbolTable::setSymbolVisibility(op, mlir::SymbolTable::Visibility::Private);
      op.setPrivate();
    }
    mlir::Block* entryBlock = op.addEntryBlock();
    m_OpBuilder.setInsertionPointToStart(entryBlock);

    // Create a new symbol table belong to this function
    m_curSymbolTable->createVarSymbolTableOnTop();

    // Register Function argument name to symbol table.
    size_t argsLen = entryBlock->getNumArguments();
    for (size_t i = 0; i < argsLen; ++i) {
      m_curSymbolTable->registerVarSymbol(std::get<0>(payload.parameters[i]),
                                          entryBlock->getArguments()[i],
                                          utils::VarSymbolKind::kFuncArgument);
    }

    // Register to CodeGenCtx
    Ps.PushFuncStmt(&op);

    // ------ Wait Block visit Done ------
    visit(ctx->block());
    // ----------- Block visit Done ------

    // check if this function is returned or need return void type.
    if (!Ps.IsFuncHasReturned()) { m_OpBuilder.create<mlir::aten::ReturnOp>(location); }

    // Pop the symbol table belong to this function
    m_curSymbolTable->deleteVarSymbolTableOnTop();

    // Pop state of CodeGenCtx
    Ps.Pop();

    return VisitorParserReturn();
  } else /*no function body*/ {
    m_OpBuilder.setInsertionPointToEnd(m_TheModule.getBody());

    // TODO WAIT: Support Package and Function rename
    auto op = m_OpBuilder.create<mlir::aten::FuncOp>(location, funcName, funcTy, _attrs, _ub);

    // Register function symbol to Global Symbol Table
    utils::AtenFunctionSymbolPayload __payload;
    __payload.funcScope = utils::AtenFunctionType::kGeneral;
    __payload.funcType = funcTy;
    __payload.funcOp = op;
    m_curSymbolTable->registerFuncSymbol(funcName, __payload);

    // important!!!
    op.setExtraAttrsAttr(extraEx);

    if (isPublic) {
      mlir::SymbolTable::setSymbolVisibility(op, mlir::SymbolTable::Visibility::Private);
      printf("[ Erro ] %d:%d fucntion declaration with no function body can only be made as "
             "private.\n",
             __line, __row);
      exit(-1);
    } else {
      mlir::SymbolTable::setSymbolVisibility(op, mlir::SymbolTable::Visibility::Private);
      op.setPrivate();
    }
  }
  // no need to register to symbol table. Using mlir's symbol table is enough.
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// signature: LeftBrace statementList? RightBrace;
//
// All done. Code Freezed!!!
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitBlock(AutoTenV1Parser::BlockContext* ctx) {
  visit(ctx->LeftBrace());

  for (auto item : ctx->statementList()->statement()) { visit(item); }

  visit(ctx->RightBrace());
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// signature:
// statement:
//	declaration
//	| labeledStmt
//	| simpleStmt
//	| returnStmt
//	| breakStmt
//	| continueStmt
//	| gotoStmt
//	| fallthroughStmt
//	| block
//	| ifStmt
//	| switchStmt
//	| forStmt
//  | pforStmt
//	| whileStmt
//	| doWhileStmt;
//
// All done. Code Freezed!!!
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitStatement(AutoTenV1Parser::StatementContext* ctx) {
  if (ctx->declaration())
    visit(ctx->declaration());
  else if (ctx->simpleStmt())
    visit(ctx->simpleStmt());
  else if (ctx->returnStmt())
    visit(ctx->returnStmt());
  else if (ctx->breakStmt())
    visit(ctx->breakStmt());
  else if (ctx->continueStmt())
    visit(ctx->continueStmt());
  else if (ctx->gotoStmt())
    visit(ctx->gotoStmt());
  else if (ctx->fallthroughStmt())
    visit(ctx->fallthroughStmt());
  else if (ctx->block())
    visit(ctx->block());
  else if (ctx->ifStmt())
    visit(ctx->ifStmt());
  else if (ctx->switchStmt())
    visit(ctx->switchStmt());
  else if (ctx->forStmt())
    visit(ctx->forStmt());
  else if (ctx->pforStmt())
    visit(ctx->pforStmt());
  else if (ctx->whileStmt())
    visit(ctx->whileStmt());
  else if (ctx->doWhileStmt())
    visit(ctx->doWhileStmt());
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// returnStmt: Return expressionList?;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitReturnStmt(AutoTenV1Parser::ReturnStmtContext* ctx) {
  int __line = ctx->Return()->getSymbol()->getLine();
  int __row = ctx->Return()->getSymbol()->getCharPositionInLine();
  // get the location
  mlir::Location location = loc(__line, __row);
  visit(ctx->Return());

  if (ctx->expressionList()) {
    auto value =
        std::any_cast<VisitorParserReturn>(visit(ctx->expressionList())).getValue<mlir::Value>();

    m_OpBuilder.create<mlir::aten::ReturnOp>(location, value);
  } else {
    m_OpBuilder.create<mlir::aten::ReturnOp>(location);
  }

  Ps.SetFuncHasReturned();

  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// simpleStmt:
// 	incDecStmt
// 	| assignment
// 	| expressionStmt
// 	| shortVarDecl;
//
// All done. Code Freezed
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitSimpleStmt(AutoTenV1Parser::SimpleStmtContext* ctx) {
  if (ctx->incDecStmt()) {
    visit(ctx->incDecStmt());
  } else if (ctx->assignment()) {
    visit(ctx->assignment());
  } else if (ctx->expressionStmt()) {
    visit(ctx->expressionStmt());
  } else if (ctx->shortVarDecl()) {
    visit(ctx->shortVarDecl());
  }
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// incDecStmt: expression (PlusPlus | MinusMinus);
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitIncDecStmt(AutoTenV1Parser::IncDecStmtContext* ctx) {
  Ps.PushIncDecStmt();
  auto valuePtr =
      std::any_cast<VisitorParserReturn>(visit(ctx->expression())).getValue<mlir::Value>();
  Ps.Pop();

  auto value = m_OpBuilder.create<mlir::aten::LoadOp>(valuePtr.getLoc(), valuePtr);

  if (ctx->PlusPlus()) {
    int __line = ctx->PlusPlus()->getSymbol()->getLine();
    int __col = ctx->PlusPlus()->getSymbol()->getCharPositionInLine();

    mlir::Location location = loc(__line, __col);
    mlir::Value result;

    if (value.getType().isa<mlir::aten::IntType>()) {
      result = m_OpBuilder.create<mlir::aten::UnaryOp>(
          location,
          mlir::aten::UnaryOpPredicateAttr::get(m_OpBuilder.getContext(),
                                                mlir::aten::UnaryOpPredicate::Inc),
          value);
    } else if (value.getType().isa<mlir::FloatType>()) {
      // TODO
    } else {
      // FIXME throw error.
      return VisitorParserReturn();
    }

    // store to value;
    m_OpBuilder.create<mlir::aten::StoreOp>(location, result, valuePtr);

  }  // TODO else if(ctx->MinusMinus) {}
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// whileStmt: While LeftParen (expression) RightParen block;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitWhileStmt(AutoTenV1Parser::WhileStmtContext* ctx) {
  visit(ctx->While());
  visit(ctx->LeftParen());

  int __line = ctx->While()->getSymbol()->getLine();
  int __row = ctx->While()->getSymbol()->getCharPositionInLine();
  mlir::Location location = loc(__line, __row);

  // For and While are all loops. They can share same parser state.
  Ps.PushForStmt();
  // build while loop
  m_OpBuilder.create<mlir::aten::LoopOp>(
      location, mlir::aten::LoopOpPredict::While, /*cond Body*/
      [&](mlir::OpBuilder& builder, mlir::Location loc) {
        visit(ctx->expression());
        builder.create<mlir::aten::YieldOp>(loc);
      },
      /*Main Body*/
      [&](mlir::OpBuilder& builder, mlir::Location loc) {
        m_curSymbolTable->createVarSymbolTableOnTop();
        visit(ctx->block());
        m_curSymbolTable->deleteVarSymbolTableOnTop();
        if (!Ps.IsForHadTerminated()) { builder.create<mlir::aten::YieldOp>(loc); }
      },
      /*Step Body*/
      [&](mlir::OpBuilder& builder, mlir::Location loc) {
        // do nothing.
        builder.create<mlir::aten::YieldOp>(loc);
      });
  Ps.Pop();
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// assignment: expressionList assign_op expressionList;
//
// assign_op: (
// 		Plus
// 		| Minus
// 		| Or
// 		| Caret
// 		| Star
// 		| Div
// 		| Mod
// 		| LeftShift
// 		| RightShift
// 		| And
// 	)? Assign;
//
// Example:
// 1. c = a + b. Done.
// 2. dst[0][0] = src[0][0] + src2[0][0]
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitAssignment(AutoTenV1Parser::AssignmentContext* ctx) {
  int __line = ctx->assign_op()->Assign()->getSymbol()->getLine();
  int __row = ctx->assign_op()->Assign()->getSymbol()->getCharPositionInLine();
  mlir::Location location = loc(__line, __row);

  // I use this state to record if we are parsing left hand side value.
  // If we are doing so, than any value from operandName() returned is pointer
  // Else operandName() will call aten.load()
  Ps.PushAssignStmt();
  auto lhs =
      std::any_cast<VisitorParserReturn>(visit(ctx->expressionList()[0])).getValue<mlir::Value>();
  Ps.Pop();

  auto rhs =
      std::any_cast<VisitorParserReturn>(visit(ctx->expressionList()[1])).getValue<mlir::Value>();

  if (!lhs.getType().isa<mlir::MemRefType>()) {
    m_OpBuilder.create<mlir::aten::StoreOp>(location, rhs, lhs);
  } else /*the lhs type is memref or memref-like type*/ {
    // create memref store op
    m_OpBuilder.create<mlir::memref::StoreOp>(location, rhs, lhs, Ps.GetCurSliceIndex());
  }
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// ifStmt:
// 	If LeftParen (
// 		expression
// 		| eos expression
// 		| simpleStmt eos expression
// 	) RightParen block (Else (ifStmt | block))?;
//
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitIfStmt(AutoTenV1Parser::IfStmtContext* ctx) {
  int __line = ctx->If()->getSymbol()->getLine();
  int __row = ctx->If()->getSymbol()->getCharPositionInLine();

  mlir::Location location = loc(__line, __row);

  visit(ctx->If());
  visit(ctx->LeftParen());

  mlir::Value ConditionValue;

  if (ctx->simpleStmt()) {
    // TODO
  } else if (ctx->eos()) {
    // TODO
  } else {
    ConditionValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression())).getValue<mlir::Value>();
  }

  if (ctx->Else()) {
    m_OpBuilder.create<mlir::aten::IfOp>(
        location, ConditionValue, /*has else scope*/ true,
        /*then scope*/
        [&](mlir::OpBuilder& builder, mlir::Location loc) {
          Ps.PushIfStmt();
          m_curSymbolTable->createVarSymbolTableOnTop();
          visit(ctx->block()[0]);
          m_curSymbolTable->deleteVarSymbolTableOnTop();
          if (!Ps.IsIfHadTerminated()) { builder.create<mlir::aten::YieldOp>(loc); }
          Ps.Pop();
          m_OpBuilder.setInsertionPointToEnd(m_TheModule.getBody());
        },
        /*else scope*/
        [&](mlir::OpBuilder& builder, mlir::Location loc) {
          Ps.PushIfStmt();
          m_curSymbolTable->createVarSymbolTableOnTop();
          visit(ctx->block()[1]);
          m_curSymbolTable->deleteVarSymbolTableOnTop();
          if (!Ps.IsIfHadTerminated()) { builder.create<mlir::aten::YieldOp>(loc); }
          Ps.Pop();
          m_OpBuilder.setInsertionPointToEnd(m_TheModule.getBody());
        });
  } else {
    m_OpBuilder.create<mlir::aten::IfOp>(
        location, ConditionValue, /*has else scope*/ false,
        /*then scope*/ [&](mlir::OpBuilder& builder, mlir::Location loc) {
          Ps.PushIfStmt();
          m_curSymbolTable->createVarSymbolTableOnTop();
          visit(ctx->block()[0]);
          m_curSymbolTable->deleteVarSymbolTableOnTop();

          if (!Ps.IsIfHadTerminated()) { builder.create<mlir::aten::YieldOp>(loc); }

          Ps.Pop();
          m_OpBuilder.setInsertionPointToEnd(m_TheModule.getBody());
        });
  }

  visit(ctx->RightParen());
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// breakStmt: Break Identifier?;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitBreakStmt(AutoTenV1Parser::BreakStmtContext* ctx) {
  visit(ctx->Break());

  int __line = ctx->Break()->getSymbol()->getLine();
  int __row = ctx->Break()->getSymbol()->getCharPositionInLine();
  mlir::Location location = loc(__line, __row);

  if (Ps.IsInIfScope()) {
    m_OpBuilder.create<mlir::aten::YieldOp>(location, mlir::aten::YieldOpPredict::Break);
    Ps.SetIfHasTerminatedByBreak();
  }

  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// forStmt:
//    For LeftParen (expression? | forClause) RightParen block;
//
// forClause:
//    initStmt = simpleStmt ? eos expression ? eos postStmt = simpleStmt ? ;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitForStmt(AutoTenV1Parser::ForStmtContext* ctx) {
  visit(ctx->For());

  int __line = ctx->For()->getSymbol()->getLine();
  int __row = ctx->For()->getSymbol()->getCharPositionInLine();
  mlir::Location location = loc(__line, __row);

  Ps.PushForStmt();
  if (ctx->expression()) {
    // TODO
  } else if (ctx->forClause()) {
    // init cond + cond + main body + step SHARED Same SymbolTable.
    m_curSymbolTable->createVarSymbolTableOnTop();

    // init cond
    visit(ctx->forClause()->initStmt);

    // build for loop
    m_OpBuilder.create<mlir::aten::LoopOp>(
        location, mlir::aten::LoopOpPredict::For, /*cond Body*/
        [&](mlir::OpBuilder& builder, mlir::Location loc) {
          auto atenBoolValue =
              std::any_cast<VisitorParserReturn>(visit(ctx->forClause()->expression()))
                  .getValue<mlir::Value>();

          // FIXME: for now, I suppose conditional expression will return bool type.
          // auto boolValue = builder.create<mlir::aten::CastOp>(
          //     loc, builder.getI1Type(),
          //     mlir::aten::CastPredicateAttr::get(m_OpBuilder.getContext(),
          //                                        mlir::aten::CastPredicate::bool_to_mlir_i1),
          //     atenBoolValue);

          // store condition
          mlir::Value ptrValue = builder.create<mlir::aten::AllocaOp>(
              location,
              /*address type*/
              mlir::aten::PointerType::get(builder.getContext(), atenBoolValue.getType()),
              /*alloca type*/ atenBoolValue.getType(),
              /*name*/ "__tmp_condition@" + std::to_string(Ps.GetForConditionTmpCnt()),
              /*alignment is 4B*/ builder.getI64IntegerAttr(1));
          builder.create<mlir::aten::StoreOp>(location, atenBoolValue, ptrValue);

          // for loop yield
          builder.create<mlir::aten::YieldOp>(loc);
        },
        /*Main Body*/
        [&](mlir::OpBuilder& builder, mlir::Location loc) {
          visit(ctx->block());
          if (!Ps.IsForHadTerminated()) { builder.create<mlir::aten::YieldOp>(loc); }
        },
        /*Step Body*/
        [&](mlir::OpBuilder& builder, mlir::Location loc) {
          visit(ctx->forClause()->postStmt);
          builder.create<mlir::aten::YieldOp>(loc);
        });
    m_curSymbolTable->deleteVarSymbolTableOnTop();
  }
  Ps.Pop();

  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// pforStmt:
//    Pfor LeftParen (expression? | pforClause) RightParen block;
//
// forClause:
//    shortVarDecl eos operand eos operand;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitPforStmt(AutoTenV1Parser::PforStmtContext* ctx) {
  visit(ctx->Pfor());

  int __line = ctx->Pfor()->getSymbol()->getLine();
  int __row = ctx->Pfor()->getSymbol()->getCharPositionInLine();
  mlir::Location location = loc(__line, __row);

  if (ctx->expression()) {
    // TODO
  } else if (ctx->pforClause()) {
    // init cond + cond + main body + step SHARED Same SymbolTable.
    m_curSymbolTable->createVarSymbolTableOnTop();

    // get aten's lower, upper, step value
    Ps.PushPforClause();
    auto _ptr_lowerBoundValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->pforClause()->shortVarDecl()))
            .getValue<mlir::Value>();
    auto lowerValue = Ps.GetIntLiteral();
    visit(ctx->pforClause()->operand()[0]);
    auto upperValue = Ps.GetIntLiteral();
    visit(ctx->pforClause()->operand()[1]);
    auto stepValue = Ps.GetIntLiteral();
    Ps.Pop();

    Ps.PushParallelForStmt();
    // build affine parallel for loop
    m_OpBuilder.create<mlir::affine::AffineForOp>(
        location, /*lower*/ lowerValue,
        /*upper*/ upperValue,
        /*step*/ stepValue, /*iter args*/ std::nullopt,
        /*body builder*/
        [&](mlir::OpBuilder& opb, mlir::Location location, mlir::Value value,
            mlir::ValueRange valueRange) {
          // update the symbol of lowerbound to value
          auto strSymbol = m_curSymbolTable->getVarValueName(_ptr_lowerBoundValue);
          m_curSymbolTable->updateSymbolKind(strSymbol.value(), utils::VarSymbolKind::kPfor);
          m_curSymbolTable->updateVarSymbol(strSymbol.value(), value);
          visit(ctx->block());
          if (!Ps.IsParallelForHadTerminated()) {
            // build affine yield
            m_OpBuilder.create<mlir::affine::AffineYieldOp>(location);
          }
        });

    // delete Var symbol table.
    m_curSymbolTable->deleteVarSymbolTableOnTop();
  }
  Ps.Pop();

  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// shortVarDecl: identifierList DeclareAssign expressionList;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitShortVarDecl(AutoTenV1Parser::ShortVarDeclContext* ctx) {
  int __line = ctx->DeclareAssign()->getSymbol()->getLine();
  int __col = ctx->DeclareAssign()->getSymbol()->getCharPositionInLine();

  mlir::Location location = loc(__line, __col);

  mlir::Value value =
      std::any_cast<VisitorParserReturn>(visit(ctx->expressionList())).getValue<mlir::Value>();
  std::string valueName =
      std::any_cast<VisitorParserReturn>(visit(ctx->identifierList())).getValue<std::string>();

  int64_t alignement;

  if (value.getType().isa<mlir::aten::IntType>()) {
    alignement = value.getType().dyn_cast<mlir::aten::IntType>().getWidth() / 8;
  } else if (value.getType().isa<mlir::FloatType>()) {
    alignement = value.getType().dyn_cast<mlir::FloatType>().getWidth() / 8;
  } else if (value.getType().isa<mlir::aten::BoolType>()) {
    alignement = 1;
  }  // TODO

  mlir::Value ptrValue = m_OpBuilder.create<mlir::aten::AllocaOp>(
      location,
      /*address type*/ mlir::aten::PointerType::get(m_OpBuilder.getContext(), value.getType()),
      /*alloca type*/ value.getType(), /*name*/ valueName,
      /*alignment is 4B*/ m_OpBuilder.getI64IntegerAttr(alignement));

  m_curSymbolTable->registerVarSymbol(valueName, ptrValue, utils::VarSymbolKind::kNormal);

  if (Ps.IsInPforClause()) { return VisitorParserReturn(ptrValue); }

  m_OpBuilder.create<mlir::aten::StoreOp>(location, value, ptrValue);
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// signature: parameters ArrowReturnType result | parameters;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitSignature(AutoTenV1Parser::SignatureContext* ctx) {
  auto payload = std::any_cast<VisitorParserReturn>(visit(ctx->parameters()))
                     .getValue<FuncParameterAndReturn>();

  // TODO parse result.
  if (!ctx->ArrowReturnType()) {
    mlir::Type resultTy = mlir::aten::VoidType::get(m_OpBuilder.getContext());
    payload.ret = {"", resultTy, /*has identifier*/ false};
  } else {
    // FIXME: now we just visit type_
    auto resultTy =
        std::any_cast<VisitorParserReturn>(visit(ctx->result()->type_())).getValue<mlir::Type>();
    payload.ret = {"", resultTy, /*has identifier*/ false};
  }

  return VisitorParserReturn(payload);
}

//===----------------------------------------------------------------------===//
// parameters:
//	LeftParen (parameterDecl (Comma parameterDecl)* Comma?)? RightParen;
//
// All done. Code Freezed!!!
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitParameters(AutoTenV1Parser::ParametersContext* ctx) {
  visit(ctx->LeftParen());

  FuncParameterAndReturn payload;

  auto paras = ctx->parameterDecl();
  for (auto item : paras) {
    auto ty = std::any_cast<VisitorParserReturn>(visit(item->type_())).getValue<mlir::Type>();
    std::string name;
    bool hasIdentifier = false;

    if (item->Ellipsis()) {
      int __line = item->Ellipsis()->getSymbol()->getLine();
      int __row = item->Ellipsis()->getSymbol()->getCharPositionInLine();
      printf("[ Erro ] %d:%d nncv not support mutable argument list right now.\n", __line, __row);
    }
    if (item->identifierList()) {
      name =
          std::any_cast<VisitorParserReturn>(visit(item->identifierList())).getValue<std::string>();
    }
    payload.parameters.emplace_back(name, ty, /*has identifier*/ hasIdentifier);
  }

  visit(ctx->RightParen());

  return VisitorParserReturn(payload);
}

//===----------------------------------------------------------------------===//
// declaration : typeDecl | varDecl;
//
// All done. Code Freezed!!!
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitDeclaration(AutoTenV1Parser::DeclarationContext* ctx) {
  if (ctx->typeDecl()) { visit(ctx->typeDecl()); }
  if (ctx->varDecl()) { return visit(ctx->varDecl()); }
  return VisitorParserReturn();
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
  std::string pkgName = removeQuotationMark(ctx->StringLiteral()->getText());
  // change the module name in mlir to package name.
  if (!isPackageNameIsMain(pkgName)) {
    std::string moduleName = "pkg_" + pkgName;
    auto sa = mlir::StringAttr::get(m_TheModule->getContext(), moduleName);
    m_TheModule->setAttr("sym_name", sa);
  } else {
    std::string moduleName = "__main";
    auto sa = mlir::StringAttr::get(m_TheModule->getContext(), moduleName);
    m_TheModule->setAttr("sym_name", sa);
  }
  // create a symbol table for the package(module or to say).
  if (utils::AtenSymbolTable::getInstance().getSymbolRefOfModule(pkgName) == nullptr) {
    m_curSymbolTable = utils::AtenSymbolTable::getInstance().createSymbolRefOfModule(pkgName);
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
//
// FIXME: Struct is not support yet.
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitStructType(AutoTenV1Parser::StructTypeContext* ctx) {
  visit(ctx->Struct());
  visit(ctx->LeftBrace());

  llvm::SmallVector<mlir::Type, 8> tys;
  utils::AtenStructSymbolPayload symbolPayload;

  for (auto item : ctx->fieldDecl()) {
    bool isPublic = (item->parent->getText() == "pub");
    std::string varName =
        std::any_cast<VisitorParserReturn>(visit(item->identifierList())).getValue<std::string>();
    mlir::Type ty = std::any_cast<VisitorParserReturn>(visit(item->type_())).getValue<mlir::Type>();
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
        "varSpec.size() != 1. nncv-c synatic only support single variable specifier, such as "
        "`var "
        "a int32;`. The [LeftParen (varSpec eos)* RightParen] pattern is not support yet.");
  }
  auto theVarSpec = varSpec[0];

  int __line = ctx->Var()->getSymbol()->getLine();
  int __row = ctx->Var()->getSymbol()->getCharPositionInLine();

  // get the symbol name in identifier list.
  auto symbolNameAny = std::any_cast<VisitorParserReturn>(
      visit(theVarSpec->identifierList()));  // TODO identifier list on working
  std::string symbolName;
  if (symbolNameAny.isa(VisitorParserReturnType::kStringLiteral)) {
    symbolName = symbolNameAny.getValue<std::string>();
  } else {
    printf("[ error ] %d:%d symbol name can't cast to string literal\n", __line, __row);
    exit(-1);
  }

  // get the identifier list's position
  mlir::Location location = loc(theVarSpec->identifierList()->getStart()->getLine(),
                                theVarSpec->identifierList()->getStart()->getCharPositionInLine());

  // build values.
  auto type = std::any_cast<VisitorParserReturn>(visit(theVarSpec->type_())).getValue<mlir::Type>();

  // case 1. declare int type
  if (type.isa<mlir::aten::IntType>()) {
    int64_t alignement = type.dyn_cast<mlir::aten::IntType>().getWidth() / 8;
    if (!theVarSpec->Assign()) {
      // Alloca a Int Type on the top of Stack
      mlir::Value value = m_OpBuilder.create<mlir::aten::AllocaOp>(
          location, /*address type*/ mlir::aten::PointerType::get(m_OpBuilder.getContext(), type),
          /*alloca type*/ type, /*name*/ symbolName,
          /*alignment is 4B*/ m_OpBuilder.getI64IntegerAttr(alignement));

      m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
      return VisitorParserReturn(value);
    } else {
      /* TODO if this expr return a mlir::Value. We just need to store this value;*/
      auto exprAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->expressionList()));
      if (exprAny.isa(VisitorParserReturnType::kMlirValue)) {
        auto value = exprAny.getValue<mlir::Value>();

        // TODO if value's type is mismatch with type, do cast.

        m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
        return VisitorParserReturn(value);
      }
      /*if the return is just a int literal. I use `ConstantOp` to create one*/
      if (exprAny.isa(VisitorParserReturnType::kFloatLiteral)
          || exprAny.isa(VisitorParserReturnType::kIntLiteral)) {
        int64_t intValue;
        if (exprAny.isa(VisitorParserReturnType::kFloatLiteral)) {
          intValue = (int64_t)exprAny.getValue<float>();
        } else if (exprAny.isa(VisitorParserReturnType::kIntLiteral)) {
          intValue = exprAny.getValue<int64_t>();
        }
        mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(
            location, type, mlir::aten::IntAttr::get(type, intValue));
        m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
        return VisitorParserReturn(value);
      }
      printf("[ error ] %d:%d can't handle this int type declaration.\n", __line, __row);
      exit(-1);
    }
  }

  // case 2. declare Float type
  if (type.isa<mlir::FloatType>()) {
    int64_t alignement = type.dyn_cast<mlir::FloatType>().getWidth() / 8;
    if (!theVarSpec->Assign()) {
      // Alloca a Int Type on the top of Stack
      mlir::Value value = m_OpBuilder.create<mlir::aten::AllocaOp>(
          location, /*address type*/ mlir::aten::PointerType::get(m_OpBuilder.getContext(), type),
          /*alloca type*/ type, /*name*/ symbolName,
          /*alignment is 4B*/ m_OpBuilder.getI64IntegerAttr(alignement));

      m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
      return VisitorParserReturn(value);
    } else {
      /* TODO if this expr return a mlir::Value. We just need to store this value;*/
      auto exprAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->expressionList()));
      if (exprAny.isa(VisitorParserReturnType::kMlirValue)) {
        auto value = exprAny.getValue<mlir::Value>();

        // TODO if value's type is mismatch with type, do cast.

        m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
        return VisitorParserReturn(value);
      }
      /*if the return is just a int literal. I use `ConstantOp` to create one*/
      if (exprAny.isa(VisitorParserReturnType::kFloatLiteral)
          || exprAny.isa(VisitorParserReturnType::kIntLiteral)) {
        double floatValue;
        if (exprAny.isa(VisitorParserReturnType::kFloatLiteral)) {
          floatValue = exprAny.getValue<double>();
        } else if (exprAny.isa(VisitorParserReturnType::kIntLiteral)) {
          floatValue = (double)exprAny.getValue<int64_t>();
        }
        mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(
            location, type, mlir::FloatAttr::get(type, floatValue));
        m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
        return VisitorParserReturn(value);
      }
      printf("[ error ] %d:%d can't handle this float type declaration.\n", __line, __row);
      exit(-1);
    }
  }

  // case 3. declare bool type
  if (type.isa<mlir::aten::BoolType>()) {
    int64_t alignement = 4;
    if (!theVarSpec->Assign()) {
      // Alloca a Int Type on the top of Stack
      mlir::Value value = m_OpBuilder.create<mlir::aten::AllocaOp>(
          location, /*address type*/ mlir::aten::PointerType::get(m_OpBuilder.getContext(), type),
          /*alloca type*/ type, /*name*/ symbolName,
          /*alignment is 4B*/ m_OpBuilder.getI64IntegerAttr(alignement));

      m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
      return VisitorParserReturn(value);
    } else {
      /* if this expr return a mlir::Value. We just need to record this value;*/
      auto exprAny = std::any_cast<VisitorParserReturn>(visit(theVarSpec->expressionList()));
      if (exprAny.isa(VisitorParserReturnType::kMlirValue)) {
        auto value = exprAny.getValue<mlir::Value>();

        // TODO if value's type is mismatch with type, do cast.

        m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
        return VisitorParserReturn(value);
      }
      /*if the return is just a int literal. I use `ConstantOp` to create one*/
      if (exprAny.isa(VisitorParserReturnType::kFloatLiteral)
          || exprAny.isa(VisitorParserReturnType::kIntLiteral)
          || exprAny.isa(VisitorParserReturnType::kBooleanLiteral)) {
        bool boolValue = true;
        if (exprAny.isa(VisitorParserReturnType::kFloatLiteral)) {
          boolValue = exprAny.getValue<double>();
        } else if (exprAny.isa(VisitorParserReturnType::kIntLiteral)) {
          boolValue = (double)exprAny.getValue<int64_t>();
        } else if (exprAny.isa(VisitorParserReturnType::kBooleanLiteral)) {
          boolValue = exprAny.getValue<bool>();
        }
        mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(
            location, type,
            mlir::aten::BoolAttr::get(m_OpBuilder.getContext(), type.cast<mlir::aten::BoolType>(),
                                      boolValue));
        m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
        return VisitorParserReturn(value);
      }
    }
  }

  // TODO case 4. declare char type
  // TODO case 5. declare string type
  // TODO case 6. declare void type
  // TODO case 7. declare tensor type

  // case 8. declare ConstantArray type
  if (type.isa<mlir::aten::ArrayType>()) {
    if (!theVarSpec->Assign()) {
      mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(
          location, type, mlir::aten::ZeroAttr::get(m_OpBuilder.getContext(), type));
      m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
      return VisitorParserReturn(value);
    } else {
      // TODO
    }
  }

  // case 9. declare Tensor type(MemRef)
  if (type.isa<mlir::MemRefType>()) {
    mlir::Value value =
        m_OpBuilder.create<mlir::memref::AllocOp>(location, type.dyn_cast<mlir::MemRefType>());
    m_curSymbolTable->registerVarSymbol(symbolName, value, utils::VarSymbolKind::kNormal);
  } else if (type.isa<mlir::UnrankedMemRefType>()) {
    // TODO
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
// FIXME: Actually Tensor(in this lang) will translate to memref in mlir
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
    Ps.SetExpressionLiteralGenMlirValue(false);
    for (auto item : ctx->expression()) {
      dimsExpr.emplace_back(std::any_cast<VisitorParserReturn>(visit(item)));
    }
    Ps.SetExpressionLiteralGenMlirValue(true);
  }
  llvm::SmallVector<int64_t, 4> memRefShape;
  for (auto item : dimsExpr) {
    if (item.isa(VisitorParserReturnType::kIntLiteral)) {
      memRefShape.emplace_back(item.getValue<int64_t>());
    }
  }

  auto memrefType = mlir::MemRefType::get(memRefShape, type);

  return VisitorParserReturn(memrefType);
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
// primaryExpr:
// 	operand
// 	| conversion
// 	| methodExpr
// 	| primaryExpr (
// 		Dot Identifier
// 		| index
// 		| slice_
// 		| typeAssertion
// 		| arguments
// 	);
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitPrimaryExpr(AutoTenV1Parser::PrimaryExprContext* ctx) {
  if (ctx->operand()) { return visit(ctx->operand()); }
  if (ctx->conversion()) { return visit(ctx->conversion()); }
  if (ctx->methodExpr()) { return visit(ctx->methodExpr()); }
  if (ctx->primaryExpr()) {
    auto visitRet = std::any_cast<VisitorParserReturn>(visit(ctx->primaryExpr()));
    if (ctx->Dot()) {
      // TODO
    } else if (ctx->index()) {
      return parseIndex_(ctx->index(), visitRet);
    } else if (ctx->slice_()) {
      return parseSlice_(ctx->slice_(), visitRet);
    } else if (ctx->typeAssertion()) {
      // TODO
    } else if (ctx->arguments()) {
      return parseArgument(ctx->arguments(), visitRet);
    }
  }
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// operand:
// 	literal
// 	| operandName
// 	| LeftParen expression RightParen;
//
// All done. Code Freezed!!!
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitOperand(AutoTenV1Parser::OperandContext* ctx) {
  if (ctx->literal()) {
    return visit(ctx->literal());
  } else if (ctx->operandName()) {
    return visit(ctx->operandName());
  } else if (ctx->LeftParen()) {
    return visit(ctx->expression());
  }
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// literal: basicLit | compositeLit | functionLit;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitLiteral(AutoTenV1Parser::LiteralContext* ctx) {
  if (ctx->basicLit()) { return visit(ctx->basicLit()); }
  if (ctx->compositeLit()) { return visit(ctx->compositeLit()); }
  if (ctx->functionLit()) { return visit(ctx->functionLit()); }
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// basicLit:
// 	Nilptr
// 	| IntegerLiteral
// 	| StringLiteral
// 	| FloatingLiteral
// 	| CharacterLiteral;
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitBasicLit(AutoTenV1Parser::BasicLitContext* ctx) {
  if (ctx->Nilptr()) {
    // TODO
  }
  if (ctx->IntegerLiteral()) {
    int __line = ctx->IntegerLiteral()->getSymbol()->getLine();
    int __col = ctx->IntegerLiteral()->getSymbol()->getCharPositionInLine();

    mlir::Location location = loc(__line, __col);

    std::string integerStr = ctx->IntegerLiteral()->getText();
    long long num = std::stoll(integerStr);

    Ps.SetIntLiteral(num);

    if (Ps.IsExpressionLiteralGenMlirValue()) {
      auto intType = mlir::aten::IntType::get(m_OpBuilder.getContext(), 32, true);
      auto attri = mlir::aten::IntAttr::get(intType, num);

      mlir::Value value = m_OpBuilder.create<mlir::aten::ConstantOp>(location, intType, attri);
      return VisitorParserReturn(value);
    } else {
      return VisitorParserReturn(num);
    }
  }
  if (ctx->StringLiteral()) {
    // TODO
  }
  if (ctx->FloatingLiteral()) {
    // TODO
  }
  if (ctx->CharacterLiteral()) {
    // TODO
  }
  return VisitorParserReturn();
}

//===----------------------------------------------------------------------===//
// operandName: Identifier;
//
// All done. Code Freezed!!!
//===----------------------------------------------------------------------===//
std::any AutoTen2MlirVisitor::visitOperandName(AutoTenV1Parser::OperandNameContext* ctx) {
  int __line = ctx->Identifier()->getSymbol()->getLine();
  int __row = ctx->Identifier()->getSymbol()->getCharPositionInLine();
  mlir::Location location = loc(__line, __row);

  auto _value = m_curSymbolTable->getVarValueSymbol(ctx->Identifier()->getText());
  if (!_value.has_value()) { return VisitorParserReturn(ctx->Identifier()->getText()); }

  if (m_curSymbolTable->getVarValueSymbolKind(ctx->Identifier()->getText())
      == utils::VarSymbolKind::kPfor) {
    return VisitorParserReturn(_value.value());
  }

  // i++, return pointer of i
  if (m_curSymbolTable->getVarValueSymbolKind(ctx->Identifier()->getText())
          == utils::VarSymbolKind::kNormal
      && Ps.IsInIncDecStmt()) {
    return VisitorParserReturn(_value.value());
  }

  // a[i, j]. The i and j should be load.
  if (m_curSymbolTable->getVarValueSymbolKind(ctx->Identifier()->getText())
          == utils::VarSymbolKind::kNormal
      && Ps.IsInSliceStmt()) {
    mlir::Value value = m_OpBuilder.create<mlir::aten::LoadOp>(location, _value.value());
    return VisitorParserReturn(value);
  }

  // memref should keep as ptr
  // func foo(a int32). a should keep as value, not ptr;
  if (m_curSymbolTable->getVarValueSymbolKind(ctx->Identifier()->getText())
          == utils::VarSymbolKind::kNormal
      && !Ps.IsInAssignStmt()
      && !(_value->getType().isa<mlir::MemRefType>()
           || _value->getType().isa<mlir::UnrankedMemRefType>())) {
    mlir::Value value = m_OpBuilder.create<mlir::aten::LoadOp>(location, _value.value());
    return VisitorParserReturn(value);
  }

  return VisitorParserReturn(_value.value());
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
    return visit(ctx->primaryExpr());
  }
  // unary_op = (Plus | Minus | Not | Caret | Star | And) expression
  else if (ctx->unary_op) {
    // TODO
  }
  // expression mul_op = (Star|Div|Mod|LeftShift|RightShift|And)expression
  else if (ctx->mul_op) {
    auto mulOpType = ctx->mul_op->getType();
    mlir::Value lhsValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression()[0])).getValue<mlir::Value>();
    mlir::Value rhsValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression()[1])).getValue<mlir::Value>();

    mlir::Location location = loc(ctx->mul_op->getLine(), ctx->mul_op->getCharPositionInLine());

    if (mulOpType == m_Lexer.Star) {
      // TODO bulder is incorrect.
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
          location,
          mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::BinOpPredicate::Mul),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (mulOpType == m_Lexer.Div) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
          location,
          mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::BinOpPredicate::Div),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (mulOpType == m_Lexer.Mod) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
          location,
          mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::BinOpPredicate::Mod),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (mulOpType == m_Lexer.LeftShift) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::ShiftOp>(location, lhsValue, rhsValue,
                                                                     m_OpBuilder.getUnitAttr());
      return VisitorParserReturn(retValue);
    } else if (mulOpType == m_Lexer.RightShift) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::ShiftOp>(location, lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (mulOpType == m_Lexer.And) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
          location,
          mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::BinOpPredicate::And),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    }
  }
  // expression add_op = (Plus|Minus|Or|Caret) expression
  else if (ctx->add_op) {
    auto addOpType = ctx->add_op->getType();
    mlir::Value lhsValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression()[0])).getValue<mlir::Value>();
    mlir::Value rhsValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression()[1])).getValue<mlir::Value>();

    mlir::Location location = loc(ctx->add_op->getLine(), ctx->add_op->getCharPositionInLine());
    if (addOpType == m_Lexer.Plus) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
          location,
          mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::BinOpPredicate::Add),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (addOpType == m_Lexer.Minus) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
          location,
          mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::BinOpPredicate::Sub),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (addOpType == m_Lexer.Or) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
          location,
          mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::BinOpPredicate::Or),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (addOpType == m_Lexer.Caret) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::BinOp>(
          location,
          mlir::aten::BinOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::BinOpPredicate::Xor),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    }

  }
  // expression rel_op = (Equal|NotEqual|Less|LessEqual|Greater|GreaterEqual) expression
  else if (ctx->rel_op) {
    auto relOpType = ctx->rel_op->getType();
    mlir::Value lhsValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression()[0])).getValue<mlir::Value>();
    mlir::Value rhsValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression()[1])).getValue<mlir::Value>();

    mlir::Location location = loc(ctx->rel_op->getLine(), ctx->rel_op->getCharPositionInLine());

    if (relOpType == m_Lexer.Equal) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
          location,
          mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpOpPredicate::eq),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (relOpType == m_Lexer.NotEqual) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
          location,
          mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpOpPredicate::ne),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (relOpType == m_Lexer.Less) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
          location,
          mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpOpPredicate::lt),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (relOpType == m_Lexer.LessEqual) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
          location,
          mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpOpPredicate::le),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (relOpType == m_Lexer.Greater) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
          location,
          mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpOpPredicate::gt),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    } else if (relOpType == m_Lexer.GreaterEqual) {
      mlir::Value retValue = m_OpBuilder.create<mlir::aten::CmpOp>(
          location,
          mlir::aten::CmpOpPredicateAttr::get(m_OpBuilder.getContext(),
                                              mlir::aten::CmpOpPredicate::ge),
          lhsValue, rhsValue);
      return VisitorParserReturn(retValue);
    }

  }
  // expression AndAnd expression
  else if (ctx->AndAnd()) {
    mlir::Value lhsValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression()[0])).getValue<mlir::Value>();
    mlir::Value rhsValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression()[1])).getValue<mlir::Value>();

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
    mlir::Value lhsValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression()[0])).getValue<mlir::Value>();
    mlir::Value rhsValue =
        std::any_cast<VisitorParserReturn>(visit(ctx->expression()[1])).getValue<mlir::Value>();

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
// NOTE: To be simplified. Array type do not support length infer. Such as `a [...]int = {1, 2,
// 3}`
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