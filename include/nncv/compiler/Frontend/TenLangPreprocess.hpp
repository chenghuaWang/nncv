#ifndef NNCV_COMPILER_TEN_LANG_PREPROCESSOR_HPP_
#define NNCV_COMPILER_TEN_LANG_PREPROCESSOR_HPP_

#include "nncv/compiler/Utils/GeneralDag.hpp"

#include <string>
#include <unordered_map>

namespace nncv {
namespace compiler {
namespace frontend {

struct ImportNode : public utils::DagNode<ImportNode> {};

struct __CompilerFlagContext__ {
  bool EnableStd;
  bool EnableNN;
  bool EnableIo;
};

static std::unordered_map<std::string, std::string> __Import2Flags__ = {
    {"std", "@Compiler.Std.Enable"},
    {"nn", "@Compiler.Ops.Extension.Enable"},
    {"io", "@Compiler.io.Enable"},
};

class AutoTenPreprocessor {
 public:
  AutoTenPreprocessor();

  bool PreprocessCompilerFlagsImport();
  bool IsDagImport();
  bool PrepareNormalImports();

  bool Do();

  bool SmallLexerForImport();

 private:
  struct __CompilerFlagContext__ m_CompilerFlags;
};

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_TEN_LANG_PREPROCESSOR_HPP_