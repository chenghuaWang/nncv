#include "nncv/compiler/Conversion/ConvOptimize/OptimizeConv2dUsingWinograd.hpp"

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

namespace mlir::nncv {
#define GEN_PASS_DEF_OPTIMIZECONV2DUSINGWINOGRAD
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {

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

namespace {}

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

namespace {}

std::unique_ptr<mlir::Pass> createOptimizeConv2dUsingWinogradPass();
}  // namespace mlir::nncv