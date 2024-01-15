#ifndef NNCV_C_CONVERSION_CONV2D_OPTIMIZE_WINOGRAD_
#define NNCV_C_CONVERSION_CONV2D_OPTIMIZE_WINOGRAD_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_OPTIMIZECONV2DUSINGWINOGRAD
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createOptimizeConv2dUsingWinogradPass();

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_CONV2D_OPTIMIZE_WINOGRAD_