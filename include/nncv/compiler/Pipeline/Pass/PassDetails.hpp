#ifndef NNCV_COMPILER_PASS_DETAILS_HPP_
#define NNCV_COMPILER_PASS_DETAILS_HPP_

#pragma once

#include "mlir/IR/Operation.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Pass/Pass.h"

namespace mlir {
namespace nncv {

#define GEN_PASS_CLASSES
#include "Pass/Passes.h.inc"

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_COMPILER_PASS_DETAILS_HPP_