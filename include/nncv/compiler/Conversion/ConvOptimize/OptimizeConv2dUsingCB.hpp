#ifndef NNCV_C_CONVERSION_CONV2D_OPTIMIZE_CB_
#define NNCV_C_CONVERSION_CONV2D_OPTIMIZE_CB_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

namespace mlir {
namespace nncv {

#define GEN_PASS_DECL_OPTIMIZECONV2DUSINGCB
#include "Conversion/Passes.h.inc"

std::unique_ptr<mlir::Pass> createOptimizeConv2dUsingCBPass();

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_CONV2D_OPTIMIZE_CB_