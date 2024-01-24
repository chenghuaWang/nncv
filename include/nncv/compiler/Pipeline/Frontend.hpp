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
  virtual ~pipeline(){};
  virtual void run() = 0;
};

class FrontendPipeline : public pipeline {
 public:
  FrontendPipeline(mlir::MLIRContext& context, mlir::OwningOpRef<mlir::ModuleOp>& module)
      : m_Context(context), m_Module(module) {}
  ~FrontendPipeline() {}

  void run() override;

  inline void setShowCst(bool flag) { m_showCst = flag; }
  inline bool ssShowCst(bool flag) const { return m_showCst; }
  inline void setBuiltinMlir(bool flag) { m_genBuiltinMlir = flag; }
  inline bool ssBuiltinMlir(bool flag) const { return m_genBuiltinMlir; }
  inline void setInputFilePath(const std::string& _CurPath) { m_CurrentFilePath = _CurPath; }
  inline void setGenAtenIR(bool flag) { m_genAtenIR = flag; }
  inline void setOutputFilePath(const std::string& _CurPath) { m_outputFilePath = _CurPath; }

 private:
  mlir::MLIRContext& m_Context;
  mlir::OwningOpRef<mlir::ModuleOp>& m_Module;
  bool m_showCst = false;
  bool m_genBuiltinMlir = false;
  bool m_genAtenIR = false;
  std::string m_CurrentFilePath;
  std::string m_outputFilePath;
};

}  // namespace pipeline
}  // namespace compiler
}  // namespace nncv

#endif  // !NNCV_COMPILER_TEN_LANG_PIP_FRO_HPP_