#ifndef NNCV_COMPILER_NNCV_FRONTEND_PASS_DETAILS_HPP_
#define NNCV_COMPILER_NNCV_FRONTEND_PASS_DETAILS_HPP_

#include "mlir/IR/Operation.h"
#include "mlir/Pass/Pass.h"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"

namespace mlir {
namespace nncv {

#define GEN_PASS_CLASSES
#include "AutoTen/Transforms/Passes.h.inc"

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_COMPILER_NNCV_FRONTEND_PASS_DETAILS_HPP_