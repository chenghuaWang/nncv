#ifndef NNCV_C_NNCV_GRAPH_INTERFACES_HPP_
#define NNCV_C_NNCV_GRAPH_INTERFACES_HPP_

#pragma once

#include "mlir/IR/Attributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/IR/SymbolTable.h"

namespace mlir {
namespace nncv {
namespace graph {
class ShapeAwareOpInterface;

// Builds a ranked shape with all dimension values for the given operand.
SmallVector<Value> buildOperandShape(ShapeAwareOpInterface op, unsigned operandIdx,
                                     OpBuilder& builder);

// Builds a ranked shape with all dimension values for the given result.
SmallVector<Value> buildResultShape(ShapeAwareOpInterface op, unsigned resultIdx,
                                    OpBuilder& builder);
}  // namespace graph
}  // namespace nncv
}  // namespace mlir

#include "NncvGraph/IR/NncvGraphOpInterfaces.h.inc"

#endif  //! NNCV_C_NNCV_GRAPH_INTERFACES_HPP_