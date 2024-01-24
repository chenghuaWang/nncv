#ifndef NNCV_COMPILER_PIPELINE_ATEN_BK_LOWERING_HPP_
#define NNCV_COMPILER_PIPELINE_ATEN_BK_LOWERING_HPP_

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/OwningOpRef.h"

namespace nncv::compiler {
namespace pipeline {

class AtenBackendLoweringPipeline {
 public:
  AtenBackendLoweringPipeline(mlir::MLIRContext& context, mlir::OwningOpRef<mlir::ModuleOp>& module)
      : m_Context(context), m_Module(module) {}

  inline void setShowLlvmIR(bool flag) { m_ShowLlvmIR = flag; }
  inline bool getLlvmIR() { return m_ShowLlvmIR; }

  inline void setOutputFilePath(const std::string& _CurPath) { m_OutputFilePath = _CurPath; }

  void run();

 private:
  mlir::MLIRContext& m_Context;
  mlir::OwningOpRef<mlir::ModuleOp>& m_Module;

  bool m_ShowLlvmIR = false;
  std::string m_OutputFilePath;
};

}  // namespace pipeline
}  // namespace nncv::compiler

#endif  //! NNCV_COMPILER_PIPELINE_ATEN_BK_LOWERING_HPP_