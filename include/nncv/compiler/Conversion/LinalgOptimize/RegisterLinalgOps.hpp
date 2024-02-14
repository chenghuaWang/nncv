// using register linalg ops pass to gen a config file for tiling size and other linalg related
// settings.

// In this pass, I will register all linalg related ops to TileSolver. The TileSolver will record
// all linalg ops that will be optimized. The tile solver uing singleton method. Remeber that, this
// pass should be executed before other optimization passes. Normally before the front end
// optimization pass.

#ifndef NNCV_C_CONVERSION_LINALG_REGISTER_LINALG_OPS_HPP_
#define NNCV_C_CONVERSION_LINALG_REGISTER_LINALG_OPS_HPP_

#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_REGISTERLINALGOPS
#include "Conversion/Passes.h.inc"

namespace mlir::nncv {
namespace {}
std::unique_ptr<mlir::Pass> createRegisterLinalgOpsPass();
}  // namespace mlir::nncv

#endif  //! NNCV_C_CONVERSION_LINALG_REGISTER_LINALG_OPS_HPP_