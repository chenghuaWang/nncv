#ifndef NNCV_C_CONVERSION_MATMUL_OPT_PARALLEL_VEC_
#define NNCV_C_CONVERSION_MATMUL_OPT_PARALLEL_VEC_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_MATMULOPTIMIZATION_PARALLELVEC
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
namespace matmul_optimize {
std::unique_ptr<mlir::Pass> createMatMulOptimizationParallelVecPass();
}
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_MATMUL_OPT_PARALLEL_VEC_