
/**
 * @file DnnModelLowering.cpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief Lowering DNN Model to NNVM or LLVM
 * @version 0.1
 * @date 2024-01-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "nncv/compiler/Pipeline/DnnModelLowering.hpp"

#include "nncv/compiler/Pipeline/Pass/Passes.hpp"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"

namespace nncv {
namespace pipeline {

void DnnModelLowering::registerAllPass() {
  // Removed, using one-shot instead.
  // m_PM->addPass(mlir::nncv::createMLProgramBufferizePass());

  // Level 1.1(Top). MLIR Build In Bufferize. One-Shot Bufferize.
  m_PM->addPass(mlir::bufferization::createOneShotBufferizePass());
}

}  // namespace pipeline
}  // namespace nncv