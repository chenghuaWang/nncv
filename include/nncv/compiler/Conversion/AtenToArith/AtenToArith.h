#ifndef NNCV_C_CONVERSION_ATEN_TO_ARITH_
#define NNCV_C_CONVERSION_ATEN_TO_ARITH_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"

#define GEN_PASS_DECL_CONVERTAFFINETOSTANDARD
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createConvertAtenToArithPass();
}
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_ATEN_TO_ARITH_