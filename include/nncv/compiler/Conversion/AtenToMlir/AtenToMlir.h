#ifndef NNCV_C_CONVERSION_ATEN_TO_MLIR_
#define NNCV_C_CONVERSION_ATEN_TO_MLIR_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_CONVERTATENTOMLIR
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createConvertAtenToMlirPass();

void populateAtenToMlirConversionPatterns(mlir::RewritePatternSet* patterns,
                                          mlir::TypeConverter& converter);
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_ATEN_TO_MLIR_