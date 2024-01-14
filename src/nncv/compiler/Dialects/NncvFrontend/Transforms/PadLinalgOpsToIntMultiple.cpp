#include <cmath>

#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"

namespace mlir::nncv {
namespace {

class PadMatmulOp : public OpInterfaceRewritePattern<linalg::LinalgOp> {
 public:
  PadMatmulOp(MLIRContext* context, int size, PatternBenefit benefit = 1)
      : OpInterfaceRewritePattern(context, benefit), paddingSize(size) {}
  LogicalResult matchAndRewrite(linalg::LinalgOp linalgOp,
                                PatternRewriter& rewriter) const override {
    Operation* op = linalgOp.getOperation();
    auto opLocation = op->getLoc();

    // only linalg::BatchMatMulOp and linalg::MatMulOp can be optimized.
    if (!mlir::isa<mlir::linalg::BatchMatmulOp>(op) && !mlir::isa<mlir::linalg::MatmulOp>(op)) {
      return mlir::failure();
    }

    auto lhs = linalgOp.getDpsInputOperand(0)->get();
    auto rhs = linalgOp.getDpsInputOperand(1)->get();
    auto res = linalgOp.getDpsInitOperand(0)->get();
    auto lhsType = dyn_cast<mlir::RankedTensorType>(lhs.getType());
    auto rhsType = dyn_cast<mlir::RankedTensorType>(lhs.getType());
    auto resType = dyn_cast<mlir::RankedTensorType>(lhs.getType());

    // Only ranked  tensor and static shape tensor can be optimized using padding mem.
    if (!lhsType || !resType || !lhsType.hasStaticShape() || !rhsType.hasStaticShape()) {
      return mlir::failure();
    }

    auto lhsShape = lhsType.getShape();
    auto rhsShape = rhsType.getShape();

    auto _B = mlir::isa<mlir::linalg::BatchMatmulOp>(op) ? lhsShape[0] : -1;
    auto _M = mlir::isa<mlir::linalg::BatchMatmulOp>(op) ? lhsShape[1] : lhsShape[0];
    auto _K = lhsShape.back();
    auto _N = rhsShape.back();

    int newM = std::ceil(float(_M) / paddingSize) * paddingSize;
    int newN = std::ceil(float(_N) / paddingSize) * paddingSize;
    int newK = std::ceil(float(_K) / paddingSize) * paddingSize;

    auto paddingForM = newM - _M;
    auto paddingForN = newN - _N;
    auto paddingForK = newK - _K;

    // all padding delta is 0, no need to padding.
    if (paddingForK == 0 && paddingForM == 0 && paddingForN == 0) { return mlir::failure(); }

    auto getFullShape = [&](llvm::ArrayRef<int> dims) {
      llvm::SmallVector<int64_t, 4> shape;
      if (mlir::isa<mlir::linalg::BatchMatmulOp>(op)) { shape.push_back(_B); }
      llvm::append_range(shape, dims);
      return shape;
    };

    auto paddedLhsType =
        mlir::RankedTensorType::get(getFullShape({newK, newN}), lhsType.getElementType());
    auto paddedRhsType =
        mlir::RankedTensorType::get(getFullShape({newK, newN}), rhsType.getElementType());

    mlir::Value paddingLhsValue = rewriter.create<mlir::arith::ConstantOp>(
        opLocation, rewriter.getZeroAttr(paddedLhsType.getElementType()));
    mlir::Value paddingRhsValue = rewriter.create<mlir::arith::ConstantOp>(
        opLocation, rewriter.getZeroAttr(paddedRhsType.getElementType()));

    auto createPadding = [&](llvm::ArrayRef<int64_t> padding) {
      llvm::SmallVector<mlir::OpFoldResult> res;
      if (mlir::isa<mlir::linalg::BatchMatmulOp>(op)) {
        res.push_back(rewriter.getI64IntegerAttr(0));
      }
      for (auto pad : padding) { res.push_back(rewriter.getI64IntegerAttr(pad)); }
      return res;
    };

    mlir::Value paddedLhs = lhs;
    mlir::Value paddedRhs = rhs;
    if (paddingForM > 0 || paddingForK > 0) {
      paddedLhs = rewriter.create<mlir::tensor::PadOp>(
          opLocation, paddedLhsType, lhs, createPadding({0, 0}),
          createPadding({paddingForM, paddingForK}), paddingLhsValue);
    }
    if (paddingForK > 0 && paddingForN > 0) {
      paddedRhs = rewriter.create<mlir::tensor::PadOp>(
          opLocation, paddedRhsType, rhs, createPadding({0, 0}),
          createPadding({paddingForK, paddingForN}), paddingRhsValue);
    }

    // Padding for K-dim doesn't change result size.
    if (paddingForM == 0 && paddingForN == 0) {
      auto paddedMatmulOp = mlir::clone(rewriter, linalgOp, {resType},
                                        llvm::ArrayRef<Value>{paddedLhs, paddedRhs, res});
      rewriter.replaceOp(linalgOp, paddedMatmulOp->getResults());
    } else {
      auto newResultType =
          RankedTensorType::get(getFullShape({newM, newN}), resType.getElementType());
      Value resultPaddingValue = rewriter.create<arith::ConstantOp>(
          opLocation, rewriter.getZeroAttr(resType.getElementType()));
      Value paddedResult = rewriter.create<tensor::PadOp>(
          opLocation, newResultType, res, createPadding({0, 0}),
          createPadding({paddingForM, paddingForN}), resultPaddingValue);
      auto paddedMatmulOp = mlir::clone(rewriter, linalgOp, {newResultType},
                                        ArrayRef<Value>{paddedLhs, paddedRhs, paddedResult});

      auto zero = rewriter.getI64IntegerAttr(0);
      auto one = rewriter.getI64IntegerAttr(1);
      auto mAttr = rewriter.getIndexAttr(_M);
      auto nAttr = rewriter.getIndexAttr(_N);
      SmallVector<OpFoldResult> offsets, strides, sizes;
      if (mlir::isa<mlir::linalg::BatchMatmulOp>(op)) {
        offsets.assign(3, zero);
        strides.assign(3, one);
        sizes = {rewriter.getIndexAttr(_B), mAttr, nAttr};
      } else {
        offsets.assign(2, zero);
        strides.assign(2, one);
        sizes = {mAttr, nAttr};
      }
      rewriter.replaceOpWithNewOp<tensor::ExtractSliceOp>(linalgOp, paddedMatmulOp->getResults()[0],
                                                          offsets, sizes, strides);
    }

    return mlir::success();
  }

 private:
  int paddingSize;
};

class PadLinalgOpsToIntegerMultiple : public PadLinalgOpsBase<PadLinalgOpsToIntegerMultiple> {
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::linalg::LinalgDialect>();
    return;
  }

  void runOnOperation() override {
    MLIRContext* context = &getContext();
    RewritePatternSet patterns(context);

    patterns.insert<PadMatmulOp>(context, paddingSize);
    if (failed(applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      return signalPassFailure();
    }

    return;
  }
};
}  // namespace

std::unique_ptr<mlir::Pass> createPadLinalgOpsToIntegerMultiplePass() {
  return std::make_unique<PadLinalgOpsToIntegerMultiple>();
}

}  // namespace mlir::nncv
