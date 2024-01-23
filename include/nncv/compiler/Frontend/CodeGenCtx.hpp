// store the op_builder. will pass to other code gen module.
// Also stored some basic data struct using when gen code in antlr or ast.
#ifndef NNCV_COMPILER_CODE_GEN_CTX_HPP_
#define NNCV_COMPILER_CODE_GEN_CTX_HPP_

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <stack>

#ifndef _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#endif
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Types.h"
#include "mlir/IR/Block.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"

namespace nncv {
namespace compiler {
namespace frontend {

//===----------------------------------------------------------------------===//
// ParserState
//===----------------------------------------------------------------------===//

enum class _ParserSateEnum : int32_t {
  kGlobal = 0,
  kFunction = 1,  // has block
  kIf = 2,        // has block
  kWhile = 3,     // has block
  kSwitch = 4,    // has block
  kAssignStmt = 5,
  kFor = 6,
  kSlice = 7,
  kIncDec = 8,
  kPfor = 9,         // parallel for
  kPforClause = 10,  // parallel for clause
};

class ParserState {
 public:
  ParserState() {}
  ~ParserState() {
    if (m_StateStack.size() != 0)
      printf("[ Erro ] The stack of parser state is not 0, get %lu instead\n", m_StateStack.size());
  }

  inline bool IsInIfScope() { return m_StateStack.top() == _ParserSateEnum::kIf; }
  inline bool IsInAssignStmt() { return m_StateStack.top() == _ParserSateEnum::kAssignStmt; }
  inline bool IsInForScope() { return m_StateStack.top() == _ParserSateEnum::kFor; }
  inline bool IsInPforClause() { return m_StateStack.top() == _ParserSateEnum::kPforClause; }

  inline mlir::aten::FuncOp* GetFuncOp() {
    if (m_FuncOp != nullptr)
      return m_FuncOp;
    else { printf("[ Error ] When lowering to MLIR. Fonud m_FuncOp is null.\n"); }
    exit(-1);
  }

  inline void PushFuncStmt(mlir::aten::FuncOp* op) {
    m_StateStack.push(_ParserSateEnum::kFunction);
    m_FuncOp = op;
    m_FuncHasReturned = false;
  }

  inline void SetFuncHasReturned() { m_FuncHasReturned = true; }
  inline bool IsFuncHasReturned() { return m_FuncHasReturned; }

  inline void PushIfStmt() {
    m_StateStack.push(_ParserSateEnum::kIf);
    m_IfHasTerminatedByBreak.push(false);
    m_IfSSARet.push(std::vector<std::string>{});
  };
  inline void SetIfHasTerminatedByBreak() {
    m_IfHasTerminatedByBreak.pop();
    m_IfHasTerminatedByBreak.push(true);
  }
  inline bool IsIfHadTerminated() { return m_IfHasTerminatedByBreak.top(); }
  inline void SetIfStmtValueUsed(std::string& vn) { m_IfSSARet.top().push_back(vn); }
  inline std::vector<std::string>& GetIfStmtValueUsed() { return m_IfSSARet.top(); }

  inline void PushAssignStmt() { m_StateStack.push(_ParserSateEnum::kAssignStmt); }

  inline void PushForStmt() {
    m_StateStack.push(_ParserSateEnum::kFor);
    m_ForHasTerminatedByBreak.push(false);
  }
  inline void SetForHasTerminatedByBreak() {
    m_ForHasTerminatedByBreak.pop();
    m_ForHasTerminatedByBreak.push(true);
  }
  inline bool IsForHadTerminated() { return m_ForHasTerminatedByBreak.top(); }
  inline int64_t GetForConditionTmpCnt() { return m_ForConditionTempCnt++; }

  inline void PushParallelForStmt() {
    m_StateStack.push(_ParserSateEnum::kPfor);
    m_ParallelForHasTerminatedByBreak.push(false);
  }
  inline void SetParallelForHasTerminatedByBreak() {
    m_ParallelForHasTerminatedByBreak.pop();
    m_ParallelForHasTerminatedByBreak.push(true);
  }
  inline bool IsParallelForHadTerminated() { return m_ParallelForHasTerminatedByBreak.top(); }
  inline void PushPforClause() { m_StateStack.push(_ParserSateEnum::kPforClause); }

  inline void SetExpressionLiteralGenMlirValue(bool v) { m_ExpressionLiteralGenMlirValue = v; }
  inline bool IsExpressionLiteralGenMlirValue() { return m_ExpressionLiteralGenMlirValue; }

  inline void SetCurSliceIndex(llvm::SmallVector<mlir::Value, 4> v) { m_CurrentSliceIndex = v; }
  inline llvm::SmallVector<mlir::Value, 4>& GetCurSliceIndex() { return m_CurrentSliceIndex; }

  inline void PushSliceStmt() { m_StateStack.push(_ParserSateEnum::kSlice); }
  inline bool IsInSliceStmt() { return m_StateStack.top() == _ParserSateEnum::kSlice; }

  inline void PushIncDecStmt() { m_StateStack.push(_ParserSateEnum::kIncDec); }
  inline bool IsInIncDecStmt() { return m_StateStack.top() == _ParserSateEnum::kIncDec; }

  inline void SetIntLiteral(int64_t v) { m_IntLiteral = v; }
  inline int64_t GetIntLiteral() { return m_IntLiteral; }

  inline void Pop() {
    auto top = m_StateStack.top();
    switch (top) {
      case _ParserSateEnum::kGlobal: {
        break;
      }
      case _ParserSateEnum::kFunction: {
        m_FuncOp = nullptr;
        m_FuncHasReturned = false;
        break;
      }
      case _ParserSateEnum::kIf: {
        m_IfHasTerminatedByBreak.pop();
        m_IfSSARet.pop();
        break;
      }
      case _ParserSateEnum::kWhile: {
        break;
      }
      case _ParserSateEnum::kSwitch: {
        break;
      }
      case _ParserSateEnum::kFor: {
        m_ForHasTerminatedByBreak.pop();
        break;
      }
      case _ParserSateEnum::kPfor: {
        m_ParallelForHasTerminatedByBreak.pop();
        break;
      }
      default: break;
    }
    m_StateStack.pop();
  }

  inline mlir::Block* GetBlock() { return m_BlockState.top(); }

 private:
  // 1. Struct state

  // 2. function state
  mlir::aten::FuncOp* m_FuncOp;
  bool m_FuncHasReturned = false;

  // 3. If State
  std::stack<bool> m_IfHasTerminatedByBreak;
  std::stack<std::vector<std::string>> m_IfSSARet;

  // 4. For State
  std::stack<bool> m_ForHasTerminatedByBreak;

  // 5. For Literal Expression. Generate mlir::Value or not.
  bool m_ExpressionLiteralGenMlirValue = true;
  int64_t m_ForConditionTempCnt = 0;

  // 6. Remeber current slice.
  llvm::SmallVector<mlir::Value, 4> m_CurrentSliceIndex;

  // 7. PFor State
  std::stack<bool> m_ParallelForHasTerminatedByBreak;

  // always record.
  int64_t m_IntLiteral;

  // stack record
  std::stack<_ParserSateEnum> m_StateStack;
  std::stack<mlir::Block*> m_BlockState;
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

  inline mlir::DictionaryAttr genDictAttrs(mlir::MLIRContext* ctx) {
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
    return mlir::DictionaryAttr::get(ctx, attrs);
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

//===----------------------------------------------------------------------===//
// Helper functions: removeQuotationMark:
// "main" -> main
//
//===----------------------------------------------------------------------===//
inline std::string removeQuotationMark(const std::string& str) {
  return str.substr(1, str.length() - 2);
}

//===----------------------------------------------------------------------===//
// Helper functions: isMain:
//===----------------------------------------------------------------------===//
inline bool isPackageNameIsMain(const std::string& str) { return str == "main"; }

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_CODE_GEN_CTX_HPP_