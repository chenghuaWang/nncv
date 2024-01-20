#ifndef NNCV_C_CONVERSION_MATMUL_OPT_DEFAULT_
#define NNCV_C_CONVERSION_MATMUL_OPT_DEFAULT_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_MATMULOPTIMIZATION_DEFAULT
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
namespace matmul_optimize {
std::unique_ptr<mlir::Pass> createMatMulOptimizationDefaultPass();
}
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_MATMUL_OPT_DEFAULT_