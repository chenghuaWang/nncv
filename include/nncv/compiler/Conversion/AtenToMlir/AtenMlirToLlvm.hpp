#pragma once
#ifndef NNCV_C_CONVERSION_ATENMLIR_TO_NNCV_
#define NNCV_C_CONVERSION_ATENMLIR_TO_NNCV_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_CONVERTATENMLIRTOLLVM
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {

std::unique_ptr<mlir::Pass> createConvertAtenMlirToLlvmPass();

}
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_ATENMLIR_TO_NNCV_