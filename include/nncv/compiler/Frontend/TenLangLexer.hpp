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
enum AutoTenToken : int {
  // charater used.
  kTokSemicolon = ';',
  kTokParentheseOpen = '(',
  kTokParentheseClose = ')',
  kTokBracketOpen = '{',
  kTokBracketClose = '}',
  kTokSbracketOpen = '[',
  kTokSbracketClose = ']',
  kTokAt = '@',

  // end of file
  kTokEOF = -1,

  // command
  kTokReturn = -2,
  kTokFunc = -3,

  // primary
  kTokIdentifier = -4,
  kTokNumber = -5
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