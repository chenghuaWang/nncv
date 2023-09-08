#ifndef MLIR_ATEN_TYPES_HPP
#define MLIR_ATEN_TYPES_HPP

#ifndef _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#endif

#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/Types.h"
#include "mlir/Interfaces/DataLayoutInterfaces.h"

#define GET_TYPEDEF_CLASSES
#include "AutoTen/IR/AutoTenOpsTypes.h.inc"

#endif  //! MLIR_ATEN_TYPES_HPP