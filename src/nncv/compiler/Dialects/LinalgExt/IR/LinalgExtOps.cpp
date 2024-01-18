#include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtOps.hpp"
#include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtDialect.hpp"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/Utils.h"
#include "mlir/Dialect/Arith/Utils/Utils.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Linalg/Utils/Utils.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Utils/StructuredOpsUtils.h"
#include "mlir/IR/Attributes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/Diagnostics.h"
#include "mlir/IR/OperationSupport.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/TypeUtilities.h"
#include "mlir/IR/Value.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Support/LogicalResult.h"
#include "mlir/Support/MathExtras.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/TypeSwitch.h"

using namespace mlir;
using namespace mlir::nncv::linalg_ext;

/// Returns a memref.subview or a tensor.extract_slice based on the type of the
/// `source`.
static Value getSlice(OpBuilder& b, Location loc, Value source, ArrayRef<OpFoldResult> offsets,
                      ArrayRef<OpFoldResult> sizes, ArrayRef<OpFoldResult> strides) {
  return TypeSwitch<Type, Value>(source.getType())
      .Case<RankedTensorType>([&](RankedTensorType t) -> Value {
        return b.create<tensor::ExtractSliceOp>(loc, source, offsets, sizes, strides);
      })
      .Case<MemRefType>([&](MemRefType type) -> Value {
        return b.create<memref::SubViewOp>(loc, source, offsets, sizes, strides);
      })
      .Default([&](Type t) { return nullptr; });
}

//===----------------------------------------------------------------------===//
// Winograd Input Transform Op
//===----------------------------------------------------------------------===//
LogicalResult WinogradInputTransformOp::verify() {
  Operation* op = getOperation();
  if (getNumDpsInputs() != 1) { return op->emitOpError("expected one input operand"); }
  if (getNumDpsInits() != 1) { return op->emitOpError("expected one output operand"); }
  auto inputType = input().getType().cast<ShapedType>();
  auto outputType = output().getType().cast<ShapedType>();
  if (outputType.getElementType() != inputType.getElementType()) {
    return op->emitOpError("expected input/output element types to be identical");
  }
  unsigned inputRank = inputType.getRank();
  unsigned outputRank = outputType.getRank();

  if (inputRank != 2 && inputRank != 4) {
    return op->emitOpError("expected input operand to have rank either 2 or 4");
  }

  if (inputRank == 2) {
    if (outputRank != 2) {
      return op->emitOpError("expected output operand to have rank 2 if input is of rank 2");
    }
    return success();
  }

  if (getOutputOperandRank() != getInputOperandRank() + 2) {
    return op->emitOpError("expected output rank to be equal to input rank + 2");
  }
  const SmallVector<int64_t> imageDims = imageDimensions();
  const size_t numImageDims = imageDims.size();
  llvm::SmallSetVector<int64_t, 2> imageDimsSet(imageDims.begin(), imageDims.end());
  if (imageDims.size() != 2) { return op->emitOpError("expected only 2 image dimensions"); }
  if (!isNchw() && !isNhwc()) {
    return op->emitOpError("expect image dimensions to be either [1, 2] or [2, 3]");
  }
  const int64_t outputTileSize = getOutputTileSize();
  const int64_t kernelSize = getKernelSize();
  const int64_t inputTileSize = getInputTileSize();
  SmallVector<int64_t> expectedOutputShape(getOutputOperandRank(), inputTileSize);
  int outputIndex;
  ArrayRef<int64_t> inputShape = inputType.getShape();
  for (size_t i = 0; i < inputShape.size(); i++) {
    outputIndex = i + numImageDims;
    if (ShapedType::isDynamic(inputShape[i])) {
      expectedOutputShape[outputIndex] = inputShape[i];
      continue;
    }
    if (!imageDimsSet.contains(i)) {
      expectedOutputShape[outputIndex] = inputShape[i];
    } else {
      expectedOutputShape[outputIndex] =
          std::ceil((float)(inputShape[i] - kernelSize + 1) / outputTileSize);
    }
  }
  if (isNchw()) { permute<Permutation::TTNCHW_TO_TTNHWC>(expectedOutputShape); }
  ArrayRef<int64_t> outputShape = outputType.getShape();
  if (failed(verifyCompatibleShape(expectedOutputShape, outputShape))) {
    return op->emitOpError("incompatible output shape");
  }
  return success();
}

SmallVector<Range> WinogradInputTransformOp::getIterationDomain(OpBuilder& builder) {
  Location loc = getLoc();
  Value zero = builder.create<mlir::arith::ConstantIndexOp>(loc, 0);
  Value one = builder.create<mlir::arith::ConstantIndexOp>(loc, 1);
  Value source = input();
  SmallVector<int64_t> imageDims = imageDimensions();
  llvm::SmallSetVector<int64_t, 2> imageDimsSet(imageDims.begin(), imageDims.end());
  SmallVector<Range> loopBounds(imageDims.size());
  int count = 0;
  for (auto dim : llvm::seq<int64_t>(0, getInputOperandRank())) {
    if (!imageDimsSet.contains(dim)) {
      loopBounds[count].offset = zero;
      loopBounds[count].size = getDimValue(builder, loc, source, dim);
      loopBounds[count].stride = one;
      count++;
    }
  }
  return loopBounds;
}

SmallVector<utils::IteratorType> WinogradInputTransformOp::getLoopIteratorTypes() {
  SmallVector<utils::IteratorType> iteratorTypes(getIterationDomainRank(),
                                                 utils::IteratorType::parallel);
  return iteratorTypes;
}

FailureOr<TilingResult> WinogradInputTransformOp::getTiledImplementation(
    OpBuilder& builder, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes) {
  Location loc = getLoc();
  auto one = builder.getIndexAttr(1);
  auto zero = builder.getIndexAttr(0);
  const int cDim = channelDim();

  assert(offsets.size() == 2);
  SmallVector<OpFoldResult> inputOffsets(getInputOperandRank(), zero);
  SmallVector<OpFoldResult> outputOffsets(getOutputOperandRank(), zero);
  outputOffsets[2] = inputOffsets[0] = offsets[0];
  outputOffsets[5] = inputOffsets[cDim] = offsets[1];

  SmallVector<OpFoldResult> inputStrides(getInputOperandRank(), one);
  SmallVector<OpFoldResult> outputStrides(getOutputOperandRank(), one);

  assert(sizes.size() == 2);
  auto inputShape = input().getType().cast<ShapedType>().getShape();
  auto outputShape = output().getType().cast<ShapedType>().getShape();
  SmallVector<OpFoldResult> inputSizes = getAsOpFoldResult(builder.getIndexArrayAttr(inputShape));
  SmallVector<OpFoldResult> outputSizes = getAsOpFoldResult(builder.getIndexArrayAttr(outputShape));
  outputSizes[2] = inputSizes[0] = sizes[0];
  outputSizes[5] = inputSizes[cDim] = sizes[1];

  SmallVector<Value> tiledOperands;
  tiledOperands.emplace_back(
      getSlice(builder, loc, input(), inputOffsets, inputSizes, inputStrides));
  tiledOperands.emplace_back(
      getSlice(builder, loc, output(), outputOffsets, outputSizes, outputStrides));

  SmallVector<Type, 4> resultTypes;
  if (hasTensorSemantics()) { resultTypes.push_back(tiledOperands[1].getType()); }

  Operation* tiledOp = mlir::clone(builder, getOperation(), resultTypes, tiledOperands);

  return TilingResult{{tiledOp}, SmallVector<Value>(tiledOp->getResults())};
}

LogicalResult WinogradInputTransformOp::getResultTilePosition(
    OpBuilder& builder, unsigned resultNumber, ArrayRef<OpFoldResult> offsets,
    ArrayRef<OpFoldResult> sizes, SmallVector<OpFoldResult>& resultOffsets,
    SmallVector<OpFoldResult>& resultSizes) {
  if (resultNumber == 0) {
    auto resultShape = output().getType().cast<ShapedType>().getShape();
    resultSizes = getAsOpFoldResult(builder.getIndexArrayAttr(resultShape));
    resultOffsets = SmallVector<OpFoldResult>(getOutputOperandRank(), builder.getIndexAttr(0));
    resultOffsets[2] = offsets[0];
    resultOffsets[5] = offsets[1];
    resultSizes[2] = sizes[0];
    resultSizes[5] = sizes[1];
    return success();
  }
  return failure();
}

LogicalResult WinogradInputTransformOp::fold(FoldAdaptor, SmallVectorImpl<OpFoldResult>&) {
  return memref::foldMemRefCast(*this);
}

LogicalResult WinogradInputTransformOp::reifyResultShapes(
    OpBuilder& b, ReifiedRankedShapedTypeDims& reifiedReturnShapes) {
  return cast<LinalgExtOp>(getOperation()).reifyResultShapes(b, reifiedReturnShapes);
}

//===----------------------------------------------------------------------===//
// Winograd output Transform Op
//===----------------------------------------------------------------------===//
LogicalResult WinogradOutputTransformOp::verify() {
  Operation* op = getOperation();
  if (getNumDpsInputs() != 1) { return op->emitOpError("expected one input operand"); }
  if (getNumDpsInits() != 1) { return op->emitOpError("expected one output operand"); }
  auto inputType = input().getType().cast<ShapedType>();
  auto outputType = output().getType().cast<ShapedType>();
  unsigned inputRank = inputType.getRank();
  unsigned outputRank = outputType.getRank();

  if (inputRank != 2 && inputRank != 6) {
    return op->emitOpError("expected input operand to have rank either 2 or 6");
  }

  if (inputRank == 2) {
    if (outputRank != 2) {
      return op->emitOpError("expected output operand to have rank 2 if input is of rank 2");
    }
    return success();
  }
  ArrayRef<int64_t> outputShape = outputType.getShape();
  if (outputType.getElementType() != inputType.getElementType()) {
    return op->emitOpError("expected input/output element types to be identical");
  }
  if (outputRank != inputRank - 2) {
    return op->emitOpError("expected output rank to be equal to input rank - 2");
  }
  const SmallVector<int64_t> imageDims = imageDimensions();
  const size_t numImageDims = imageDims.size();
  llvm::SmallSetVector<int64_t, 2> imageDimsSet(imageDims.begin(), imageDims.end());
  if (imageDims.size() != 2) { return op->emitOpError("expected only 2 image dimensions"); }
  if (!isNchw() && !isNhwc()) {
    return op->emitOpError("expect image dimensions to be either [1, 2] or [2, 3]");
  }
  SmallVector<int64_t> inputShape(inputType.getShape());
  if (isNchw()) { permute<Permutation::TTNHWC_TO_TTNCHW>(inputShape); }
  const int64_t outputTileSize = getOutputTileSize();
  SmallVector<int64_t> expectedOutputShape(getOutputOperandRank(), 1);
  int outputIndex;
  for (int i = numImageDims; i < inputShape.size(); i++) {
    outputIndex = i - numImageDims;
    if (!imageDimsSet.contains(outputIndex)) {
      expectedOutputShape[outputIndex] = inputShape[i];
    } else {
      expectedOutputShape[outputIndex] = outputTileSize * inputShape[i];
    }
  }
  if (failed(verifyCompatibleShape(expectedOutputShape, outputShape))) {
    return op->emitOpError("incompatible output shape");
  }
  return success();
}

SmallVector<Range> WinogradOutputTransformOp::getIterationDomain(OpBuilder& builder) {
  Location loc = getLoc();
  Value zero = builder.create<arith::ConstantIndexOp>(loc, 0);
  Value one = builder.create<arith::ConstantIndexOp>(loc, 1);
  Value source = output();
  SmallVector<int64_t> imageDims = imageDimensions();
  llvm::SmallSetVector<int64_t, 2> imageDimsSet(imageDims.begin(), imageDims.end());
  SmallVector<Range> loopBounds(imageDims.size());
  int count = 0;
  for (auto dim : llvm::seq<int64_t>(0, getOutputOperandRank())) {
    if (!imageDimsSet.contains(dim)) {
      loopBounds[count].offset = zero;
      loopBounds[count].size = getDimValue(builder, loc, source, dim);
      loopBounds[count].stride = one;
      count++;
    }
  }
  return loopBounds;
}

SmallVector<utils::IteratorType> WinogradOutputTransformOp::getLoopIteratorTypes() {
  SmallVector<utils::IteratorType> iteratorTypes(getIterationDomainRank(),
                                                 utils::IteratorType::parallel);
  return iteratorTypes;
}

FailureOr<TilingResult> WinogradOutputTransformOp::getTiledImplementation(
    OpBuilder& builder, ArrayRef<OpFoldResult> offsets, ArrayRef<OpFoldResult> sizes) {
  Location loc = getLoc();
  auto one = builder.getIndexAttr(1);
  auto zero = builder.getIndexAttr(0);
  const int cDim = channelDim();

  assert(offsets.size() == 2);
  SmallVector<OpFoldResult> inputOffsets(getInputOperandRank(), zero);
  SmallVector<OpFoldResult> outputOffsets(getOutputOperandRank(), zero);
  inputOffsets[2] = outputOffsets[0] = offsets[0];
  inputOffsets[5] = outputOffsets[cDim] = offsets[1];

  SmallVector<OpFoldResult> inputStrides(getInputOperandRank(), one);
  SmallVector<OpFoldResult> outputStrides(getOutputOperandRank(), one);

  assert(sizes.size() == 2);
  auto inputShape = input().getType().cast<ShapedType>().getShape();
  auto outputShape = output().getType().cast<ShapedType>().getShape();
  SmallVector<OpFoldResult> inputSizes = getAsOpFoldResult(builder.getIndexArrayAttr(inputShape));
  SmallVector<OpFoldResult> outputSizes = getAsOpFoldResult(builder.getIndexArrayAttr(outputShape));
  inputSizes[2] = outputSizes[0] = sizes[0];
  inputSizes[5] = outputSizes[cDim] = sizes[1];

  SmallVector<Value> tiledOperands;
  tiledOperands.emplace_back(
      getSlice(builder, loc, input(), inputOffsets, inputSizes, inputStrides));
  tiledOperands.emplace_back(
      getSlice(builder, loc, output(), outputOffsets, outputSizes, outputStrides));

  SmallVector<Type, 4> resultTypes;
  if (hasTensorSemantics()) { resultTypes.push_back(tiledOperands[1].getType()); }

  Operation* tiledOp = mlir::clone(builder, getOperation(), resultTypes, tiledOperands);

  return TilingResult{{tiledOp}, SmallVector<Value>(tiledOp->getResults())};
}

LogicalResult WinogradOutputTransformOp::getResultTilePosition(
    OpBuilder& builder, unsigned resultNumber, ArrayRef<OpFoldResult> offsets,
    ArrayRef<OpFoldResult> sizes, SmallVector<OpFoldResult>& resultOffsets,
    SmallVector<OpFoldResult>& resultSizes) {
  if (resultNumber == 0) {
    auto resultShape = output().getType().cast<ShapedType>().getShape();
    resultSizes = getAsOpFoldResult(builder.getIndexArrayAttr(resultShape));
    resultOffsets = SmallVector<OpFoldResult>(getOutputOperandRank(), builder.getIndexAttr(0));
    const int cDim = channelDim();
    resultOffsets[0] = offsets[0];
    resultOffsets[cDim] = offsets[1];
    resultSizes[0] = sizes[0];
    resultSizes[cDim] = sizes[1];
    return success();
  }
  return failure();
}

LogicalResult WinogradOutputTransformOp::fold(FoldAdaptor, SmallVectorImpl<OpFoldResult>&) {
  return memref::foldMemRefCast(*this);
}

LogicalResult WinogradOutputTransformOp::reifyResultShapes(
    OpBuilder& b, ReifiedRankedShapedTypeDims& reifiedReturnShapes) {
  return cast<LinalgExtOp>(getOperation()).reifyResultShapes(b, reifiedReturnShapes);
}

static void getEffectsImpl(
    SmallVectorImpl<SideEffects::EffectInstance<MemoryEffects::Effect>>& effects,
    ValueRange inputOperands, ValueRange outputOperands) {
  for (Value value : inputOperands) {
    if (!llvm::isa<MemRefType>(value.getType())) { continue; }
    effects.emplace_back(MemoryEffects::Read::get(), value, SideEffects::DefaultResource::get());
  }
  for (Value value : outputOperands) {
    if (!llvm::isa<MemRefType>(value.getType())) { continue; }
    effects.emplace_back(MemoryEffects::Read::get(), value, SideEffects::DefaultResource::get());
    effects.emplace_back(MemoryEffects::Write::get(), value, SideEffects::DefaultResource::get());
  }
}

#define DEFINE_OP_GET_EFFECTS(OP_NAME)                                                \
  void OP_NAME::getEffects(                                                           \
      SmallVectorImpl<SideEffects::EffectInstance<MemoryEffects::Effect>>& effects) { \
    getEffectsImpl(effects, getDpsInputs(), getDpsInits());                           \
  }

DEFINE_OP_GET_EFFECTS(WinogradInputTransformOp)
DEFINE_OP_GET_EFFECTS(WinogradOutputTransformOp)

#define GET_OP_CLASSES
#include "LinalgExt/IR/LinalgExtOps.cpp.inc"  // IWYU pragma: keep