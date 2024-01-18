#include "nncv/compiler/Conversion/ConvOptimize/OptimizeConv2dUsingWinograd.hpp"
#include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtDialect.hpp"
#include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtOps.hpp"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_OPTIMIZECONV2DUSINGWINOGRAD
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {

namespace LINALGEXT = mlir::nncv::linalg_ext;

static constexpr int64_t outputTileSize = 6;

// Ref:
// https://github.com/openxla/iree/llvm-external-projects/iree-dialects/lib/Dialect/LinalgExt/Passes/ConvertConv2DToWinograd.cpp

static inline int index(int y, int x, int dimy, int dimx) { return (x + dimx * y); }

static inline int index(int z, int y, int x, int w, int dimz, int dimy, int dimx, int dimw) {
  return (w + dimw * (x + dimx * (y + dimy * z)));
}

static bool hasAllOneValues(DenseIntElementsAttr attr) {
  return llvm::all_of(attr, [](APInt element) { return element.isOne(); });
}

static DenseElementsAttr foldFilterTransform(ArrayRef<int64_t> shape, int64_t inputTileSize,
                                             int64_t kernelSize, ShapedType outputType,
                                             const float* G, bool isSplat, float splatValue,
                                             DenseElementsAttr::iterator_range<APFloat>& input,
                                             FloatType floatType, bool isNchw) {
  const int& kh = isNchw ? shape[2] : shape[0];
  const int& kw = isNchw ? shape[3] : shape[1];
  const int& ic = isNchw ? shape[1] : shape[2];
  const int& oc = isNchw ? shape[0] : shape[3];
  const int64_t numElements = inputTileSize * inputTileSize * ic * oc;
  SmallVector<APFloat> output(numElements, APFloat(0.0f));
  for (int d0 = 0; d0 < inputTileSize; d0++) {
    for (int d1 = 0; d1 < inputTileSize; d1++) {
      for (int d2 = 0; d2 < ic; d2++) {
        for (int d3 = 0; d3 < oc; d3++) {
          APFloat accum(0.0f);
          for (int d4 = 0; d4 < kernelSize; d4++) {
            for (int d5 = 0; d5 < kernelSize; d5++) {
              APFloat ival(splatValue);
              if (!isSplat) {
                if (!isNchw) {
                  ival = input[index(d4, d5, d2, d3, kh, kw, ic, oc)];
                } else {
                  ival = input[index(d3, d2, d4, d5, oc, ic, kh, kw)];
                }
              }
              int idx0 = index(d0, d4, inputTileSize, kernelSize);
              int idx1 = index(d1, d5, inputTileSize, kernelSize);
              accum = accum + APFloat(G[idx0]) * ival * APFloat(G[idx1]);
            }
          }
          int odx = index(d0, d1, d2, d3, inputTileSize, inputTileSize, ic, oc);
          output[odx] = accum;
          if (floatType.isF16()) {
            bool losesInfo;
            output[odx].convert(APFloat::IEEEhalf(), APFloat::rmNearestTiesToEven, &losesInfo);
          }
        }
      }
    }
  }
  return DenseElementsAttr::get(outputType, output);
}

template<typename T>
static bool hasValidStridesAndDilations(Operation* op) {
  auto convOp = dyn_cast<T>(op);
  // Check that strides = 1
  if (!hasAllOneValues(convOp.getStrides())) return false;

  // Check that dilations = 1
  if (!hasAllOneValues(convOp.getDilations())) return false;
  return true;
}

static bool isValidConv2d(Operation* op, bool& isNchw) {
  isNchw = isa<linalg::Conv2DNchwFchwOp>(op);
  const bool isNhwc = isa<linalg::Conv2DNhwcHwcfOp>(op);
  if (!(isNchw || isNhwc)) return false;
  return (isNchw ? hasValidStridesAndDilations<linalg::Conv2DNchwFchwOp>(op)
                 : hasValidStridesAndDilations<linalg::Conv2DNhwcHwcfOp>(op));
}

namespace {

template<typename ConvOp>
class FoldWinogradFilterTransform final : public OpRewritePattern<ConvOp> {
 public:
  using OpRewritePattern<ConvOp>::OpRewritePattern;

  LogicalResult matchAndRewrite(ConvOp convOp, PatternRewriter& rewriter) const override {
    bool isNchw;
    if (!isValidConv2d(convOp, isNchw)) return failure();

    // Check that kernel size = 3x3
    Value kernel = convOp.getInputs()[1];
    auto kernelType = kernel.getType().cast<ShapedType>();
    if (!kernelType) return failure();
    ArrayRef<int64_t> kernelShape = kernelType.getShape();
    if (kernelShape.size() != 4) return failure();
    const int64_t kh = isNchw ? kernelShape[2] : kernelShape[0];
    const int64_t kw = isNchw ? kernelShape[3] : kernelShape[1];
    if ((kh != 3) || (kw != 3)) return failure();
    const int64_t kernelSize = kh;
    const int64_t inputTileSize = outputTileSize + kernelSize - 1;

    DenseIntOrFPElementsAttr kernelAttr;
    if (!matchPattern(kernel, m_Constant(&kernelAttr))) { return failure(); }

    Operation* constOp = kernel.getDefiningOp();
    ShapedType type = constOp->getResult(0).getType().cast<ShapedType>();
    auto elemType = type.getElementType().cast<FloatType>();
    ArrayRef<int64_t> shape = type.getShape();
    DenseElementsAttr::iterator_range<APFloat> nonSplatValues = kernelAttr.getValues<APFloat>();
    bool isSplat = kernelAttr.isSplat();
    float splatValue{0.0};
    if (isSplat) { splatValue = kernelAttr.getSplatValue<APFloat>().convertToFloat(); }
    SmallVector<int64_t> resultShape{inputTileSize * inputTileSize, shape[2], shape[3]};
    if (isNchw) {
      resultShape[1] = shape[1];
      resultShape[2] = shape[0];
    }
    auto resultType = RankedTensorType::get(resultShape, elemType);
    auto foldedKernelAttr =
        foldFilterTransform(shape, inputTileSize, kernelSize, resultType, winograd::G_6x6_3x3,
                            isSplat, splatValue, nonSplatValues, elemType, isNchw);
    rewriter.replaceOpWithNewOp<arith::ConstantOp>(constOp, foldedKernelAttr);
    return success();
  }
};

}  // namespace

static Value createCollapse(Value tensor, Location loc, PatternRewriter& rewriter,
                            SmallVectorImpl<int64_t>& outputShape,
                            SmallVectorImpl<ReassociationIndices>& reassociations) {
  auto tensorType = tensor.getType().cast<ShapedType>();
  auto elementTy = tensorType.getElementType();
  auto resultType = RankedTensorType::get(outputShape, elementTy);
  return rewriter.create<tensor::CollapseShapeOp>(loc, resultType, tensor, reassociations);
}

static Value createExpand(Value tensor, Location loc, PatternRewriter& rewriter,
                          SmallVectorImpl<int64_t>& outputShape,
                          SmallVectorImpl<ReassociationIndices>& reassociations) {
  auto tensorType = tensor.getType().cast<ShapedType>();
  auto elementTy = tensorType.getElementType();
  auto resultType = RankedTensorType::get(outputShape, elementTy);
  return rewriter.create<tensor::ExpandShapeOp>(loc, resultType, tensor, reassociations);
}

namespace {
template<typename ConvOp>
class ConvertConvToWinograd final : public OpRewritePattern<ConvOp> {
 public:
  using OpRewritePattern<ConvOp>::OpRewritePattern;

  LogicalResult matchAndRewrite(ConvOp convOp, PatternRewriter& rewriter) const override {
    bool isNchw;
    if (!isValidConv2d(convOp, isNchw)) return failure();

    // Check that kernel has been constant folded (by validating rank = 3)
    Value kernel = convOp.getInputs()[1];
    auto kernelType = kernel.getType().cast<ShapedType>();
    if (!kernelType) return failure();
    Type elementType = kernelType.getElementType();
    ArrayRef<int64_t> kernelShape = kernelType.getShape();
    if (kernelShape.size() != 3) return failure();

    const int64_t kernelSize = 3;
    const int64_t inputTileSize = outputTileSize + kernelSize - 1;

    // Create winograd input transform op
    Location loc = convOp.getLoc();
    Value zero = rewriter.create<arith::ConstantOp>(loc, rewriter.getZeroAttr(elementType));
    Value input = convOp.getInputs()[0];
    auto inputType = input.getType().cast<ShapedType>();
    if (!inputType) return failure();
    SmallVector<int64_t> inputShape(inputType.getShape());
    if (llvm::any_of(inputShape, ShapedType::isDynamic)) return failure();
    assert(inputShape.size() == 4);
    if (isNchw) { LINALGEXT::permute<LINALGEXT::Permutation::NCHW_TO_NHWC>(inputShape); }

    const std::array<int64_t, 2> nhwcImageDimensions{1, 2};
    const std::array<int64_t, 2> nchwImageDimensions{2, 3};
    const size_t numImageDims = nhwcImageDimensions.size();
    SmallVector<int64_t> resultShape(6, inputTileSize);
    llvm::SmallSetVector<int64_t, 2> imageDimensionsSet(nhwcImageDimensions.begin(),
                                                        nhwcImageDimensions.end());
    int outputIndex;
    for (size_t i = 0; i < inputShape.size(); i++) {
      outputIndex = i + numImageDims;
      if (!imageDimensionsSet.contains(i)) {
        resultShape[outputIndex] = inputShape[i];
      } else {
        resultShape[outputIndex] =
            std::ceil((float)(inputShape[i] - kernelSize + 1) / outputTileSize);
      }
    }
    Value emptyTensor = rewriter.create<tensor::EmptyOp>(loc, resultShape, elementType);
    auto& imageDimensions = isNchw ? nchwImageDimensions : nhwcImageDimensions;
    auto winogradInputOp = rewriter.create<LINALGEXT::WinogradInputTransformOp>(
        loc, emptyTensor.getType(), ValueRange{input}, ValueRange{emptyTensor}, outputTileSize,
        kernelSize, imageDimensions);
    Value winogradInput = winogradInputOp.getResult()[0];

    // Add collapse shape
    SmallVector<int64_t> collapsedShape = {resultShape[0] * resultShape[1],
                                           resultShape[2] * resultShape[3] * resultShape[4],
                                           resultShape[5]};
    SmallVector<ReassociationIndices> reassociations = {{0, 1}, {2, 3, 4}, {5}};
    Value collapsedWinogradInput =
        createCollapse(winogradInput, loc, rewriter, collapsedShape, reassociations);

    // Add BatchMatmulOp
    SmallVector<int64_t> bmmShape(collapsedShape.begin(), collapsedShape.end());
    Value output = convOp.getOutputs()[0];
    auto outputType = output.getType().cast<RankedTensorType>();
    SmallVector<int64_t> outputShape(outputType.getShape());
    if (isNchw) { LINALGEXT::permute<LINALGEXT::Permutation::NCHW_TO_NHWC>(outputShape); }
    bmmShape[2] = outputShape[3];
    auto bmmOutputType = RankedTensorType::get(bmmShape, elementType);
    emptyTensor = rewriter.create<tensor::EmptyOp>(loc, bmmShape, elementType);
    auto fillOp = rewriter.create<linalg::FillOp>(loc, ValueRange{zero}, ValueRange{emptyTensor});
    auto bmmOp = rewriter.create<linalg::BatchMatmulOp>(
        loc, bmmOutputType, ValueRange({collapsedWinogradInput, kernel}),
        ValueRange({fillOp.result()}));
    Value bmmResult = bmmOp.getResult(0);

    // Add expand shape
    SmallVector<int64_t> expandedShape = {resultShape[0], resultShape[1], resultShape[2],
                                          resultShape[3], resultShape[4], outputShape[3]};
    reassociations = {{0, 1}, {2, 3, 4}, {5}};
    Value expandedBmmResult = createExpand(bmmResult, loc, rewriter, expandedShape, reassociations);

    // Convert back into original domain
    SmallVector<int64_t> paddedResultShape(outputShape.size(), 0);
    for (size_t i = 0; i < outputShape.size(); i++) {
      if (!imageDimensionsSet.contains(i)) {
        paddedResultShape[i] = outputShape[i];
      } else {
        paddedResultShape[i] = resultShape[i + numImageDims] * outputTileSize;
      }
    }
    if (isNchw) { LINALGEXT::permute<LINALGEXT::Permutation::NHWC_TO_NCHW>(paddedResultShape); }
    emptyTensor = rewriter.create<tensor::EmptyOp>(loc, paddedResultShape, elementType);
    auto winogradOutputOp = rewriter.create<LINALGEXT::WinogradOutputTransformOp>(
        loc, emptyTensor.getType(), ValueRange{expandedBmmResult}, ValueRange{emptyTensor},
        outputTileSize, kernelSize, imageDimensions);
    Value paddedOutput = winogradOutputOp.getResult()[0];

    // Extract slice
    SmallVector<OpFoldResult> offsets(outputShape.size(), rewriter.getIndexAttr(0));
    SmallVector<OpFoldResult> strides(outputShape.size(), rewriter.getIndexAttr(1));
    SmallVector<OpFoldResult> sizes;
    for (const int64_t shape : outputType.getShape()) sizes.push_back(rewriter.getIndexAttr(shape));
    auto winogradOutput = rewriter.create<tensor::ExtractSliceOp>(loc, outputType, paddedOutput,
                                                                  offsets, sizes, strides);

    Value result = convOp.getResult(0);
    result.replaceAllUsesWith(winogradOutput);
    return success();
  }
};

class OptimizeConv2dUsingWinogradPass
    : public impl::OptimizeConv2dUsingWinogradBase<OptimizeConv2dUsingWinogradPass> {
  void getDependentDialects(DialectRegistry& registry) const override {
    registry.insert<linalg::LinalgDialect, LINALGEXT::NNCVLinalgExtDialect>();
  }

  void runOnOperation() override {
    MLIRContext* context = &getContext();
    RewritePatternSet patterns(&getContext());
    patterns.insert<FoldWinogradFilterTransform<linalg::Conv2DNchwFchwOp>,
                    FoldWinogradFilterTransform<linalg::Conv2DNhwcHwcfOp>,
                    ConvertConvToWinograd<linalg::Conv2DNhwcHwcfOp>,
                    ConvertConvToWinograd<linalg::Conv2DNchwFchwOp>>(context);
    if (failed(applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      return signalPassFailure();
    }
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createOptimizeConv2dUsingWinogradPass() {
  return std::make_unique<OptimizeConv2dUsingWinogradPass>();
}
}  // namespace mlir::nncv