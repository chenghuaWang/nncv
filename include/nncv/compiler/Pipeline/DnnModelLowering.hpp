/**
 * @file DnnModelLowering.hpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief Lowering DNN Model to NNVM or LLVM
 * @version 0.1
 * @date 2024-01-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef NNCV_COMPILER_DNN_MODEL_LOWERING_HPP_
#define NNCV_COMPILER_DNN_MODEL_LOWERING_HPP_

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/OwningOpRef.h"
#pragma once

#include "mlir/Pass/PassManager.h"

namespace nncv {
namespace pipeline {

/**
 * @brief This pass should be performed after all tiling and vectorization is done for normal linalg
 * ops, such as matmul and conv2d(except conv2d_nchw_fchw, this format of conv will be optimized
 * manually)
 *
 * @param pm
 */
void populateOneBufferizationPassPipeline(mlir::PassManager& pm);

class DnnModelLowering {
 public:
  DnnModelLowering(mlir::MLIRContext& context, mlir::OwningOpRef<mlir::ModuleOp>& module)
      : m_Context(context), m_Module(module) {}

  void run();
  inline void setGenNVPTX() { m_GenNVPTX = true; }
  inline void setGenHostWoParallel() { m_GenHostWoParallel = true; }
  inline void setGenHostWParallel() { m_GenHostWParallel = true; }
  inline void setUsingNncvIR() { m_UsingNncvIR = true; }
  inline void setOutputFilePath(const std::string& _CurPath) { m_OutputFilePath = _CurPath; }

 private:
  bool m_GenNVPTX = false;
  bool m_GenHostWoParallel = false;
  bool m_GenHostWParallel = false;
  bool m_UsingNncvIR = false;
  mlir::MLIRContext& m_Context;
  mlir::OwningOpRef<mlir::ModuleOp>& m_Module;
  std::string m_OutputFilePath;
};

}  // namespace pipeline
}  // namespace nncv

#endif  //! NNCV_COMPILER_DNN_MODEL_LOWERING_HPP_