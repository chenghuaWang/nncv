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
  DnnModelLowering(mlir::PassManager* pm) : usingNncvIR(false), m_PM(pm) {}

  void registerAllPass();

 private:
  bool usingNncvIR;
  mlir::PassManager* m_PM;
};

}  // namespace pipeline
}  // namespace nncv

#endif  //! NNCV_COMPILER_DNN_MODEL_LOWERING_HPP_