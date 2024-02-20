#ifndef NNCV_C_CONVERSION_VEC_PAD_
#define NNCV_C_CONVERSION_VEC_PAD_

#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_TENSORTOVECTORVECTORIZEPAD
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {

void populateVectorizePadPatterns(RewritePatternSet& patterns, PatternBenefit baseBenefit = 1);

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createVectorizePadPass();
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_VEC_PAD_