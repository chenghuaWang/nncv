#include "nncv/compiler//Utils/STrap.hpp"
#include "nncv/compiler/Utils/CliFormatOutput.hpp"
#include "nncv/compiler/Frontend/TenLangLexer.hpp"
#include <stdexcept>

namespace nncv {
namespace compiler {
namespace fronted {

AutoTenDictionary::AutoTenDictionary() {
  /// Operators
  AddToken("=", std::make_tuple(AutoTenTokenValue::kEqual, AutoTenTokenType::kOperators, 2));
  AddToken(">=",
           std::make_tuple(AutoTenTokenValue::kGreaterOrEqual, AutoTenTokenType::kOperators, 2));
  AddToken(">", std::make_tuple(AutoTenTokenValue::kGreaterThen, AutoTenTokenType::kOperators, 2));
  AddToken("<=", std::make_tuple(AutoTenTokenValue::kLessOrEqual, AutoTenTokenType::kOperators, 2));
  AddToken("<", std::make_tuple(AutoTenTokenValue::kLessThen, AutoTenTokenType::kOperators, 2));
  AddToken("+", std::make_tuple(AutoTenTokenValue::kPlus, AutoTenTokenType::kOperators, 10));
  AddToken("-", std::make_tuple(AutoTenTokenValue::kMinus, AutoTenTokenType::kOperators, 10));
  AddToken("*", std::make_tuple(AutoTenTokenValue::kMultiplyOrDeReference,
                                AutoTenTokenType::kOperators, 20));
  AddToken("&", std::make_tuple(AutoTenTokenValue::kReference, AutoTenTokenType::kOperators, 20));
  AddToken("/", std::make_tuple(AutoTenTokenValue::kDivide, AutoTenTokenType::kOperators, 20));

  /// Delimiters
  AddToken(",", std::make_tuple(AutoTenTokenValue::kComma, AutoTenTokenType::kDelimiter, -1));
  AddToken(":", std::make_tuple(AutoTenTokenValue::kColon, AutoTenTokenType::kDelimiter, -1));
  AddToken("(",
           std::make_tuple(AutoTenTokenValue::kParentheseOpen, AutoTenTokenType::kDelimiter, -1));
  AddToken(")",
           std::make_tuple(AutoTenTokenValue::kParentheseClose, AutoTenTokenType::kDelimiter, -1));
  AddToken("{", std::make_tuple(AutoTenTokenValue::kBracketOpen, AutoTenTokenType::kDelimiter, -1));
  AddToken("}",
           std::make_tuple(AutoTenTokenValue::kBracketClose, AutoTenTokenType::kDelimiter, -1));
  AddToken("[",
           std::make_tuple(AutoTenTokenValue::kSbracketOpen, AutoTenTokenType::kDelimiter, -1));
  AddToken("]",
           std::make_tuple(AutoTenTokenValue::kSbracketClose, AutoTenTokenType::kDelimiter, -1));
  AddToken("<",
           std::make_tuple(AutoTenTokenValue::kAngleBracketOpen, AutoTenTokenType::kDelimiter, -1));
  AddToken(">", std::make_tuple(AutoTenTokenValue::kAngleBracketClose, AutoTenTokenType::kDelimiter,
                                -1));
  AddToken(".", std::make_tuple(AutoTenTokenValue::kPeriod, AutoTenTokenType::kDelimiter, -1));
  AddToken(";", std::make_tuple(AutoTenTokenValue::kSemicolon, AutoTenTokenType::kDelimiter, -1));
  AddToken("@", std::make_tuple(AutoTenTokenValue::kAt, AutoTenTokenType::kDelimiter, -1));

  /// Keywords-logical
  AddToken("and", std::make_tuple(AutoTenTokenValue::kAnd, AutoTenTokenType::kKeywords, 20));
  AddToken("or", std::make_tuple(AutoTenTokenValue::kOr, AutoTenTokenType::kKeywords, 10));
  AddToken("xor", std::make_tuple(AutoTenTokenValue::kXor, AutoTenTokenType::kKeywords, 10));
  AddToken("not", std::make_tuple(AutoTenTokenValue::kNot, AutoTenTokenType::kKeywords, 40));
  AddToken("<<", std::make_tuple(AutoTenTokenValue::kShl, AutoTenTokenType::kKeywords, 20));
  AddToken(">>", std::make_tuple(AutoTenTokenValue::kShr, AutoTenTokenType::kKeywords, 20));
  AddToken("%", std::make_tuple(AutoTenTokenValue::kMod, AutoTenTokenType::kKeywords, 20));

  /// Keywords-control-flow
  AddToken("if", std::make_tuple(AutoTenTokenValue::kIf, AutoTenTokenType::kKeywords, -1));
  AddToken("nil", std::make_tuple(AutoTenTokenValue::kNil, AutoTenTokenType::kKeywords, -1));
  AddToken("else", std::make_tuple(AutoTenTokenValue::kElse, AutoTenTokenType::kKeywords, -1));
  AddToken("while", std::make_tuple(AutoTenTokenValue::kWhile, AutoTenTokenType::kKeywords, -1));
  AddToken("do", std::make_tuple(AutoTenTokenValue::kDo, AutoTenTokenType::kKeywords, -1));
  AddToken("->", std::make_tuple(AutoTenTokenValue::kReturnValue, AutoTenTokenType::kKeywords, -1));

  /// Keywords function, struct, impl
  AddToken("func", std::make_tuple(AutoTenTokenValue::kFunc, AutoTenTokenType::kKeywords, -1));
  AddToken("struct", std::make_tuple(AutoTenTokenValue::kStruct, AutoTenTokenType::kKeywords, -1));
  AddToken("impl", std::make_tuple(AutoTenTokenValue::kImpl, AutoTenTokenType::kKeywords, -1));

  /// I/O
  AddToken("read", std::make_tuple(AutoTenTokenValue::kRead, AutoTenTokenType::kKeywords, -1));
  AddToken("write", std::make_tuple(AutoTenTokenValue::kWrite, AutoTenTokenType::kKeywords, -1));

  /// Types
  AddToken("var", std::make_tuple(AutoTenTokenValue::kVar, AutoTenTokenType::kKeywords, -1));
  AddToken("string",
           std::make_tuple(AutoTenTokenValue::kString, AutoTenTokenType::kTypeString, -1));
  AddToken("Tensor",
           std::make_tuple(AutoTenTokenValue::kTensor, AutoTenTokenType::kTypeTensor, -1));
  AddToken("int8", std::make_tuple(AutoTenTokenValue::kInt8, AutoTenTokenType::kTypeInteger, -1));
  AddToken("int16", std::make_tuple(AutoTenTokenValue::kInt16, AutoTenTokenType::kTypeInteger, -1));
  AddToken("int32", std::make_tuple(AutoTenTokenValue::kInt32, AutoTenTokenType::kTypeInteger, -1));
  AddToken("float32",
           std::make_tuple(AutoTenTokenValue::kFloat32, AutoTenTokenType::kTypeReal, -1));
  AddToken("float64",
           std::make_tuple(AutoTenTokenValue::kFloat64, AutoTenTokenType::kTypeReal, -1));
  AddToken("bool", std::make_tuple(AutoTenTokenValue::kBool, AutoTenTokenType::kTypeBool, -1));
  AddToken("file", std::make_tuple(AutoTenTokenValue::kFile, AutoTenTokenType::kKeywords, -1));
  AddToken("char", std::make_tuple(AutoTenTokenValue::kChar, AutoTenTokenType::kTypeChar, -1));
}

void AutoTenDictionary::AddToken(std::string name,
                                 std::tuple<AutoTenTokenValue, AutoTenTokenType, int> TokenMeta) {
  m_Dictionary.insert(std::pair<decltype(name), decltype(TokenMeta)>(name, TokenMeta));
}

std::tuple<AutoTenTokenType, AutoTenTokenValue, int> AutoTenDictionary::Lookup(
    const std::string& name) const {
  AutoTenTokenValue TokenValue = AutoTenTokenValue::kUnused;
  AutoTenTokenType TokenType = AutoTenTokenType::kIdentifier;
  int Precedence = -1;
  auto Iter = m_Dictionary.find(name);

  if (Iter != m_Dictionary.end()) {
    TokenValue = std::get<0>(Iter->second);
    TokenType = std::get<1>(Iter->second);
    Precedence = std::get<2>(Iter->second);
  }

  return std::make_tuple(TokenType, TokenValue, Precedence);
}

bool AutoTenDictionary::HaveToken(const std::string& name) const {
  auto Iter = m_Dictionary.find(name);

  if (Iter != m_Dictionary.end()) { return true; }

  return false;
}

AutoTenLexer::AutoTenLexer(const std::string& SrcFileName)
    : m_FileName(std::make_shared<std::string>(SrcFileName)),
      m_Line(1),
      m_Column(0),
      m_CurrentChar(0),
      m_State(AutoTenLexerState::kNone) {
  m_IfStream.open(*m_FileName);
  if (m_IfStream.fail()) {
    throw std::runtime_error("When trying to open" + (*m_FileName) + " Error Occurs.");
  }
}

void AutoTenLexer::GetNextChar() {
  m_CurrentChar = m_IfStream.get();

  if (m_CurrentChar == '\n') {
    m_Line++;
    m_Column = 0;
  } else {
    m_Column++;
  }
}

char AutoTenLexer::PeekChar() {
  char c = m_IfStream.peek();
  return c;
}

void AutoTenLexer::AddToBuffer(char c) { m_Buffer.push_back(c); }

void AutoTenLexer::ReduceBuffer() { m_Buffer.pop_back(); }

void AutoTenLexer::CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                               std::string Name, int SymbolPrecedence) {
  m_Token = AutoTenToken(Tt, Tv, Loc, Name, SymbolPrecedence);
  m_Buffer.clear();
  m_State = AutoTenLexerState::kNone;
}

void AutoTenLexer::CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                               int8_t IntValue, std::string Name) {
  m_Token = AutoTenToken(Tt, Tv, Loc, IntValue, Name);
  m_Buffer.clear();
  m_State = AutoTenLexerState::kNone;
}

void AutoTenLexer::CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                               int16_t IntValue, std::string Name) {
  m_Token = AutoTenToken(Tt, Tv, Loc, IntValue, Name);
  m_Buffer.clear();
  m_State = AutoTenLexerState::kNone;
}

void AutoTenLexer::CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                               int32_t IntValue, std::string Name) {
  m_Token = AutoTenToken(Tt, Tv, Loc, IntValue, Name);
  m_Buffer.clear();
  m_State = AutoTenLexerState::kNone;
}

void AutoTenLexer::CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                               int64_t IntValue, std::string Name) {
  m_Token = AutoTenToken(Tt, Tv, Loc, IntValue, Name);
  m_Buffer.clear();
  m_State = AutoTenLexerState::kNone;
}

void AutoTenLexer::CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                               float FloatValue, std::string Name) {
  m_Token = AutoTenToken(Tt, Tv, Loc, FloatValue, Name);
  m_Buffer.clear();
  m_State = AutoTenLexerState::kNone;
}

void AutoTenLexer::CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                               double FloatValue, std::string Name) {
  m_Token = AutoTenToken(Tt, Tv, Loc, FloatValue, Name);
  m_Buffer.clear();
  m_State = AutoTenLexerState::kNone;
}

void AutoTenLexer::CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                               bool BoolValue, std::string Name) {
  m_Token = AutoTenToken(Tt, Tv, Loc, BoolValue, Name);
  m_Buffer.clear();
  m_State = AutoTenLexerState::kNone;
}

void AutoTenLexer::CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                               char CharValue, std::string Name) {
  m_Token = AutoTenToken(Tt, Tv, Loc, CharValue, Name);
  m_Buffer.clear();
  m_State = AutoTenLexerState::kNone;
}

void AutoTenLexer::CreateToken(AutoTenTokenType Tt, AutoTenTokenValue Tv, const Location& Loc,
                               const std::string& StrVale, std::string Name) {
  m_Token = AutoTenToken(Tt, Tv, Loc, StrVale, Name);
  m_Buffer.clear();
  m_State = AutoTenLexerState::kNone;
}

AutoTenToken AutoTenLexer::GetNextToken() {
  bool matched = false;
  do {
    if (m_State != AutoTenLexerState::kNone) { matched = true; }

    switch (m_State) {
      case AutoTenLexerState::kNone: GetNextChar(); break;
      case AutoTenLexerState::kEof: HandleEOFState(); break;
      case AutoTenLexerState::kIdentifier: HandleIdentifierState(); break;
      case AutoTenLexerState::kNumber: HandleNumberState(); break;
      case AutoTenLexerState::kString: HandleStringState(); break;
      case AutoTenLexerState::kOperation: HandleOperationState(); break;
      default: {
        throw std::logic_error("When Lexer parse next token, lexer state mismatch.");
      }
    }
    if (m_State == AutoTenLexerState::kNone) {
      // TODO preprocess();
      if (m_IfStream.eof()) {
        m_State = AutoTenLexerState::kEof;
      } else {
        if (std::isalpha(m_CurrentChar) || (m_CurrentChar == '_')) {
          m_State = AutoTenLexerState::kIdentifier;
        } else if (std::isdigit(m_CurrentChar)) {
          m_State = AutoTenLexerState::kNumber;
        } else if (m_CurrentChar == '\"') {
          m_State = AutoTenLexerState::kString;
        } else {
          m_State = AutoTenLexerState::kOperation;
        }
      }
    }
  } while (!matched);

  return m_Token;
}

void AutoTenLexer::HandleEOFState() {
  m_Loc = GetTokenLocation();
  CreateToken(AutoTenTokenType::kEof, AutoTenTokenValue::kUnused, m_Loc, std::string("EOF"), -1);
  m_IfStream.close();
}

void AutoTenLexer::HandleNumberState() {
  m_Loc = GetTokenLocation();
  bool IsFloat = false;
  bool IsExponent = false;

  int NumberSystem = 10;

  enum class NumberState { kInteger, kFloat, kExponent, kDone };
  NumberState ThisNumberState = NumberState::kInteger;

  do {
    switch (ThisNumberState) {
      case NumberState::kInteger: {
        if (NumberSystem == 10) { HandleDigit(); }
        break;
      }
      case NumberState::kFloat: {
        HandleFloat();
        IsFloat = true;
        break;
      }
      case NumberState::kExponent: {
      }
      case NumberState::kDone: break;
    }

    if (m_CurrentChar == '.') {
      if (IsFloat) {
        utils::CliFormatOutput::ErrorAt(*m_FileName, m_Line, m_Column,
                                        "Float type should have just onr dot, but found two.");
        utils::TrapAt(utils::ErrorType::kLexerError);
      }
      if (IsExponent) {
        utils::CliFormatOutput::ErrorAt(
            *m_FileName, m_Line, m_Column,
            "Scientist number representation in AutoTen can not have dot.");
        utils::TrapAt(utils::ErrorType::kLexerError);
      }
      if (NumberSystem != 10) {
        utils::CliFormatOutput::ErrorAt(*m_FileName, m_Line, m_Column,
                                        "Float only support number system 10.");
        utils::TrapAt(utils::ErrorType::kLexerError);
      }
      ThisNumberState = NumberState::kFloat;
    } else if (m_CurrentChar == 'E' || m_CurrentChar == 'e') {
      if (IsExponent) {
        utils::CliFormatOutput::ErrorAt(*m_FileName, m_Line, m_Column,
                                        "Scientist presentation can not have more than one e / E");
        utils::TrapAt(utils::ErrorType::kLexerError);
      }
      ThisNumberState = NumberState::kExponent;
    } else {
      ThisNumberState = NumberState::kDone;
    }
  } while (ThisNumberState != NumberState::kDone);
  // TODO
}

void AutoTenLexer::HandleDigit() {
  AddToBuffer(m_CurrentChar);
  GetNextChar();

  while (std::isdigit(m_CurrentChar)) {
    AddToBuffer(m_CurrentChar);
    GetNextChar();
  }
}

void AutoTenLexer::HandleFloat() {
  if (!std::isdigit(PeekChar())) {
    utils::CliFormatOutput::ErrorAt(*m_FileName, m_Line, m_Column,
                                    "Float number part should be numbers");
    utils::TrapAt(utils::ErrorType::kLexerError);
  }

  AddToBuffer(m_CurrentChar);
  GetNextChar();

  while (std::isdigit(m_CurrentChar)) {
    AddToBuffer(m_CurrentChar);
    GetNextChar();
  }
}

void AutoTenLexer::HandleStringState() {
  m_Loc = GetTokenLocation();
  // eat "
  GetNextChar();

  while (true) {
    if (m_CurrentChar == '\"') { break; }

    AddToBuffer(m_CurrentChar);
    GetNextChar();
  }

  // eat "
  GetNextChar();

  if (m_Buffer.size() == 1) {
    CreateToken(AutoTenTokenType::kTypeChar, AutoTenTokenValue::kUnused, m_Loc, m_Buffer.at(0),
                m_Buffer);
  } else {
    CreateToken(AutoTenTokenType::kTypeString, AutoTenTokenValue::kUnused, m_Loc, m_Buffer,
                m_Buffer);
  }
}

void AutoTenLexer::HandleOperationState() {
  m_Loc = GetTokenLocation();
  AddToBuffer(m_CurrentChar);
  AddToBuffer(PeekChar());

  if (m_Dictionary.HaveToken(m_Buffer)) {
    GetNextChar();
  } else {
    ReduceBuffer();
  }

  auto TokenMeta = m_Dictionary.Lookup(m_Buffer);
  CreateToken(std::get<0>(TokenMeta), std::get<1>(TokenMeta), m_Loc, m_Buffer,
              std::get<2>(TokenMeta));
  GetNextChar();
}

void AutoTenLexer::HandleIdentifierState() {
  m_Loc = GetTokenLocation();

  AddToBuffer(m_CurrentChar);
  GetNextChar();

  /// While current char is not '_', number or alpha.
  while (std::isalnum(m_CurrentChar) || m_CurrentChar == '_') {
    AddToBuffer(m_CurrentChar);
    GetNextChar();
  }

  /// Check if this identifier is in KeyWords
  auto TokenMeta = m_Dictionary.Lookup(m_Buffer);
  CreateToken(std::get<0>(TokenMeta), std::get<1>(TokenMeta), m_Loc, m_Buffer,
              std::get<2>(TokenMeta));
}

}  // namespace fronted
}  // namespace compiler
}  // namespace nncv