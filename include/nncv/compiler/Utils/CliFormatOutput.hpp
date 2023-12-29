/// This file will be included multiple times
#pragma once

#include "fmt/core.h"
#include "fmt/color.h"

namespace nncv {
namespace compiler {
namespace utils {

struct CliFormatOutput {
  static inline void ErrorAt(const std::string& _fn, int _line, int _col,
                             const std::string& _what) {
    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
               fmt::format("[  Err  ]: File {}(Line: {}, Colum{}).\n", _fn, _line, _col));
    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, fmt::format("    ->:{}\n", _what));
    exit(1);
  }

  static inline void Info(const std::string& s) {
    fmt::print(fg(fmt::color::white), fmt::format("[ "));
    fmt::print(fg(fmt::color::green), fmt::format("INFO"));
    fmt::print(fg(fmt::color::white), fmt::format("  ] "));
    fmt::print(fg(fmt::color::white), fmt::format(s));
  }
};

}  // namespace utils
}  // namespace compiler
}  // namespace nncv