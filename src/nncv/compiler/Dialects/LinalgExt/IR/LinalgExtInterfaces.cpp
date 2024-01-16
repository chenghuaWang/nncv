#include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtInterface.hpp"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"

using namespace mlir;
using namespace mlir::nncv::linalg_ext;

LogicalResult nncv::linalg_ext::detail::verifyLinalgExtOpInterface(Operation* op) {
  LinalgExtOp linalgExtOp = cast<LinalgExtOp>(op);
  if (!isa<DestinationStyleOpInterface>(op)) {
    return linalgExtOp.emitOpError("expected operation that implements LinalgExtInterface to also "
                                   "implement DestinationStyleOpInterface");
  }
  return success();
}

#include "LinalgExt/IR/LinalgExtOpInterfaces.cpp.inc"  // IWYU pragma: export

template<typename Ty, typename DimOpTy>
static void getDimValues(OpBuilder& b, Location loc, Value v, Ty t,
                         SmallVector<OpFoldResult>& dimVals) {
  for (auto dim : llvm::enumerate(t.getShape())) {
    if (ShapedType::isDynamic(dim.value())) {
      dimVals.push_back(b.create<DimOpTy>(loc, v, dim.index()).getResult());
    } else {
      dimVals.push_back(b.getIndexAttr(dim.value()));
    }
  }
}

LogicalResult LinalgExtOp::reifyResultShapes(OpBuilder& b,
                                             ReifiedRankedShapedTypeDims& reifiedReturnShapes) {
  Operation* op = getOperation();
  for (auto output : cast<DestinationStyleOpInterface>(op).getDpsInits()) {
    SmallVector<OpFoldResult> dims;
    Type outputType = output.getType();
    if (auto rankedTensorType = outputType.dyn_cast<RankedTensorType>()) {
      getDimValues<RankedTensorType, tensor::DimOp>(b, op->getLoc(), output, rankedTensorType,
                                                    dims);
    } else if (auto memrefType = outputType.dyn_cast<MemRefType>()) {
      getDimValues<MemRefType, memref::DimOp>(b, op->getLoc(), output, memrefType, dims);
    } else if (!outputType.isIntOrIndexOrFloat()) {
      return op->emitOpError("invalid type for output operand, expected tensor, "
                             "memref or scalar type");
    }
    reifiedReturnShapes.emplace_back(std::move(dims));
  }
  return success();
}
