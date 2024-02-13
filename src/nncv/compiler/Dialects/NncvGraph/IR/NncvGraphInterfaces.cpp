#include "nncv/compiler/Dialects/NncvGraph/IR/NncvGraphInterfaces.hpp"

#include "llvm/ADT/BitVector.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/IR/Attributes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Diagnostics.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/Dominance.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/IR/TypeSupport.h"
#include "mlir/IR/TypeUtilities.h"
#include "mlir/Interfaces/CastInterfaces.h"
#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Parser/Parser.h"

namespace mlir::nncv::graph {

static SmallVector<Value> buildShape(Location loc, ShapedType type, ValueRange dynamicDims,
                                     OpBuilder& builder) {
  SmallVector<Value> dims;
  dims.reserve(type.getRank());
  unsigned dynamicIdx = 0;
  for (unsigned i = 0; i < type.getRank(); ++i) {
    int64_t dim = type.getDimSize(i);
    if (ShapedType::isDynamic(dim)) {
      dims.push_back(dynamicDims[dynamicIdx++]);
    } else {
      dims.push_back(builder.create<arith::ConstantIndexOp>(loc, dim));
    }
  }
  return dims;
}

SmallVector<Value> buildOperandShape(ShapeAwareOpInterface op, unsigned operandIdx,
                                     OpBuilder& builder) {
  auto operand = op->getOperand(operandIdx);
  auto type = llvm::cast<ShapedType>(operand.getType());
  auto dynamicDims = op.getOperandDynamicDims(operandIdx);
  return buildShape(op.getLoc(), type, dynamicDims, builder);
}

SmallVector<Value> buildResultShape(ShapeAwareOpInterface op, unsigned resultIdx,
                                    OpBuilder& builder) {
  auto result = op->getResult(resultIdx);
  auto type = llvm::cast<ShapedType>(result.getType());
  auto dynamicDims = op.getResultDynamicDims(resultIdx);
  return buildShape(op.getLoc(), type, dynamicDims, builder);
}

}  // namespace mlir::nncv::graph