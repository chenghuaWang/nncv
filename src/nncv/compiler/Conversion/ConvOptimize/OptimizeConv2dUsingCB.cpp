#include "nncv/compiler/Conversion/ConvOptimize/OptimizeConv2dUsingCB.hpp"

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
#define GEN_PASS_DEF_OPTIMIZECONV2DUSINGCB
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

// utilities
Value zeroCond(OpBuilder& builder, Location loc, Type elemType, Value value, Value zeroElem) {
  Value cond;
  auto bitWidth = elemType.getIntOrFloatBitWidth();
  if (elemType.isF32() || elemType.isF64()) {
    cond = builder.create<arith::CmpFOp>(loc, arith::CmpFPredicate::ONE, value, zeroElem);
  } else if (elemType.isInteger(bitWidth)) {
    cond = builder.create<arith::CmpIOp>(loc, arith::CmpIPredicate::ne, value, zeroElem);
  }
  return cond;
}

Value indexToF32(OpBuilder& builder, Location loc, Value val) {
  Value interm1 = builder.create<arith::IndexCastOp>(loc, builder.getI32Type(), val);
  return builder.create<arith::SIToFPOp>(loc, builder.getF32Type(), interm1);
}

//===----------------------------------------------------------------------===//
// Convolution optimization without Channel
// Ref:
// https://github.com/buddy-compiler/buddy-mlir/blob/main/midend/lib/Conversion/ConvVectorization/CBConvVectorization.cpp
//===----------------------------------------------------------------------===//
void _populateCBSplitingPatternWoChannel(Operation* op, int64_t stride,
                                         ConversionPatternRewriter& rewriter) {
  auto mlirLoc = op->getLoc();
  auto mlirCtx = op->getContext();

  // Element type.
  FloatType f32 = mlir::FloatType::getF32(mlirCtx);

  // Get i1 as the element type for mask vector.
  IntegerType i1 = IntegerType::get(mlirCtx, 1);

  // Get the vector type we need
  VectorType vectorTy32 = mlir::VectorType::get({stride}, f32);
  VectorType vectorMaskTy = VectorType::get({stride}, i1);

  // Create constant index.
  Value c0 = rewriter.create<arith::ConstantIndexOp>(mlirLoc, 0);
  Value c1 = rewriter.create<arith::ConstantIndexOp>(mlirLoc, 1);
  Value cStride = rewriter.create<arith::ConstantIndexOp>(mlirLoc, stride);
  Value f0 = rewriter.create<arith::ConstantFloatOp>(
      mlirLoc, APFloat::getZero(f32.getFloatSemantics()), f32);

  // Create pass through vector.
  Value passThroughVec = rewriter.create<vector::SplatOp>(mlirLoc, vectorTy32, f0);

  // Get input, kernel and output.
  Value input = op->getOperand(0);
  Value kernel = op->getOperand(1);
  Value output = op->getOperand(2);

  // Create DimOp.
  Value kernelRow = rewriter.create<memref::DimOp>(mlirLoc, kernel, c0);
  Value kernelCol = rewriter.create<memref::DimOp>(mlirLoc, kernel, c1);
  Value outputRow = rewriter.create<memref::DimOp>(mlirLoc, output, c0);
  Value outputCol = rewriter.create<memref::DimOp>(mlirLoc, output, c1);

  // Size of strip mining.
  AffineExpr d0;
  mlir::bindDims(mlirCtx, d0);
  AffineMap stripMap = AffineMap::get(1, 0, {d0.ceilDiv(stride)}, mlirCtx);
  SmallVector<Value, 8> lowerBounds(3, c0);
  SmallVector<Value, 8> uperBounds{outputRow, kernelRow, kernelCol};
  SmallVector<int64_t, 8> steps(3, /*Value=*/1);

  affine::buildAffineLoopNest(
      rewriter, mlirLoc, lowerBounds, uperBounds, steps,
      [&](OpBuilder& builder, Location loc, ValueRange ivs) {
        // Create strip mining loop.
        builder.create<affine::AffineForOp>(
            loc, ValueRange{c0}, builder.getDimIdentityMap(), ValueRange{outputCol}, stripMap,
            /*Step=*/1, std::nullopt,
            [&](OpBuilder& nestedBuilder, Location nestedLoc, Value iv, ValueRange itrArgs) {
              // Vectorize the kernel.
              // Broadcast element of the kernel.
              Value kernelValue =
                  builder.create<memref::LoadOp>(loc, kernel, ValueRange{ivs[1], ivs[2]});
              Value kernelNonZeroCond =
                  zeroCond(builder, loc, f32, kernelValue, indexToF32(builder, loc, c0));
              builder.create<scf::IfOp>(
                  loc, kernelNonZeroCond, [&](OpBuilder& builder, Location loc) {
                    Value kernelVector =
                        builder.create<vector::BroadcastOp>(loc, vectorTy32, kernelValue);
                    // Load input vector from memref.
                    AffineExpr m, n, k, j;
                    bindDims(mlirCtx, m, n, k, j);
                    AffineMap inputVectorMap = AffineMap::get(
                        /*dimCount=*/4, /*symbolCount=*/0, {m + n, k + j * stride}, mlirCtx);
                    // Calculate the tail.
                    Value currCol = nestedBuilder.create<arith::MulIOp>(loc, iv, cStride);
                    Value tail = nestedBuilder.create<arith::SubIOp>(loc, outputCol, currCol);
                    Value tailCond = rewriter.create<arith::CmpIOp>(loc, arith::CmpIPredicate::sge,
                                                                    tail, cStride);
                    // If the current column does not reach the tail.
                    builder.create<scf::IfOp>(
                        loc, tailCond,
                        [&](OpBuilder& builder, Location loc) {
                          Value inputVector = nestedBuilder.create<affine::AffineVectorLoadOp>(
                              loc, vectorTy32, input, inputVectorMap,
                              ValueRange{ivs[0], ivs[1], ivs[2], iv});
                          // Define AffineMap.
                          // The `outputVector` and `resultVector` share the
                          // same AffineMap.
                          AffineExpr x, y;
                          bindDims(mlirCtx, x, y);
                          AffineMap outputVectorMap = AffineMap::get(
                              /*dimCount=*/2, /*symbolCount=*/0, {x, y * stride}, mlirCtx);
                          Value outputVector = nestedBuilder.create<affine::AffineVectorLoadOp>(
                              loc, vectorTy32, output, outputVectorMap, ValueRange{ivs[0], iv});
                          // FMA = Fused Multiply + Add
                          Value resultVector = nestedBuilder.create<vector::FMAOp>(
                              loc, inputVector, kernelVector, outputVector);
                          nestedBuilder.create<affine::AffineVectorStoreOp>(
                              loc, resultVector, output, outputVectorMap, ValueRange{ivs[0], iv});
                          builder.create<scf::YieldOp>(loc);
                        },
                        // The else branch (the current column reaches the
                        // tail).
                        [&](OpBuilder& builder, Location loc) {
                          // Create mask according to the tail.
                          Value tailMask =
                              builder.create<vector::CreateMaskOp>(loc, vectorMaskTy, tail);
                          // Calculate the index of the input and output.
                          Value inputRow = nestedBuilder.create<arith::AddIOp>(loc, ivs[0], ivs[1]);
                          Value outputCol = nestedBuilder.create<arith::MulIOp>(loc, iv, cStride);
                          Value inputCol =
                              nestedBuilder.create<arith::AddIOp>(loc, ivs[2], outputCol);
                          // Masked load input and output.
                          Value maskedInputVec = builder.create<vector::MaskedLoadOp>(
                              loc, vectorTy32, input, ValueRange{inputRow, inputCol}, tailMask,
                              passThroughVec);
                          Value maskedOutputVec = builder.create<vector::MaskedLoadOp>(
                              loc, vectorTy32, output, ValueRange{ivs[0], outputCol}, tailMask,
                              passThroughVec);
                          // FMA.
                          Value resultVec = builder.create<vector::FMAOp>(
                              loc, maskedInputVec, kernelVector, maskedOutputVec);
                          // Masked store the result to output.
                          builder.create<vector::MaskedStoreOp>(
                              loc, output, ValueRange{ivs[0], outputCol}, tailMask, resultVec);
                          builder.create<scf::YieldOp>(loc);
                        });
                    builder.create<scf::YieldOp>(loc);
                  });
              nestedBuilder.create<affine::AffineYieldOp>(nestedLoc);
            });
      });
  rewriter.eraseOp(op);
  return;
}

void _populateCBTilingPatternWoChannel(Operation* op, llvm::ArrayRef<int64_t> tileSizes,
                                       ConversionPatternRewriter& rewriter) {
  auto mlirLoc = op->getLoc();
  auto mlirCtx = op->getContext();

  FloatType f32 = mlir::FloatType::getF32(mlirCtx);

  VectorType vectorTy1 = mlir::VectorType::get({1}, f32);

  VectorType vectorTy32 = mlir::VectorType::get(tileSizes, f32);

  Value c0 = rewriter.create<arith::ConstantIndexOp>(mlirLoc, 0);
  Value c1 = rewriter.create<arith::ConstantIndexOp>(mlirLoc, 1);

  Value input = op->getOperand(0);
  Value kernel = op->getOperand(1);
  Value output = op->getOperand(2);

  Value kernelRow = rewriter.create<memref::DimOp>(mlirLoc, kernel, c0);
  Value kernelCol = rewriter.create<memref::DimOp>(mlirLoc, kernel, c1);

  Value f0 = rewriter.create<arith::ConstantFloatOp>(
      mlirLoc, APFloat::getZero(f32.getFloatSemantics()), f32);
  // Size of strip mining.
  AffineExpr d0;
  bindDims(mlirCtx, d0);
  SmallVector<Value, 8> lowerBounds(2, c0);
  SmallVector<Value, 8> uperBounds{kernelRow, kernelCol};
  SmallVector<int64_t, 8> steps(2, /*Value=*/1);
  affine::buildAffineLoopNest(
      rewriter, mlirLoc, lowerBounds, uperBounds, steps,
      [&](OpBuilder& builder, Location loc, ValueRange ivs) {
        // Vectorize the kernel.
        // Broadcast element of the kernel into 2D vector.
        Value kernelValue = builder.create<affine::AffineVectorLoadOp>(loc, vectorTy1, kernel,
                                                                       ValueRange{ivs[0], ivs[1]});
        Value kernelVector = builder.create<vector::BroadcastOp>(loc, vectorTy32, kernelValue);
        // Load input and output as 2D vector.
        Value inputVector = builder.create<vector::TransferReadOp>(loc, vectorTy32, input,
                                                                   ValueRange{ivs[0], ivs[1]}, f0);
        Value outputVector =
            builder.create<vector::TransferReadOp>(loc, vectorTy32, output, ValueRange{c0, c0}, f0);
        // FMA.
        Value resultVector =
            builder.create<vector::FMAOp>(loc, inputVector, kernelVector, outputVector);
        // 2D vector write back to memory.
        builder.create<vector::TransferWriteOp>(loc, resultVector, output, ValueRange{c0, c0});
      });
  // Remove the origin convolution operation.
  rewriter.eraseOp(op);
  return;
}

class CBForConv2DWoChannelPattern : public OpConversionPattern<linalg::Conv2DOp> {
 public:
  using OpConversionPattern<linalg::Conv2DOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(linalg::Conv2DOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    if (m_TileSizes.empty()) {
      _populateCBSplitingPatternWoChannel(op, m_Stride, rewriter);
    } else {
      _populateCBTilingPatternWoChannel(op, m_TileSizes, rewriter);
    }
    return success();
  }

 private:
  int64_t m_Stride;
  ArrayRef<int64_t> m_TileSizes;
};

//===----------------------------------------------------------------------===//
// Convolution optimization with Channel:
// TODO
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Convolution optimization Pass
//===----------------------------------------------------------------------===//
class OptimizeConv2dUsingCBPass
    : public impl::OptimizeConv2dUsingCBBase<OptimizeConv2dUsingCBPass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<linalg::LinalgDialect, scf::SCFDialect, affine::AffineDialect,
                    vector::VectorDialect, func::FuncDialect>();
  }

  void runOnOperation() override {
    MLIRContext* context = &getContext();
    ModuleOp module = getOperation();

    RewritePatternSet patterns(context);
    patterns.add<CBForConv2DWoChannelPattern>(context);

    ConversionTarget target(*context);
    target.addLegalDialect<arith::ArithDialect, affine::AffineDialect, scf::SCFDialect,
                           func::FuncDialect, memref::MemRefDialect, vector::VectorDialect,
                           math::MathDialect>();
    target.addLegalOp<ModuleOp, func::FuncOp, func::ReturnOp>();
    target.addLegalOp<linalg::FillOp>();

    if (failed(applyPartialConversion(module, target, std::move(patterns)))) {
      signalPassFailure();
    }
  }
};

}  // namespace
std::unique_ptr<mlir::Pass> createOptimizeConv2dUsingCBPass() {
  return std::make_unique<OptimizeConv2dUsingCBPass>();
}
}  // namespace mlir::nncv