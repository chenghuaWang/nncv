#ifndef NNCV_C_CONVERSION_CONV2D_OPTIMIZE_ALL_
#define NNCV_C_CONVERSION_CONV2D_OPTIMIZE_ALL_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_CONVERTOPTIMIZEDCONV2DTOAFFINE
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createConvertOptimizedConv2dToAffinePass();

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_CONV2D_OPTIMIZE_ALL_