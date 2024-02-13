#ifndef NNCV_C_NNCV_GRAPH_OPS_HPP_
#define NNCV_C_NNCV_GRAPH_OPS_HPP_

#pragma once

#include "llvm/ADT/SmallBitVector.h"
#include "mlir/IR/Attributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/ControlFlowInterfaces.h"
#include "mlir/Interfaces/InferTypeOpInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"

#include "nncv/compiler/Dialects/NncvGraph/IR/NncvGraphInterfaces.hpp"
#include "nncv/compiler/Dialects/NncvGraph/IR/NncvGraphTypes.hpp"

namespace mlir {
namespace nncv {
namespace graph {}  // namespace graph
}  // namespace nncv
}  // namespace mlir

#define GET_OP_CLASSES
#include "NncvGraph/IR/NncvGraphOps.h.inc"  // IWYU pragma: export

#endif  //! NNCV_C_NNCV_GRAPH_OPS_HPP_