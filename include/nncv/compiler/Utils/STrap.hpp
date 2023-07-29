/// This file will be included multiple times
#pragma once

#include <cstdio>
#include <cstdlib>

namespace nncv {
namespace compiler {
namespace utils {

// TODO using trap stack to get function stack infomation. and call trap_reduce when abort()
// occurred

#define ERROR_CHECK_TABLE_LEN 32

enum class ErrorType : int {
  kUnkown = 0,
  kLexerError = 1,
};

static inline void __HandlerUnkwonErr() {}

static inline void __HandlerLexerErr() {
  std::printf("\n\nLexer error is critical, exit with state 1.(Lexer Error)\n");
  std::exit(1);
}

// TODO

static void (*__error_check_table__[ERROR_CHECK_TABLE_LEN])() = {
    __HandlerUnkwonErr, __HandlerLexerErr,
    // TODO
};

inline void TrapAt(const ErrorType& idx) {
  auto func = (__error_check_table__[(int)idx]);
  (*func)();
}

#undef ERROR_CHECK_TABLE_LEN
}  // namespace utils
}  // namespace compiler
}  // namespace nncv