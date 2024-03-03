#ifndef NNCV_C_CONVERSION_SPLIT_PARAMS_
#define NNCV_C_CONVERSION_SPLIT_PARAMS_

#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_SPLITPARAMS
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createSplitParamsPass();
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_SPLIT_PARAMS_