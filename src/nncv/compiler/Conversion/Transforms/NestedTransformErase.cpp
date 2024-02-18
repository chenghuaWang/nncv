#include "mlir/Dialect/Transform/IR/TransformInterfaces.h"
#include "nncv/compiler/Conversion/Transforms/NestedTransformErasePass.hpp"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Dialect/Transform/IR/TransformDialect.h"
#include "mlir/Transforms/DialectConversion.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_NESTEDTRANSFORMERASE
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class NestedTransformErasePass : public impl::NestedTransformEraseBase<NestedTransformErasePass> {
 public:
  void runOnOperation() override {
    getOperation()->walk<WalkOrder::PreOrder>([&](Operation* nestedOp) {
      if (mlir::isa<mlir::transform::TransformOpInterface>(nestedOp)) {
        nestedOp->erase();
        return WalkResult::skip();
      }
      return WalkResult::advance();
    });
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createNestedTransformErasePass() {
  return std::make_unique<NestedTransformErasePass>();
}

}  // namespace mlir::nncv