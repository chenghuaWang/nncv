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

void runPmWithExit(mlir::PassManager& pm, mlir::OwningOpRef<mlir::ModuleOp>& module,
                   const std::string& str);

void runPmSilent(mlir::PassManager& pm, mlir::OwningOpRef<mlir::ModuleOp>& module);

/**
 * @brief This pass should be performed after all tiling and vectorization is done for normal linalg
 * ops, such as matmul and conv2d(except conv2d_nchw_fchw, this format of conv will be optimized
 * manually)
 *
 * @param pm
 */
void populateOneBufferizationPassPipeline(mlir::PassManager& pm);

void populateInputOptimizationPassPipeline(mlir::PassManager& pm, bool enableImg2Col = false,
                                           bool enablePaddingMatMul = false);

void populateTensorOptimizationPassPipeline(mlir::PassManager& pm);

void populateWinogradOrImg2ColPassPipeline(mlir::PassManager& pm, bool winograd = false,
                                           bool img2col = false);

void populateTileAllPassPipeline(mlir::PassManager& pm, bool oneshot = true, bool lowerConv = false,
                                 bool gpy = false);

void populateVectorizationPassPipeline(mlir::PassManager& pm, bool gpu = false);

void populateConv2dToAffineVecManuallyPassPipeline(mlir::PassManager& pm);

void populateLoopFusionAndNormalizationPassPipeline(mlir::PassManager& pm);

class DnnModelLowering {
 public:
  DnnModelLowering(mlir::MLIRContext& context, mlir::OwningOpRef<mlir::ModuleOp>& module)
      : m_Context(context), m_Module(module) {}

  void run();
  inline void setGenNVPTX() { m_GenNVPTX = true; }
  inline void setGenHostWoParallel() { m_GenHostWoParallel = true; }
  inline void setGenHostWParallel() { m_GenHostWParallel = true; }
  inline void setUsingNncvIR() { m_UsingNncvIR = true; }
  inline void setGenNative() { m_Native = true; }
  inline void setAdvX86() { m_AdvanceX86 = true; }
  inline void setOutputFilePath(const std::string& _CurPath) { m_OutputFilePath = _CurPath; }
  inline void setGenConfigFileOnly(bool flag) {
    m_GenConfigFileOnly = flag;
    if (flag) {
      m_GenNVPTX = false;
      m_GenHostWoParallel = false;
      m_GenHostWParallel = false;
    }
  }
  inline void setGenConfigFilePath(const std::string& _CurPath) { m_ConfigFilePath = _CurPath; }
  inline void setWarpC(bool flag = true) { m_WaprC = flag; }
  inline void setNumThreads(int64_t v) { m_NumThreads = v; }
  inline void setSplitParams(bool flag = false) { m_SplitParams = flag; }

 private:
  bool m_GenNVPTX = false;
  bool m_GenHostWoParallel = false;
  bool m_GenHostWParallel = false;
  bool m_UsingNncvIR = false;
  bool m_GenConfigFileOnly = false;
  bool m_WaprC = false;
  bool m_SplitParams = false;
  bool m_Native = false;
  bool m_AdvanceX86 = false;
  int64_t m_NumThreads = 4;
  std::string m_ConfigFilePath;
  mlir::MLIRContext& m_Context;
  mlir::OwningOpRef<mlir::ModuleOp>& m_Module;
  std::string m_OutputFilePath;
};

}  // namespace pipeline
}  // namespace nncv

#endif  //! NNCV_COMPILER_DNN_MODEL_LOWERING_HPP_