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

#include <tuple>
#include <map>

#include <iostream>
#include <fstream>

#include <stdint.h>

namespace nncv {
namespace compiler {
namespace frontend {

//===----------------------------------------------------------------------===//
// Structure definition a location in a file.
//===----------------------------------------------------------------------===//
struct Location {
  Location() = default;
  Location(std::shared_ptr<std::string> _Fn, int L, int C) : FileName(_Fn), Line(L), Col(C) {}
  std::shared_ptr<std::string> FileName;  ///< filename.
  int Line;                               ///< line number.
  int Col;                                ///< column number.
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

  kUnused = -1024,

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
  kXor = -66,
  kMod = -67,
  kShl = -68,  /// Shift left
  kShr = -69,  /// Shift right
  kNil = -70,
  kReturnValue = -71,

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
  kVar = -65,  /// Type is auto inferenced.
  kInt64 = -72,

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
  kAngleBracketOpen = '<',
  kAngleBracketClose = '>',
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
  inline AutoTenToken() = default;
  inline AutoTenToken(AutoTenTokenType Type, AutoTenTokenValue Value, const Location& Location,
                      const std::string& Name, int SymbolPrecedence)
      : m_Type(Type),
        m_Value(Value),
        m_Location(Location),
        m_Name(Name),
        m_SymbolPrecedence(SymbolPrecedence) {}
  inline AutoTenToken(AutoTenTokenType Type, AutoTenTokenValue Value, const Location& Location,
                      const std::string& StrValue, std::string Name)
      : m_Type(Type),
        m_Value(Value),
        m_Location(Location),
        m_Name(Name),
        m_SymbolPrecedence(-1),
        m_kString(StrValue) {}
  inline AutoTenToken(AutoTenTokenType Type, AutoTenTokenValue Value, const Location& Location,
                      int8_t Int8Value, std::string Name)
      : m_Type(Type),
        m_Value(Value),
        m_Location(Location),
        m_Name(Name),
        m_SymbolPrecedence(-1),
        m_kI8(Int8Value) {}
  inline AutoTenToken(AutoTenTokenType Type, AutoTenTokenValue Value, const Location& Location,
                      int16_t Int16Value, std::string Name)
      : m_Type(Type),
        m_Value(Value),
        m_Location(Location),
        m_Name(Name),
        m_SymbolPrecedence(-1),
        m_kI16(Int16Value) {}
  inline AutoTenToken(AutoTenTokenType Type, AutoTenTokenValue Value, const Location& Location,
                      int32_t Int32Value, std::string Name)
      : m_Type(Type),
        m_Value(Value),
        m_Location(Location),
        m_Name(Name),
        m_SymbolPrecedence(-1),
        m_kI32(Int32Value) {}
  inline AutoTenToken(AutoTenTokenType Type, AutoTenTokenValue Value, const Location& Location,
                      int64_t Int64Value, std::string Name)
      : m_Type(Type),
        m_Value(Value),
        m_Location(Location),
        m_Name(Name),
        m_SymbolPrecedence(-1),
        m_kI64(Int64Value) {}
  inline AutoTenToken(AutoTenTokenType Type, AutoTenTokenValue Value, const Location& Location,
                      float Float32Value, std::string Name)
      : m_Type(Type),
        m_Value(Value),
        m_Location(Location),
        m_Name(Name),
        m_SymbolPrecedence(-1),
        m_kF32(Float32Value) {}
  inline AutoTenToken(AutoTenTokenType Type, AutoTenTokenValue Value, const Location& Location,
                      double Float64Value, std::string Name)
      : m_Type(Type),
        m_Value(Value),
        m_Location(Location),
        m_Name(Name),
        m_SymbolPrecedence(-1),
        m_kF64(Float64Value) {}
  inline AutoTenToken(AutoTenTokenType Type, AutoTenTokenValue Value, const Location& Location,
                      bool BoolValue, std::string Name)
      : m_Type(Type),
        m_Value(Value),
        m_Location(Location),
        m_Name(Name),
        m_SymbolPrecedence(-1),
        m_kBool(BoolValue) {}
  inline AutoTenToken(AutoTenTokenType Type, AutoTenTokenValue Value, const Location& Location,
                      char CharValue, std::string Name)
      : m_Type(Type),
        m_Value(Value),
        m_Location(Location),
        m_Name(Name),
        m_SymbolPrecedence(-1),
        m_kChar(CharValue) {}

  inline AutoTenTokenType GetTokenType() const { return m_Type; }
  inline AutoTenTokenValue GetTokenValue() const { return m_Value; }
  inline const Location& GetTokenLocation() const { return m_Location; }
  inline std::string GetTokenName() const { return m_Name; }

  inline int GetSymbolPrecedence() const { return m_SymbolPrecedence; }

  inline int8_t GetInt8Value() const { return m_kI8; }
  inline int8_t GetInt16Value() const { return m_kI16; }
  inline int8_t GetInt32Value() const { return m_kI32; }
  inline int8_t GetInt64Value() const { return m_kI64; }
  inline float GetFloat32Value() const { return m_kF32; }
  inline double GetFloat64Value() const { return m_kF64; }
  inline std::string GetStringValue() const { return m_kString; }
  inline bool GetBoolValue() const { return m_kBool; }
  inline char GetCharValue() const { return m_kChar; }

  inline void DebugDump(std::ostream& out = std::cout) const {}

  inline std::string GetIdentifierName() const { return m_Name; }

  inline std::string TokenTypeDescription() const {
    std::string ret;

    switch (m_Type) {
      case AutoTenTokenType::kTypeInteger: {
        switch (m_Value) {
          case AutoTenTokenValue::kInt8: ret = "integer(8 bits)"; break;
          case AutoTenTokenValue::kInt16: ret = "integer(16 bits)"; break;
          case AutoTenTokenValue::kInt32: ret = "integer(32 bits)"; break;
          case AutoTenTokenValue::kInt64: ret = "integer(64 bits)"; break;
          default: break;
        }
      }
      case AutoTenTokenType::kTypeReal: {
        switch (m_Value) {
          case AutoTenTokenValue::kFloat32: ret = "float(32 bits)"; break;
          case AutoTenTokenValue::kFloat64: ret = "float(64 bits)"; break;
          default: break;
        }
      }
      case AutoTenTokenType::kTypeTensor: ret = "tensor"; break;
      case AutoTenTokenType::kTypeBool: ret = "boolean"; break;
      case AutoTenTokenType::kTypeChar: ret = "char"; break;
      case AutoTenTokenType::kTypeString: ret = "string"; break;
      case AutoTenTokenType::kIdentifier: ret = "identifier"; break;
      case AutoTenTokenType::kKeywords: ret = "keywords"; break;
      case AutoTenTokenType::kOperators: ret = "operators"; break;
      case AutoTenTokenType::kDelimiter: ret = "delimiter"; break;
      case AutoTenTokenType::kEof: ret = "eof"; break;
      case AutoTenTokenType::kTypeUnknow: ret = "unknown"; break;
      default: break;
    }
    return ret;
  }
  inline std::string ToString() const {
    return std::string("Token Type: " + TokenTypeDescription() + "Token Name: " + m_Name);
  }

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
  bool m_kBool;
  char m_kChar;
};

//===----------------------------------------------------------------------===//
// Token-Type Dictionary
//===----------------------------------------------------------------------===//
class AutoTenDictionary {
 public:
  AutoTenDictionary();
  std::tuple<AutoTenTokenType, AutoTenTokenValue, int> Lookup(const std::string& name) const;
  bool HaveToken(const std::string& name) const;

 private:
  void AddToken(std::string name, std::tuple<AutoTenTokenValue, AutoTenTokenType, int> TokenMeta);

 private:
  /// token name, token value, token type, precedence.
  std::map<std::string, std::tuple<AutoTenTokenValue, AutoTenTokenType, int>> m_Dictionary;
};

//===----------------------------------------------------------------------===//
// Lexer Main Class
//===----------------------------------------------------------------------===//

enum class AutoTenLexerState {
  kNone = 0,
  kEof,
  kIdentifier,
  kNumber,
  kString,
  kOperation,
};

class AutoTenLexer {
 public:
  explicit AutoTenLexer(const std::string& SrcFileName);

  inline AutoTenToken GetToken() const { return m_Token; }
  AutoTenToken GetNextToken();

 private:
  void GetNextChar();
  char PeekChar();
  void AddToBuffer(char c);
  void ReduceBuffer();
  void CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc, std::string Name,
                   int SymbolPrecedence);
  void CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc, int8_t IntValue,
                   std::string Name);
  void CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc, int16_t IntValue,
                   std::string Name);
  void CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc, int32_t IntValue,
                   std::string Name);
  void CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc, int64_t IntValue,
                   std::string Name);
  void CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc, float FloatValue,
                   std::string Name);
  void CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                   double FloatValue, std::string Name);
  void CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc, bool BoolValue,
                   std::string Name);
  void CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc, char CharValue,
                   std::string Name);
  void CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                   const std::string& StrVale, std::string Name);

  void HandleEOFState();
  void HandleIdentifierState();
  void HandleNumberState();
  void HandleStringState();
  void HandleOperationState();

  /// TODO Preprocess need to binding.

  inline Location GetTokenLocation() const { return Location(m_FileName, m_Line, m_Column); }
  void HandleDigit();
  void HandleFloat();

  std::shared_ptr<std::string> m_FileName;
  std::ifstream m_IfStream;
  int m_Line;
  int m_Column;
  Location m_Loc;
  char m_CurrentChar;
  AutoTenLexerState m_State;
  AutoTenToken m_Token;
  AutoTenDictionary m_Dictionary;
  std::string m_Buffer;
};

//===----------------------------------------------------------------------===//
// Lexer Buffer
//===----------------------------------------------------------------------===//
class AutoTenLexerBuffer : public AutoTenLexer {
 public:
 private:
};

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_TEN_LANG_LEXER_HPP_