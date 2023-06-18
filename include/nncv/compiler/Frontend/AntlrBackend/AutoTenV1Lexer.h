
// Generated from ../AutoTenV1Lexer.g4 by ANTLR 4.13.0

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
    If = 27, While = 28, For = 29, Else = 30, Do = 31, Switch = 32, Case = 33, 
    Default = 34, Function = 35, Return = 36, Struct = 37, Type = 38, Package = 39, 
    Impl = 40, Public = 41, Sizeof = 42, LeftParen = 43, RightParen = 44, 
    LeftBracket = 45, RightBracket = 46, LeftBrace = 47, RightBrace = 48, 
    Plus = 49, Minus = 50, Star = 51, Div = 52, Mod = 53, Caret = 54, And = 55, 
    Or = 56, Tilde = 57, Not = 58, Assign = 59, DeclareAssign = 60, Less = 61, 
    Greater = 62, LeftShift = 63, RightShift = 64, NotEqual = 65, Equal = 66, 
    LessEqual = 67, GreaterEqual = 68, AndAnd = 69, OrOr = 70, PlusPlus = 71, 
    MinusMinus = 72, Comma = 73, ArrowReturnType = 74, Colon = 75, Dot = 76, 
    DotStar = 77, ArrowStar = 78, At = 79, Semi = 80, Map = 81, Ellipsis = 82, 
    Identifier = 83, DecimalLiteral = 84, OctalLiteral = 85, HexadecimalLiteral = 86, 
    BinaryLiteral = 87, Integersuffix = 88, UserDefinedIntegerLiteral = 89, 
    UserDefinedFloatingLiteral = 90, UserDefinedStringLiteral = 91, UserDefinedCharacterLiteral = 92, 
    Whitespace = 93, Newline = 94, BlockComment = 95, LineComment = 96
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
