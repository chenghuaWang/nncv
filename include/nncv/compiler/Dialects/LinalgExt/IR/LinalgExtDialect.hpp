#ifndef NNCV_LINALG_EXT_DIALECT_HPP_
#define NNCV_LINALG_EXT_DIALECT_HPP_

#include "mlir/IR/Dialect.h"
#include "mlir/IR/OpDefinition.h"

#include "LinalgExt/IR/LinalgExtDialect.h.inc"  // IWYU pragma: keep

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/IR/Builders.h"
#include "llvm/ADT/TypeSwitch.h"

namespace mlir {
namespace nncv {
namespace linalg_ext {

template<typename T>
SmallVector<T> interchange(ArrayRef<T> elements, ArrayRef<int64_t> interchangeVector,
                           int offset = 0) {
  SmallVector<T> vec = llvm::to_vector(elements);
  for (auto en : llvm::enumerate(interchangeVector)) {
    vec[en.index() + offset] = elements[en.value() + offset];
  }
  return vec;
}
template<typename T>
SmallVector<T> undoInterchange(ArrayRef<T> elements, ArrayRef<int64_t> interchangeVector,
                               int offset = 0) {
  SmallVector<T> vec = llvm::to_vector(elements);
  for (auto en : llvm::enumerate(interchangeVector)) {
    vec[en.value() + offset] = elements[en.index() + offset];
  }
  return vec;
}

/// Returns the `interchangeVector` based on `dimsPos`.
SmallVector<int64_t> computeInterchangeFromDimPos(ArrayRef<int64_t> dimsPos, int64_t rank);

/// Converts a 2D float array to a constant value. The 2D array is stored as
/// a 1D row-major array in `val` and has shape `rows` x `cols`.
Value createValueFrom2DConstant(const float* val, int64_t rows, int64_t cols, Location loc,
                                RewriterBase& rewriter);

// Converts OpFoldResults to int64_t shape entries, unconditionally mapping all
// Value's to kDynamic, even if they are arith.constant values.
SmallVector<int64_t> asShapeWithAnyValueAsDynamic(ArrayRef<OpFoldResult> ofrs);

enum class Permutation {
  NCHW_TO_NHWC,
  NHWC_TO_NCHW,
  TTNHWC_TO_TTNCHW,
  TTNCHW_TO_TTNHWC,
};

// Permutes the elements of a SmallVector depending on the permutation specified
template<Permutation P, typename T>
static void permute(SmallVectorImpl<T>& vector) {
  switch (P) {
    case Permutation::NCHW_TO_NHWC:
      std::rotate(vector.begin() + 1, vector.begin() + 2, vector.end());
      break;
    case Permutation::NHWC_TO_NCHW:
      std::rotate(vector.rbegin(), vector.rbegin() + 1, vector.rend() - 1);
      break;
    case Permutation::TTNCHW_TO_TTNHWC:
      std::rotate(vector.begin() + 3, vector.begin() + 4, vector.end());
      break;
    case Permutation::TTNHWC_TO_TTNCHW:
      std::rotate(vector.rbegin(), vector.rbegin() + 1, vector.rend() - 3);
      break;
  }
}

inline Value getDimValue(OpBuilder& builder, Location loc, Value v, int64_t dim) {
  ShapedType type = v.getType().cast<ShapedType>();
  if (!type.isDynamicDim(dim)) {
    return builder.create<arith::ConstantIndexOp>(loc, type.getDimSize(dim));
  }
  return TypeSwitch<Type, Value>(v.getType())
      .Case<RankedTensorType>(
          [&](RankedTensorType t) -> Value { return builder.create<tensor::DimOp>(loc, v, dim); })
      .Case<MemRefType>(
          [&](MemRefType t) -> Value { return builder.create<memref::DimOp>(loc, v, dim); });
}

inline OpFoldResult getDim(OpBuilder& builder, Location loc, Value v, int64_t dim) {
  auto t = v.getType().cast<ShapedType>();
  if (t.isDynamicDim(dim)) { return getDimValue(builder, loc, v, dim); }
  return builder.getI64IntegerAttr(t.getDimSize(dim));
}

inline SmallVector<OpFoldResult> getDims(OpBuilder& builder, Location loc, Value shapedTypeValue) {
  return llvm::map_to_vector(
      llvm::seq<int64_t>(0, shapedTypeValue.getType().cast<ShapedType>().getRank()),
      [&](int64_t dim) { return getDim(builder, loc, shapedTypeValue, dim); });
}

inline SmallVector<int64_t> computeInterchangeFromDimPos(ArrayRef<int64_t> dimsPos, int64_t rank) {
  SmallVector<int64_t> interchangeVector;
  interchangeVector.reserve(dimsPos.size());
  // First map dims and their position. For example, dims_pos = [2, 0] will map
  // to:
  // [
  //  [ key: 2, value: 0]
  //  [ key: 0, value: 1]
  // ]
  // where key is the idx in dims_pos while value its position in dims_pos.
  DenseMap<int64_t, int64_t> dimsAndPosMapping;
  for (int64_t dimsIdx = 0, end = dimsPos.size(); dimsIdx < end; dimsIdx++)
    dimsAndPosMapping[dimsPos[dimsIdx]] = dimsIdx;

  // Scan the position in order and insert the value in the map
  // to compute the interchange vector.
  for (int64_t dimsIdx = 0; dimsIdx < rank; dimsIdx++) {
    if (dimsAndPosMapping.count(dimsIdx)) interchangeVector.push_back(dimsAndPosMapping[dimsIdx]);
  }
  return interchangeVector;
}

inline Value createValueFrom2DConstant(const float* val, int64_t rows, int64_t cols, Location loc,
                                       RewriterBase& rewriter) {
  ArrayRef<float> vector(val, rows * cols);
  SmallVector<int64_t> shape{rows, cols};
  return rewriter.create<arith::ConstantOp>(
      loc, DenseFPElementsAttr::get(RankedTensorType::get(shape, rewriter.getF32Type()), vector));
}

inline SmallVector<int64_t> asShapeWithAnyValueAsDynamic(ArrayRef<OpFoldResult> ofrs) {
  SmallVector<int64_t> result;
  for (auto o : ofrs) {
    // Have to do this first, as getConstantIntValue special-cases constants.
    if (o.dyn_cast<Value>())
      result.push_back(ShapedType::kDynamic);
    else
      result.push_back(getConstantIntValue(o).value_or(ShapedType::kDynamic));
  }
  return result;
}

}  // namespace linalg_ext
}  // namespace nncv
}  // namespace mlir

#endif  // NNCV_LINALG_EXT_DIALECT_HPP_