#ifndef NNCV_C_NNCV_GRAPH_TYPES_HPP_
#define NNCV_C_NNCV_GRAPH_TYPES_HPP_

#pragma once

#include "nncv/compiler/Dialects/NncvGraph/IR/NncvGraphDialect.hpp"
#include "nncv/compiler/Dialects/NncvGraph/IR/NncvGraphInterfaces.hpp"

#include "llvm/ADT/DenseMapInfo.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringSwitch.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/TypeSupport.h"
#include "mlir/IR/Types.h"
#include "mlir/Support/LLVM.h"

// clang-format off: must be included after all LLVM/MLIR headers.
#include "NncvGraph/IR/NncvGraphEnums.h.inc"  //IWYU pragma: export
// clang-format on

namespace mlir {
namespace nncv {
namespace graph {

#include "NncvGraph/IR/NncvGraphTypeInterfaces.h.inc"  // IWYU pragma: export

}  // namespace graph
}  // namespace nncv
}  // namespace mlir

// clang-format off: must be included after all LLVM/MLIR headers.
#define GET_ATTRDEF_CLASSES
#include "NncvGraph/IR/NncvGraphAttrs.h.inc"  // IWYU pragma: keep
#define GET_TYPEDEF_CLASSES
#include "NncvGraph/IR/NncvGraphTypes.h.inc"  // IWYU pragma: keep
// clang-format on

#endif  //! NNCV_C_NNCV_GRAPH_TYPES_HPP_