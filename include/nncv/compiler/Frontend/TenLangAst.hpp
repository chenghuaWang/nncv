/**
 * @file TenLangAst.hpp
 * @author chenghua.Wang (chenghua.wang.edu@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-06-01
 *
 * @details Ast impl is reference from clang:
 * https://clang.llvm.org/docs/IntroductionToTheClangAST.html
 *
 * In this file. Coding style follows the llvm toy example.
 * @copyright Copyright (c) 2023
 *
 */
#ifndef NNCV_COMPILER_TEN_LANG_AST_HPP_
#define NNCV_COMPILER_TEN_LANG_AST_HPP_

#pragma once

#if defined(_WIN32) && _MSC_VER < 1900
#error MS Compiler version need higher than 1900
#endif

#include "nncv/compiler/Frontend/TenLangLexer.hpp"

#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/ArrayRef.h"

#include <string>
#include <memory>
#include <vector>
#include <optional>

namespace nncv {
namespace compiler {
namespace frontend {

class ExprAst;

using ExprASTList = std::vector<std::unique_ptr<ExprAst>>;

//===----------------------------------------------------------------------===//
// Actually, the parse tree in antlr does not need a AST. The Concrete Syntax tree
// is already contains full infomation needed to generate IR. But I need to check
// the type and do some symbol check. Those method is hard to implement in visitor
// or listner mode in antlr. In that case, an AST is necessary.
//===----------------------------------------------------------------------===//

typedef struct _location {
  _location(std::shared_ptr<std::string> _FileName, int _Colum, int _Row)
      : FileName(_FileName), Colum(_Colum), Row(_Row) {}
  std::shared_ptr<std::string> FileName;
  int Colum;
  int Row;
} Location;

//===----------------------------------------------------------------------===//
// Base class of all expression node
//===----------------------------------------------------------------------===//
class ExprAst {
 public:
  enum ExprAstKind {
    // function related
    ExprCall = 0,
    ExprReturn,
    // operation
    ExprBinaryOp,
    ExprUnaryOp,
    // ref
    ExprMember,
    // declaration
    ExprGeneralValDel,
    EXprArrayDecl,
    ExprMapDecl,
    ExprStringDel,
    // Literal
    ExprStringLiteral,
    ExprNumberLiteral,
    ExprCharLiteral,
    ExprBoolLiteral,
    // Control Flow
    ExprAssign,
    ExprIf,
    ExprCase,
    ExprWhile,
    ExprDoWhile,
    ExprFor,
    // trivial
    ExprArrayAccess,
  };
  ExprAst(ExprAstKind _Kind, Location _Location)
      : m_Kind(_Kind), m_Location(std::move(_Location)) {}
  virtual ~ExprAst() = default;

  ExprAstKind getKind() const { return m_Kind; }

  const Location& loc() { return m_Location; }

 private:
  const ExprAstKind m_Kind;
  Location m_Location;
};

//===----------------------------------------------------------------------===//
// Expression class for function call. Such as `print(c);`
//===----------------------------------------------------------------------===//
class CallExprAst : public ExprAst {
  std::string callee;
  std::vector<std::unique_ptr<ExprAst>> args;
  std::vector<std::unique_ptr<ExprAst>> attribute;

 public:
  CallExprAst(Location loc, const std::string& callee, std::vector<std::unique_ptr<ExprAst>> args,
              std::vector<std::unique_ptr<ExprAst>> attribute)
      : ExprAst(ExprCall, std::move(loc)),
        callee(callee),
        args(std::move(args)),
        attribute(std::move(attribute)) {}

  llvm::StringRef getCallee() { return callee; }
  llvm::ArrayRef<std::unique_ptr<ExprAst>> getArgs() { return args; }
  llvm::ArrayRef<std::unique_ptr<ExprAst>> getAttribute() { return attribute; }

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprCall; }
};

//===----------------------------------------------------------------------===//
// Expression class for Binary Op. Such as `a + b;`
//===----------------------------------------------------------------------===//
class BinaryExprAst : public ExprAst {
  std::string op;
  std::unique_ptr<ExprAst> lhs, rhs;

 public:
  llvm::StringRef getOp() { return op; }
  ExprAst* getLHS() { return lhs.get(); }
  ExprAst* getRHS() { return rhs.get(); }

  BinaryExprAst(Location loc, const std::string& op, std::unique_ptr<ExprAst> lhs,
                std::unique_ptr<ExprAst> rhs)
      : ExprAst(ExprBinaryOp, std::move(loc)), op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprBinaryOp; }
};

//===----------------------------------------------------------------------===//
// Expression class for Unary Op. Such as `i ++;`. Only `lhs op`.
//===----------------------------------------------------------------------===//
class UnaryExprAst : public ExprAst {
  std::string op;
  std::unique_ptr<ExprAst> lhs;

 public:
  llvm::StringRef getOp() { return op; }
  ExprAst* getLHS() { return lhs.get(); }

  UnaryExprAst(Location loc, const std::string& op, std::unique_ptr<ExprAst> lhs)
      : ExprAst(ExprUnaryOp, std::move(loc)), op(op), lhs(std::move(lhs)) {}

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprUnaryOp; }
};

//===----------------------------------------------------------------------===//
// Expression class for Memeber. Such as `var a Tensor; a.type`; `type` is a member.
// But you should notice that MemberExprAst is just for struct. It can't call
// a function.
//===----------------------------------------------------------------------===//
class MemberExprAst : public ExprAst {
  std::unique_ptr<ExprAst> structLi;
  std::unique_ptr<ExprAst> member;

 public:
  ExprAst* getStructLi() { return structLi.get(); }
  ExprAst* getMember() { return member.get(); }

  MemberExprAst(Location loc, std::unique_ptr<ExprAst> structLi, std::unique_ptr<ExprAst> member)
      : ExprAst(ExprMember, std::move(loc)),
        structLi(std::move(structLi)),
        member(std::move(member)) {}

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprMember; }
};

//===----------------------------------------------------------------------===//
// Expression class for array. Such as `var a [10]int16 = {10, 1, 2, 3};`
//===----------------------------------------------------------------------===//
class ArrayDeclExprAst : public ExprAst {
  std::string arrayName;
  std::string typeName;
  std::optional<std::unique_ptr<ExprAst>> initArray;

 public:
  ArrayDeclExprAst(Location loc, const std::string& arrayName, const std::string& typeName,
                   std::optional<std::unique_ptr<ExprAst>> initArray)
      : ExprAst(EXprArrayDecl, std::move(loc)),
        arrayName(arrayName),
        typeName(typeName),
        initArray(std::move(initArray)) {}
  llvm::StringRef getArrayName() { return arrayName; }
  llvm::StringRef getTypeName() { return typeName; }
  std::optional<ExprAst*> getInitArray() {
    if (initArray.has_value()) return initArray->get();
    return std::nullopt;
  }

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == EXprArrayDecl; }
};

//===----------------------------------------------------------------------===//
// Expression class for array. Such as `return 1+1;`
//===----------------------------------------------------------------------===//
class ReturnExprAst : public ExprAst {
  std::optional<std::unique_ptr<ExprAst>> expr;

 public:
  ReturnExprAst(Location loc, std::optional<std::unique_ptr<ExprAst>> expr)
      : ExprAst(ExprReturn, std::move(loc)), expr(std::move(expr)) {}

  std::optional<ExprAst*> getExpr() {
    if (expr.has_value()) return expr->get();
    return std::nullopt;
  }

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprReturn; }
};

//===----------------------------------------------------------------------===//
// Expression class for map. Such as `var foo map[string]int32;`
//===----------------------------------------------------------------------===//
class MapDeclExprAst : public ExprAst {
  std::string mapName;
  std::string keyType;
  std::string valueType;
  std::optional<std::unique_ptr<ExprAst>> initMap;

 public:
  MapDeclExprAst(Location loc, const std::string& mapName, const std::string& keyType,
                 const std::string& valueType, std::optional<std::unique_ptr<ExprAst>> initMap)
      : ExprAst(ExprMapDecl, std::move(loc)),
        mapName(mapName),
        keyType(keyType),
        valueType(valueType),
        initMap(std::move(initMap)) {}
  llvm::StringRef getMapName() { return mapName; }
  llvm::StringRef getKeyType() { return keyType; }
  llvm::StringRef getValueType() { return valueType; }
  std::optional<ExprAst*> getInitMap() {
    if (initMap.has_value()) return initMap->get();
    return std::nullopt;
  }

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprMapDecl; }
};

//===----------------------------------------------------------------------===//
// Expression class for string. Such as `var a string = "name";`
//===----------------------------------------------------------------------===//
class StringExprAst : public ExprAst {
  std::string stringName;
  std::optional<std::unique_ptr<ExprAst>> initString;

 public:
  StringExprAst(Location loc, const std::string& stringName,
                std::optional<std::unique_ptr<ExprAst>> initString)
      : ExprAst(ExprStringDel, std::move(loc)),
        stringName(stringName),
        initString(std::move(initString)) {}

  llvm::StringRef getStringName() { return stringName; }
  std::optional<ExprAst*> getInitString() {
    if (initString.has_value()) return initString->get();
    return std::nullopt;
  }

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprStringDel; }
};

//===----------------------------------------------------------------------===//
// Expression class for string literal. Such as `"name"`
//===----------------------------------------------------------------------===//
class StringLiteralExprAst : public ExprAst {
  std::string stringLiteral;

 public:
  StringLiteralExprAst(Location loc, const std::string& stringLiteral)
      : ExprAst(ExprStringLiteral, std::move(loc)), stringLiteral(stringLiteral) {}
  llvm::StringRef getStringLiteral() { return stringLiteral; }

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprStringLiteral; }
};

//===----------------------------------------------------------------------===//
// Expression class for number literal. Such as `10.0`
//===----------------------------------------------------------------------===//
class NumberLiteralExprAst : public ExprAst {
 public:
  int8_t intValue8;
  int16_t intValue16;
  int32_t intValue32;
  int64_t intValue64;
  float floatValue32;
  double floatValue64;

  enum NumberType {
    int8,
    int16,
    int32,
    int64,
    float32,
    float64,
  };

  NumberType type;

  NumberLiteralExprAst(Location loc, int8_t intValue8)
      : ExprAst(ExprStringLiteral, std::move(loc)), intValue8(intValue8), type(int8) {}

  NumberLiteralExprAst(Location loc, int16_t intValue16)
      : ExprAst(ExprStringLiteral, std::move(loc)), intValue16(intValue16), type(int16) {}

  NumberLiteralExprAst(Location loc, int32_t intValue32)
      : ExprAst(ExprStringLiteral, std::move(loc)), intValue32(intValue32), type(int32) {}

  NumberLiteralExprAst(Location loc, int64_t intValue64)
      : ExprAst(ExprStringLiteral, std::move(loc)), intValue64(intValue64), type(int64) {}

  NumberLiteralExprAst(Location loc, float floatValue32)
      : ExprAst(ExprStringLiteral, std::move(loc)), floatValue32(floatValue32), type(float32) {}

  NumberLiteralExprAst(Location loc, double floatValue64)
      : ExprAst(ExprStringLiteral, std::move(loc)), floatValue64(floatValue64), type(float64) {}

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprNumberLiteral; }
};

//===----------------------------------------------------------------------===//
// Expression class for char literal. Such as `'A'`
//===----------------------------------------------------------------------===//
class CharLiteralExprAst : public ExprAst {
  char charLiteral;

 public:
  CharLiteralExprAst(Location loc, char charLiteral)
      : ExprAst(ExprStringLiteral, std::move(loc)), charLiteral(charLiteral) {}
  char getCharLiteral() { return charLiteral; }

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprCharLiteral; }
};

//===----------------------------------------------------------------------===//
// Expression class for bool literal. Such as `true`
//===----------------------------------------------------------------------===//
class BoolLiteralExprAst : public ExprAst {
  bool boolLiteral;

 public:
  BoolLiteralExprAst(Location loc, bool boolLiteral)
      : ExprAst(ExprStringLiteral, std::move(loc)), boolLiteral(boolLiteral) {}
  bool getBoolLiteral() { return boolLiteral; }

  /// LLVM style RTTI
  static bool classof(const ExprAst* c) { return c->getKind() == ExprBoolLiteral; }
};

//    ExprBoolLiteral

//===----------------------------------------------------------------------===//
// The context of this AST. It response for doing things below:
// 1. Manage Global parameters symbol table
// 2. Manage symbol table for each struct's impl
// 3. Manage symbol table when AST walker step in a function
// 4. Some compiler flags check before middle end and back end.
//===----------------------------------------------------------------------===//
class AutoTenAstContext {};

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_TEN_LANG_AST_HPP_