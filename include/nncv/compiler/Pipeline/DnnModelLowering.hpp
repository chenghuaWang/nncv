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

#pragma once

#include "mlir/Pass/PassManager.h"

namespace nncv {
namespace pipeline {

class DnnModelLowering {
 public:
  DnnModelLowering(mlir::PassManager* pm) : m_UsingNncvIR(false), m_PM(pm) {}

  void registerAllPass();
  inline void setGenNVPTX() { m_GenNVPTX = true; }
  inline void setGenHostWoParallel() { m_GenHostWoParallel = true; }
  inline void setGenHostWParallel() { m_GenHostWParallel = true; }
  inline void setUsingNncvIR() { m_UsingNncvIR = true; }

 private:
  bool m_GenNVPTX;
  bool m_GenHostWoParallel;
  bool m_GenHostWParallel;
  bool m_UsingNncvIR;
  mlir::PassManager* m_PM;
};

}  // namespace pipeline
}  // namespace nncv

#endif  //! NNCV_COMPILER_DNN_MODEL_LOWERING_HPP_