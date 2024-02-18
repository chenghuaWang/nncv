#ifndef NNCV_C_CONVERSION_TRANSFORMS_ERASE_
#define NNCV_C_CONVERSION_TRANSFORMS_ERASE_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_NESTEDTRANSFORMERASE
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createNestedTransformErasePass();
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_TRANSFORMS_ERASE_