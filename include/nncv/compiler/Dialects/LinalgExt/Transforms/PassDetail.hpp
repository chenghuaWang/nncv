#ifndef NNCV_COMPILER_NNCV_LINALG_EXT_PASS_TRANSFORMS_DEATILS_HPP_
#define NNCV_COMPILER_NNCV_LINALG_EXT_PASS_TRANSFORMS_DEATILS_HPP_

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Pass/Pass.h"

namespace mlir::nncv::linalg_ext {

#define GEN_PASS_CLASSES
#include "LinalgExt/Passes/Passes.h.inc"  // IWYU pragma: keep

}  // namespace mlir::nncv::linalg_ext

#endif  //! NNCV_COMPILER_NNCV_LINALG_EXT_PASS_TRANSFORMS_DEATILS_HPP_