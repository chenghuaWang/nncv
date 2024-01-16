#ifndef NNCV_LINALG_EXT_OPS_HPP_
#define NNCV_LINALG_EXT_OPS_HPP_

#include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtInterface.hpp"
#include "mlir/IR/Attributes.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/Interfaces/ControlFlowInterfaces.h"
#include "mlir/Interfaces/InferTypeOpInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/TilingInterface.h"

#include "LinalgExt/IR/LinalgExtEnums.h.inc"  // IWYU pragma: export

#define GET_ATTRDEF_CLASSES
#include "LinalgExt/IR/LinalgExtAttrs.h.inc"  // IWYU pragma: export

#define GET_OP_CLASSES
#include "LinalgExt/IR/LinalgExtOps.h.inc"  // IWYU pragma: export

#endif  //! NNCV_LINALG_EXT_OPS_HPP_