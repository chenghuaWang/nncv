/**
 * @file TenLangLexer.hpp
 * @author chenghua.Wang (chenghua.wang.edu@gmail.com)
 * @brief The Lexer of AutoTen. Based on nested case statement
 * @version 0.1
 * @date 2023-05-22
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef NNCV_COMPILER_TEN_LANG_LEXER_HPP_
#define NNCV_COMPILER_TEN_LANG_LEXER_HPP_

#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/SmallVector.h"

#include <memory>
#include <string>

#include <stdint.h>

namespace nncv {
namespace compiler {
namespace fronted {

//===----------------------------------------------------------------------===//
// Charater reserved
//===----------------------------------------------------------------------===//
static llvm::SmallVector<std::string, 12> __CharacterReserved__ = {
    "func",    "return",  "Tensor", "int16", "int32", "float16",
    "float32", "float64", "bool",   "for",   "while", "Print",
};

//===----------------------------------------------------------------------===//
// Structure definition a location in a file.
//===----------------------------------------------------------------------===//
struct Location {
  std::shared_ptr<std::string> file;  ///< filename.
  int line;                           ///< line number.
  int col;                            ///< column number.
};

//===----------------------------------------------------------------------===//
// The Token Lexer returned
//===----------------------------------------------------------------------===//
enum AutoTenTokenType : int {
  kTypeInteger = 0,
  kTypeReal,
  kTypeBool,
  kTypeChar,
  kTypeString,
  kTypeTensor,

  kIdentifier,  // such as abc
  kKeywords,    // such as if
  kOperators,   // such as  + - * /
  kDelimiter,   // such as ,
  kEof,         // end of file
  kTypeUnknow
};

enum AutoTenTokenValue : int {
  // Auto Tenser lang v 0.0.1

  // Control
  kAnd = -1,      /// logical &&
  kOr = -2,       /// logical ||
  kNot = -3,      /// logical !
  kFor = -4,      /// Control Flow for(...){} loop
  kDo = -5,       /// Control Flow do{...}while(...) loop
  kIf = -6,       /// Control Flow if(...) {}
  kElse = -7,     /// Control Flow if(...) {} else {}
  kWhile = -8,    /// Control Flow while(...) {}
  kFunc = -9,     /// Function define
  kImpl = -10,    /// The Implementation of funcs for Structure
  kReturn = -11,  /// Return something

  // Built in types
  kTensor = -12,
  kInt8 = -13,
  kInt16 = -14,
  kInt32 = -15,
  kFloat32 = -16,
  kFloat64 = -17,
  kBool = -18,
  kString = -19,
  kChar = -20,
  kStruct = -21,
  kFile = -64,

  // I/O
  kWrite = -22,
  kRead = -23,

  // Normal Symbols
  kSemicolon = ';',
  kParentheseOpen = '(',
  kParentheseClose = ')',
  kBracketOpen = '{',
  kBracketClose = '}',
  kSbracketOpen = '[',
  kSbracketClose = ']',
  kAt = '@',
  kComma = ',',
  kColon = ':',
  kPeriod = '.',
  kPlus = '+',
  kMinus = '-',
  kMultiplyOrDeReference = '*',
  kReference = '&',
  kDivide = '/',

  // Compare symbols
  kLessOrEqual = -24,     // <=
  kLessThen = -25,        // <
  kGreaterOrEqual = -26,  // >=
  kGreaterThen = -27,     // >
  kEqual = -28,           // ==
  kNotEqual = -29,        // !
  kValueUnknow
};

struct AutoTenToken {
  inline AutoTenToken();
  inline AutoTenToken(AutoTenTokenType type, AutoTenTokenValue value, const Location& location,
                      const std::string& name, int symbolPrecedence) {}
  inline AutoTenTokenType GetTokenType() const { return m_Type; }

 private:
  AutoTenTokenType m_Type;
  AutoTenTokenValue m_Value;
  Location m_Location;
  std::string m_Name;
  int m_SymbolPrecedence;

  // constant value
  int8_t m_kI8;
  int16_t m_kI16;
  int32_t m_kI32;
  int64_t m_kI64;
  float m_kF32;
  double m_kF64;
  std::string m_kString;
};

//===----------------------------------------------------------------------===//
// Lexer Main Class
//===----------------------------------------------------------------------===//
class AutoTenLexer {
 public:
 private:
};

//===----------------------------------------------------------------------===//
// Lexer Buffer
//===----------------------------------------------------------------------===//
class AutoTenLexerBuffer : public AutoTenLexer {
 public:
 private:
};

}  // namespace fronted
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_TEN_LANG_LEXER_HPP_