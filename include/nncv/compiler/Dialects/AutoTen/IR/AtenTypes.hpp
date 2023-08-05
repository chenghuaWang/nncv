#ifndef MLIR_ATEN_TYPES_HPP
#define MLIR_ATEN_TYPES_HPP

#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/Types.h"
#include "mlir/Interfaces/DataLayoutInterfaces.h"

#define GET_TYPEDEF_CLASSES
#include "AutoTen/IR/AutoTenOpsTypes.h.inc"

#endif  //! MLIR_ATEN_TYPES_HPP