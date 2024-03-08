#include "nncv/compiler/Conversion/Transforms/RegisterMemToGpu.hpp"

#include "mlir/Conversion/LLVMCommon/ConversionTarget.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/GPU/IR/GPUDialect.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Dialect/Transform/IR/TransformDialect.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/PatternMatch.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_REGISTERMEMTOGPU
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class InsertBeforeGpuLaunchFunc final : public OpRewritePattern<mlir::gpu::LaunchFuncOp> {
 public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(mlir::gpu::LaunchFuncOp op,
                                PatternRewriter& rewriter) const override {
    // get operations
    auto args = op.getKernelOperands();
    auto argsNum = op.getNumKernelOperands();
    for (size_t i = 0; i < argsNum; ++i) {
      if (args[i].getType().isa<mlir::MemRefType>()
          || args[i].getType().isa<mlir::UnrankedMemRefType>()) {
        // set insertion point
        mlir::OpBuilder::InsertionGuard guard(rewriter);
        rewriter.setInsertionPoint(op);
        rewriter.create<mlir::gpu::HostRegisterOp>(op->getLoc(), args[i]);
      }
    }

    return success();
  }
};

class RegisterMemToGpuPass : public impl::RegisterMemToGpuBase<RegisterMemToGpuPass> {
 public:
  void runOnOperation() override {
    IRRewriter rewriter(&getContext());
    getOperation()->walk([&](mlir::gpu::LaunchFuncOp op) {
      auto args = op.getKernelOperands();
      auto argsNum = op.getNumKernelOperands();
      for (size_t i = 0; i < argsNum; ++i) {
        if (args[i].getType().isa<mlir::MemRefType>()) {
          // set insertion point
          mlir::OpBuilder::InsertionGuard guard(rewriter);
          rewriter.setInsertionPoint(op);
          mlir::Value ut = rewriter.create<mlir::memref::CastOp>(
              op.getLoc(), /*toType*/
              mlir::UnrankedMemRefType::get(
                  args[i].getType().cast<mlir::MemRefType>().getElementType(), {}),
              /*fromValue*/ args[i]);
          rewriter.create<mlir::gpu::HostRegisterOp>(op.getLoc(), ut);
        } else if (args[i].getType().isa<mlir::UnrankedMemRefType>()) {
          // set insertion point
          mlir::OpBuilder::InsertionGuard guard(rewriter);
          rewriter.setInsertionPoint(op);
          rewriter.create<mlir::gpu::HostRegisterOp>(op.getLoc(), args[i]);
        }
      }
    });
  }
};

}  // namespace

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createRegisterMemToGpuPass() {
  return std::make_unique<RegisterMemToGpuPass>();
}

}  // namespace mlir::nncv
