#ifndef MLIR_ATEN_DIALECT_HPP
#define MLIR_ATEN_DIALECT_HPP

#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/FunctionInterfaces.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/CastInterfaces.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"

namespace mlir {
namespace aten {
namespace detail {
struct StructTypeStorage;
}  // namespace detail
}  // namespace aten
}  // namespace mlir

#include "AutoTen/Dialect.h.inc"

//===----------------------------------------------------------------------===//
// Aten Operations
//===----------------------------------------------------------------------===//

/// Include the auto-generated header file containing the declarations of the
/// Aten operations.
#define GET_OP_CLASSES
#include "AutoTen/AutoTen.h.inc"

namespace mlir {
namespace aten {

class StructType : public mlir::Type::TypeBase<StructType, mlir::Type, detail::StructTypeStorage> {
 public:
  using Base::Base;

  /// Create an instance of a `StructType` with the given element types. There
  /// *must* be atleast one element type.
  static StructType get(llvm::ArrayRef<mlir::Type> elementTypes);

  /// Returns the element types of this struct type.
  llvm::ArrayRef<mlir::Type> getElementTypes();

  /// Returns the number of element type held by this struct.
  size_t getNumElementTypes() { return getElementTypes().size(); }
};

}  // namespace aten
}  // namespace mlir

#endif  // ! MLIR_ATEN_DIALECT_HPP