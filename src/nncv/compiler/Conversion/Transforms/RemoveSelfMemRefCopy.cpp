#include "nncv/compiler/Conversion/Transforms/RemoveSelfMemRefCopy.hpp"

#include "mlir/Conversion/LLVMCommon/ConversionTarget.h"
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

namespace mlir::nncv {
#define GEN_PASS_DEF_REMOVESELFMEMREFCOPY
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class MemRefSelfCopyPattern final : public OpRewritePattern<memref::CopyOp> {
 public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(memref::CopyOp op, PatternRewriter& rewriter) const override {
    auto source = op.getSource();
    auto target = op.getTarget();
    if (source == target) {
      rewriter.eraseOp(op);
      return success();
    }
    return failure();
  }
};

class RemoveSelfMemRefCopyPass : public impl::RemoveSelfMemRefCopyBase<RemoveSelfMemRefCopyPass> {
 public:
  void runOnOperation() override {
    mlir::LLVMConversionTarget target(getContext());
    mlir::RewritePatternSet patterns(&getContext());
    patterns.insert<MemRefSelfCopyPattern>(&getContext());
    if (failed(mlir::applyPartialConversion(getOperation(), target, std::move(patterns))))
      signalPassFailure();
  }
};

}  // namespace

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createRemoveSelfMemRefCopyPass() {
  return std::make_unique<RemoveSelfMemRefCopyPass>();
}

}  // namespace mlir::nncv