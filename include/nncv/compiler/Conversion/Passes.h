#ifndef NNCV_ATEN_CONVERSION_PASSES_H
#define NNCV_ATEN_CONVERSION_PASSES_H

#include "nncv/compiler/Conversion/AtenToArith/AtenToArith.h"

namespace mlir {
#define GEN_PASS_REGISTRATION
#include "Conversion/Passes.h.inc"
}  // namespace mlir

#endif  //! NNCV_ATEN_CONVERSION_PASSES_H