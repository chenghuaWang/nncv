// store the op_builder. will pass to other code gen module.
// Also stored some basic data struct using when gen code in antlr or ast.
#ifndef NNCV_COMPILER_CODE_GEN_CTX_HPP_
#define NNCV_COMPILER_CODE_GEN_CTX_HPP_

#include <string>
#include <map>
#include <functional>

namespace nncv {
namespace compiler {
namespace frontend {

//===----------------------------------------------------------------------===//
// Compiler Flags: Global flags.
//===----------------------------------------------------------------------===//
struct CompileFlags {
  CompileFlags() : enableStdExt(true), enableNNCVExt(true), enablePolyOpt(true) {}

  bool enableStdExt;
  bool enableNNCVExt;
  bool enablePolyOpt;
};

//===----------------------------------------------------------------------===//
// Function: Compiler Flags
// TODO: Tile size, mem buffer size.
// @input = ""
// @output = ""
//===----------------------------------------------------------------------===//
class FuncCompilerFlag;

enum class __FuncFlagType : int32_t {
  kKernel_AutoParallel = 0,
  kKernel_Platform = 1,
};

static std::map<std::string, __FuncFlagType> __FuncFlagsKeyCheckTable = {
    {"Kernel.AutoParallel", __FuncFlagType::kKernel_AutoParallel},
    {"Kernel.Platform", __FuncFlagType::kKernel_Platform},
};

class FuncCompilerFlag {
 public:
  FuncCompilerFlag() : asKernelAndEnableParallel(false), deviceType(""){};

  inline bool setFlagsKV(std::string& key, bool value) {
    auto item = __FuncFlagsKeyCheckTable.find(key);
    if (item != __FuncFlagsKeyCheckTable.end()) {
      switch (item->second) {
        case __FuncFlagType::kKernel_AutoParallel: {
          asKernelAndEnableParallel = true;
          return true;
        }
        default: return false;
      }
    }
    return false;
  }

  inline bool setFlagsKV(std::string& key, std::string& value) {
    auto item = __FuncFlagsKeyCheckTable.find(key);
    if (item != __FuncFlagsKeyCheckTable.end()) {
      switch (item->second) {
        case __FuncFlagType::kKernel_Platform: {
          deviceType = value;
          return true;
        }
        default: return false;
      }
    }
    return false;
  }

 private:
  bool asKernelAndEnableParallel;
  std::string deviceType;
};

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_CODE_GEN_CTX_HPP_