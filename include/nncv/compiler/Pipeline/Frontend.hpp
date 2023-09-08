#ifndef NNCV_COMPILER_TEN_LANG_PIP_FRO_HPP_
#define NNCV_COMPILER_TEN_LANG_PIP_FRO_HPP_

#include <string>
#include "nncv/compiler/Frontend/TenLangLexer.hpp"
#include "nncv/compiler/Frontend/TenLangParser.hpp"

namespace nncv {
namespace compiler {
namespace pipeline {

class pipelineAll {};

class pipeline {
 public:
  virtual void run() = 0;
};

class FrontendPipeline : public pipeline {
 public:
  FrontendPipeline(mlir::MLIRContext& context, mlir::OwningOpRef<mlir::ModuleOp>& module)
      : m_Context(context), m_Module(module) {}

  void run() override;

  inline void setShowCst(bool flag) { m_showCst = flag; }
  inline bool ssShowCst(bool flag) const { return m_showCst; }
  inline void setDumpMlir(bool flag) { m_dumpMlir = flag; }
  inline bool ssDumpMlir(bool flag) const { return m_dumpMlir; }
  inline void setFilePath(const std::string& _CurPath) { m_CurrentFilePath = _CurPath; }

 private:
  mlir::MLIRContext& m_Context;
  mlir::OwningOpRef<mlir::ModuleOp>& m_Module;
  bool m_showCst = false;
  bool m_dumpMlir = false;
  std::string m_CurrentFilePath;
};

}  // namespace pipeline
}  // namespace compiler
}  // namespace nncv

#endif  // !NNCV_COMPILER_TEN_LANG_PIP_FRO_HPP_