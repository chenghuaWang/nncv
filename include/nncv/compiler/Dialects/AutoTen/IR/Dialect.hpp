#ifndef MLIR_ATEN_DIALECT_HPP
#define MLIR_ATEN_DIALECT_HPP

#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/FunctionInterfaces.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/IR/TypeRange.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/CastInterfaces.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Shape/IR/Shape.h"

#include "AutoTen/IR/Dialect.h.inc"

//===----------------------------------------------------------------------===//
// Aten Operations
//===----------------------------------------------------------------------===//
#include "AutoTen/IR/AutoTenOpsEnums.h.inc"
#define GET_ATTRDEF_CLASSES
#include "AutoTen/IR/AutoTenOpsAttributes.h.inc"
#define GET_TYPEDEF_CLASSES
#include "AutoTen/IR/AutoTenTypes.h.inc"

/// Include the auto-generated header file containing the declarations of the
/// Aten operations.
#define GET_OP_CLASSES
#include "AutoTen/IR/AutoTen.h.inc"

namespace mlir {
namespace aten {}  // namespace aten
}  // namespace mlir

#endif  // ! MLIR_ATEN_DIALECT_HPP