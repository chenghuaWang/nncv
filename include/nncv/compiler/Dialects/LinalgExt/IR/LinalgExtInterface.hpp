#ifndef NNCV_LINALG_EXT_INTERFACE_HPP_
#define NNCV_LINALG_EXT_INTERFACE_HPP_

#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/Interfaces/DestinationStyleOpInterface.h"
#include "mlir/Interfaces/InferTypeOpInterface.h"
#include "mlir/Support/LLVM.h"

namespace mlir::nncv::linalg_ext {

class LinalgExtOp;

namespace detail {
LogicalResult verifyLinalgExtOpInterface(Operation* op);
}

#include "LinalgExt/IR/LinalgExtOps.h.inc"  // IWYU pragma: export

#include "LinalgExt/IR/LinalgExtOpInterfaces.h.inc"  // IWYU pragma: export
}  // namespace mlir::nncv::linalg_ext

#endif  //! NNCV_LINALG_EXT_INTERFACE_HPP_