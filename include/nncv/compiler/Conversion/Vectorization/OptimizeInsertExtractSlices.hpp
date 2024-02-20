#ifndef NNCV_C_CONVERSION_VEC_OPTIMIZE_IN_EX_SL_
#define NNCV_C_CONVERSION_VEC_OPTIMIZE_IN_EX_SL_

#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_OPTIMIZETENSORINSERTEXTRACTSLICES
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>>
createOptimizeTensorInsertExtractSlicesPass();
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_VEC_OPTIMIZE_IN_EX_SL_