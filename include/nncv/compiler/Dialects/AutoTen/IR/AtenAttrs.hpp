#ifndef MLIR_ATEN_ATTRS_HPP
#define MLIR_ATEN_ATTRS_HPP

#include "mlir/IR/Attributes.h"
#include "mlir/IR/BuiltinAttributeInterfaces.h"

#include "mlir/IR/BuiltinAttributes.h"
#include "AutoTen/IR/AutoTenOpsEnums.h.inc"

namespace mlir {
namespace aten {
class ArrayType;
class StructType;
class BoolType;
}  // namespace aten
}  // namespace mlir

#define GET_ATTRDEF_CLASSES
#include "AutoTen/IR/AutoTenOpsAttributes.h.inc"

#endif  //! MLIR_ATEN_ATTRS_HPP