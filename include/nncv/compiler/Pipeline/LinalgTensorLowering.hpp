/**
 * @file LinalgTensorLowering.hpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief Lowering Linalg and Tensor Partially to NNCV IR
 * @version 0.1
 * @date 2024-01-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef NNCV_COMPILER_LINALG_TENSOR_LOWERING_HPP_
#define NNCV_COMPILER_LINALG_TENSOR_LOWERING_HPP_

#pragma once

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Pass/Pass.h"

namespace {
struct LinalgTensorToNncvLoweringPass
    : public mlir::PassWrapper<LinalgTensorToNncvLoweringPass,
                               mlir::OperationPass<mlir::ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(LinalgTensorToNncvLoweringPass);

  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    // TODO
  }
  void runOnOperation() final;
};

// TODO register to createPass function.

}  // namespace

#endif  //! NNCV_COMPILER_LINALG_TENSOR_LOWERING_HPP_