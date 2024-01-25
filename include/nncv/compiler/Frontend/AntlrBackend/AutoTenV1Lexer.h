
// Generated from ./AutoTenV1Lexer.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"


namespace antlrcpp {


class  AutoTenV1Lexer : public antlr4::Lexer {
public:
  enum {
    IntegerLiteral = 1, CharacterLiteral = 2, FloatingLiteral = 3, StringLiteral = 4, 
    BooleanLiteral = 5, PointerLiteral = 6, UserDefinedLiteral = 7, Int8 = 8, 
    Int16 = 9, Int32 = 10, Int64 = 11, Float32 = 12, Float64 = 13, Char = 14, 
    Bool = 15, String = 16, Tensor = 17, Var = 18, False_ = 19, True_ = 20, 
    Void = 21, Nilptr = 22, Break = 23, Continue = 24, Goto = 25, Fallthrough = 26, 
    If = 27, While = 28, For = 29, Pfor = 30, Else = 31, Do = 32, Switch = 33, 
    Case = 34, Default = 35, Function = 36, Return = 37, Struct = 38, Type = 39, 
    Package = 40, Impl = 41, Public = 42, Sizeof = 43, LeftParen = 44, RightParen = 45, 
    LeftBracket = 46, RightBracket = 47, LeftBrace = 48, RightBrace = 49, 
    Plus = 50, Minus = 51, Star = 52, Div = 53, Mod = 54, Caret = 55, And = 56, 
    Or = 57, Tilde = 58, Not = 59, Assign = 60, DeclareAssign = 61, Less = 62, 
    Greater = 63, LeftShift = 64, RightShift = 65, NotEqual = 66, Equal = 67, 
    LessEqual = 68, GreaterEqual = 69, AndAnd = 70, OrOr = 71, PlusPlus = 72, 
    MinusMinus = 73, Comma = 74, ArrowReturnType = 75, Colon = 76, Dot = 77, 
    DotStar = 78, ArrowStar = 79, At = 80, Semi = 81, Map = 82, Ellipsis = 83, 
    Import = 84, Identifier = 85, DecimalLiteral = 86, OctalLiteral = 87, 
    HexadecimalLiteral = 88, BinaryLiteral = 89, Integersuffix = 90, UserDefinedIntegerLiteral = 91, 
    UserDefinedFloatingLiteral = 92, UserDefinedStringLiteral = 93, UserDefinedCharacterLiteral = 94, 
    Whitespace = 95, Newline = 96, BlockComment = 97, LineComment = 98
  };

  explicit AutoTenV1Lexer(antlr4::CharStream *input);

  ~AutoTenV1Lexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace antlrcpp
