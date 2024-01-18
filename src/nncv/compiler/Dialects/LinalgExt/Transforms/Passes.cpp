#include "nncv/compiler/Dialects/LinalgExt/Transforms/Passes.hpp"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Transforms/Passes.h"

namespace mlir::nncv::linalg_ext {

namespace detail {
#define GEN_PASS_REGISTRATION
#include "LinalgExt/Passes/Passes.h.inc"  // IWYU pragma: export
}  // namespace detail

}  // namespace mlir::nncv::linalg_ext
