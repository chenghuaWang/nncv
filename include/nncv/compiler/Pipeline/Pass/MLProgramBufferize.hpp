#ifndef NNCV_COMPILER_MLPROG_BUFERIZE_PASS_HPP_
#define NNCV_COMPILER_MLPROG_BUFERIZE_PASS_HPP_

#include "mlir/Pass/Pass.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/PassManager.h"

#pragma once

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createMLProgramBufferizePass();
}
}  // namespace mlir

#endif  //! NNCV_COMPILER_MLPROG_BUFERIZE_PASS_HPP_