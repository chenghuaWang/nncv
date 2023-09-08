// store the op_builder. will pass to other code gen module.
// Also stored some basic data struct using when gen code in antlr or ast.
#ifndef NNCV_COMPILER_CODE_GEN_CTX_HPP_
#define NNCV_COMPILER_CODE_GEN_CTX_HPP_

#include <string>
#include <map>
#include <utility>
#include <vector>

#ifndef _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#endif
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Types.h"

namespace nncv {
namespace compiler {
namespace frontend {

//===----------------------------------------------------------------------===//
// ParserState
//===----------------------------------------------------------------------===//
class ParserState {
  // register function actions.
};

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

  inline bool setFlagsKV(std::string& key, const std::string& value) {
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

  inline llvm::SmallVector<mlir::NamedAttribute> genNamedAttrs(mlir::MLIRContext* ctx) {
    llvm::SmallVector<mlir::NamedAttribute> attrs;
    // [1] Kernel.AutoParallel
    if (asKernelAndEnableParallel) {
      auto _na = mlir::NamedAttribute(mlir::StringAttr::get(ctx, "Kernel.AutoParallel"),
                                      mlir::IntegerAttr::get(mlir::IntegerType::get(ctx, 32), 1));
      attrs.emplace_back(_na);
      // [2] Kernel.Platform
      auto _nda = mlir::NamedAttribute(mlir::StringAttr::get(ctx, "Kernel.Platform"),
                                       mlir::StringAttr::get(ctx, deviceType));
      attrs.emplace_back(_nda);
    }
    return attrs;
  }

 private:
  bool asKernelAndEnableParallel;
  std::string deviceType;
};

//===----------------------------------------------------------------------===//
// Store the parameter of Functions
//===----------------------------------------------------------------------===//
struct FuncParameterAndReturn {
  std::vector<std::tuple<std::string, mlir::Type, /*has identifier*/ bool>> parameters;
  std::tuple<std::string, mlir::Type, /*has identifier*/ bool> ret;
};

//===----------------------------------------------------------------------===//
// Helper functions: Generate sym_visibility:
// "nested", "private", "public".
//
//===----------------------------------------------------------------------===//
inline mlir::StringAttr genSymVisibilityAttr(mlir::MLIRContext* ctx, bool isPublic,
                                             bool nested = false) {
  if (nested) { return mlir::StringAttr::get(ctx, "nested"); }
  if (isPublic) {
    return mlir::StringAttr::get(ctx, "public");
  } else {
    return mlir::StringAttr::get(ctx, "private");
  }
}

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_CODE_GEN_CTX_HPP_