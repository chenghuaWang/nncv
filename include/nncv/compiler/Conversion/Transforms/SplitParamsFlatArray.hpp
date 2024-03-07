#ifndef NNCV_C_CONVERSION_SPLIT_PARAMS_FLAT_ARRAY_
#define NNCV_C_CONVERSION_SPLIT_PARAMS_FLAT_ARRAY_

#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_SPLITPARAMSFLATARRAY
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {

namespace {}  // namespace

std::unique_ptr<mlir::Pass> createSplitParamsFlatArrayPass();
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_SPLIT_PARAMS_FLAT_ARRAY_