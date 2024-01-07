#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"

#include "mlir/Dialect/Utils/ReshapeOpsUtils.h"
#include "mlir/Support/LogicalResult.h"

#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"

namespace mlir::nncv {

inline bool isConv2d1x1(mlir::DenseIntElementsAttr& stride, mlir::DenseIntElementsAttr& dialation) {
  bool strideAllOne =
      llvm::all_of(stride, [](APInt element) { return element.getSExtValue() == 1; });
  bool dialationAllOne =
      llvm::all_of(dialation, [](APInt element) { return element.getSExtValue() == 1; });

  if (!strideAllOne || !dialationAllOne) { return false; }

  return true;
}

namespace {

// Input: NHWC.
// Kernel: HWCF.
class ConvertConv2D1x1NhwcHwcf final
    : public mlir::OpRewritePattern<mlir::linalg::Conv2DNhwcHwcfOp> {
 public:
  using OpRewritePattern::OpRewritePattern;

  mlir::LogicalResult matchAndRewrite(mlir::linalg::Conv2DNhwcHwcfOp convOp,
                                      mlir::PatternRewriter& rewriter) const override {
    // get all infomation from this op
    auto inputType = llvm::cast<ShapedType>(convOp.getInputs()[0].getType());
    auto filterType = llvm::cast<ShapedType>(convOp.getInputs()[1].getType());
    auto outputType = llvm::cast<ShapedType>(convOp.getOutputs()[0].getType());
    auto stride = convOp.getStrides();
    auto dialation = convOp.getDilations();

    auto loc = convOp->getLoc();

    // Is Conv 2d is 1x1?
    if (!isConv2d1x1(stride, dialation)) { return mlir::failure(); }
    auto shape = filterType.getShape();
    if (shape[0] != 1 || shape[1] != 1) { return mlir::failure(); }

    // collapse shape 3 times
    llvm::SmallVector<ReassociationIndices> Conv2dReassocIndices = {{0, 1, 2}, {3}};

    auto oldInputShape = inputType.getShape();
    auto oldFilterShape = filterType.getShape();
    auto oldOutputShape = outputType.getShape();

    auto newLhsType = mlir::RankedTensorType::get(
        {oldInputShape[0] * oldInputShape[1] * oldInputShape[2], oldInputShape[3]},
        inputType.getElementType());
    auto newRhsType = mlir::RankedTensorType::get(
        {oldFilterShape[0] * oldFilterShape[1] * oldFilterShape[2], oldFilterShape[3]},
        filterType.getElementType());
    auto newOutType = mlir::RankedTensorType::get(
        {oldOutputShape[0] * oldOutputShape[1] * oldOutputShape[2], oldOutputShape[3]},
        outputType.getElementType());

    auto newLhs = rewriter.create<mlir::tensor::CollapseShapeOp>(
        loc, newLhsType, convOp.getInputs()[0], Conv2dReassocIndices);
    auto newRhs = rewriter.create<mlir::tensor::CollapseShapeOp>(
        loc, newRhsType, convOp.getInputs()[1], Conv2dReassocIndices);
    auto newOut = rewriter.create<mlir::tensor::CollapseShapeOp>(
        loc, newOutType, convOp.getOutputs()[0], Conv2dReassocIndices);

    // generate linalg.matmul
    auto op = rewriter.create<mlir::linalg::MatmulOp>(loc, newOutType,
                                                      llvm::ArrayRef<mlir::Value>{newLhs, newRhs},
                                                      llvm::ArrayRef<mlir::Value>{newOut});

    // expand result
    mlir::Value result = op.getResults().front();
    auto reshapedResult =
        rewriter.create<mlir::tensor::ExpandShapeOp>(loc, outputType, result, Conv2dReassocIndices);

    // replace convOp
    rewriter.replaceOp(convOp, llvm::ArrayRef<mlir::Value>{reshapedResult});

    return success();
  }
};

// Input: NCHW.
// Kernel: FCHW.
// BUG: Dims is Error
class ConvertConv2D1x1NchwFchw final
    : public mlir::OpRewritePattern<mlir::linalg::Conv2DNchwFchwOp> {
 public:
  using OpRewritePattern::OpRewritePattern;

  mlir::LogicalResult matchAndRewrite(mlir::linalg::Conv2DNchwFchwOp convOp,
                                      mlir::PatternRewriter& rewriter) const override {
    // get all infomation from this op
    auto inputType = llvm::cast<ShapedType>(convOp.getInputs()[0].getType());
    auto filterType = llvm::cast<ShapedType>(convOp.getInputs()[1].getType());
    auto outputType = llvm::cast<ShapedType>(convOp.getOutputs()[0].getType());
    auto stride = convOp.getStrides();
    auto dialation = convOp.getDilations();

    auto loc = convOp->getLoc();

    // Is Conv 2d is 1x1?
    if (!isConv2d1x1(stride, dialation)) { return mlir::failure(); }
    auto shape = filterType.getShape();
    if (shape[2] != 1 || shape[3] != 1) { return mlir::failure(); }

    // collapse shape 3 times
    llvm::SmallVector<ReassociationIndices> Conv2dReassocIndices = {{0, 1, 2}, {3}};

    auto oldInputShape = inputType.getShape();
    auto oldFilterShape = filterType.getShape();
    auto oldOutputShape = outputType.getShape();

    auto newLhsType = mlir::RankedTensorType::get(
        {oldInputShape[0] * oldInputShape[1] * oldInputShape[2], oldInputShape[3]},
        inputType.getElementType());
    auto newRhsType = mlir::RankedTensorType::get(
        {oldFilterShape[0] * oldFilterShape[1] * oldFilterShape[2], oldFilterShape[3]},
        filterType.getElementType());
    auto newOutType = mlir::RankedTensorType::get(
        {oldOutputShape[0] * oldOutputShape[1] * oldOutputShape[2], oldOutputShape[3]},
        outputType.getElementType());

    auto newLhs = rewriter.create<mlir::tensor::CollapseShapeOp>(
        loc, newLhsType, convOp.getInputs()[0], Conv2dReassocIndices);
    auto newRhs = rewriter.create<mlir::tensor::CollapseShapeOp>(
        loc, newRhsType, convOp.getInputs()[1], Conv2dReassocIndices);
    auto newOut = rewriter.create<mlir::tensor::CollapseShapeOp>(
        loc, newOutType, convOp.getOutputs()[0], Conv2dReassocIndices);

    // generate linalg.matmul
    auto op = rewriter.create<mlir::linalg::MatmulOp>(loc, newOutType,
                                                      llvm::ArrayRef<mlir::Value>{newLhs, newRhs},
                                                      llvm::ArrayRef<mlir::Value>{newOut});

    // expand result
    mlir::Value result = op.getResults().front();
    auto reshapedResult =
        rewriter.create<mlir::tensor::ExpandShapeOp>(loc, outputType, result, Conv2dReassocIndices);

    // replace convOp
    rewriter.replaceOp(convOp, llvm::ArrayRef<mlir::Value>{reshapedResult});

    return success();
  }
};

class ConvertConv2D1x1ToMatmul
    : public mlir::nncv::ConvertConv2D1x1ToMatmulBase<ConvertConv2D1x1ToMatmul> {
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::linalg::LinalgDialect, mlir::tensor::TensorDialect>();
    return;
  }

  void runOnOperation() override {
    mlir::MLIRContext* context = &getContext();
    mlir::RewritePatternSet patterns(context);

    // insert rewrite patternt
    patterns.insert<ConvertConv2D1x1NhwcHwcf, ConvertConv2D1x1NchwFchw>(context);

    // do rewrite
    if (mlir::failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      // no need to signalPassFailure();
      return;
    }

    return;
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createConvertConv2D1x1ToMatmulPass() {
  return std::make_unique<ConvertConv2D1x1ToMatmul>();
}
}  // namespace mlir::nncv