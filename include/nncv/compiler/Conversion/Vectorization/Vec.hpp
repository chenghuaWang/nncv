#ifndef NNCV_C_CONVERSION_VEC_
#define NNCV_C_CONVERSION_VEC_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_VECTORIZATION
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createVectorizationPass(bool flag = false);
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_VEC_