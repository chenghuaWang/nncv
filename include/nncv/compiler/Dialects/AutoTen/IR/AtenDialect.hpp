#ifndef MLIR_ATEN_DIALECT_HPP
#define MLIR_ATEN_DIALECT_HPP

#ifndef _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#endif

#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/FunctionInterfaces.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/ControlFlowInterfaces.h"
#include "mlir/Interfaces/InferTypeOpInterface.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
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

#include "nncv/compiler/Dialects/AutoTen/IR/AtenAttrs.hpp"
#include "AutoTen/IR/AutoTenOpsDialect.h.inc"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"

namespace mlir {
namespace OpTrait {

namespace impl {
// These functions are out-of-line implementations of the methods in the
// corresponding trait classes.  This avoids them being template
// instantiated/duplicated.
LogicalResult verifySameFirstOperandAndResultType(Operation* op);
}  // namespace impl

/// This class provides verification for ops that are known to have the same
/// first operand and result type.
///
template<typename ConcreteType>
class SameFirstOperandAndResultType
    : public TraitBase<ConcreteType, SameFirstOperandAndResultType> {
 public:
  static LogicalResult verifyTrait(Operation* op) {
    return impl::verifySameFirstOperandAndResultType(op);
  }
};

}  // namespace OpTrait
}  // namespace mlir

#define GET_OP_CLASSES
#include "AutoTen/IR/AutoTenOps.h.inc"

#endif  // ! MLIR_ATEN_DIALECT_HPP