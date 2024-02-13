// referenced from buddy.
// optimizing linalg.conv2d_nchw_fchw manually
// other format linalg.conv2d will be lowered using mlir built in pipeline.

#include "nncv/compiler/Conversion/ConvOptimize/ConvertOptimizedConv2dToAffine.hpp"

#include "mlir/IR/IntegerSet.h"
#include "nncv/compiler/Utils/PlatformCtx.hpp"

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
#define GEN_PASS_DEF_CONVERTOPTIMIZEDCONV2DTOAFFINE
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class ConvOptimizePattern : public mlir::ConversionPattern {
 public:
  explicit ConvOptimizePattern(MLIRContext* context)
      : ConversionPattern(linalg::Conv2DNchwFchwOp::getOperationName(), 1, context) {}

  LogicalResult matchAndRewrite(Operation* op, ArrayRef<Value> operands,
                                ConversionPatternRewriter& rewriter) const override {
    if (!mlir::cast<mlir::linalg::Conv2DNchwFchwOp>(op)) { return mlir::LogicalResult::failure(); }

    // calculate
    int64_t vecSize = ::nncv::compiler::utils::PlatformCtx::getInstance().CpuHasAVX2 ? 8 : 4;
    int64_t kernelM = ::nncv::compiler::utils::PlatformCtx::getInstance().CpuHasAVX2 ? 8 : 4;
    int64_t kernelN = 4;

    // get location
    auto loc = op->getLoc();

    // init constant
    const Value c0 = rewriter.create<arith::ConstantOp>(loc, rewriter.getIndexAttr(0));
    const Value cf0 = rewriter.create<arith::ConstantOp>(loc, rewriter.getF32FloatAttr(0.));

    const AffineExpr d0 = rewriter.getAffineDimExpr(0);
    const AffineExpr d1 = rewriter.getAffineDimExpr(1);
    const AffineExpr s0 = rewriter.getAffineSymbolExpr(0);

    Value input = op->getOperand(0);
    Value filter = op->getOperand(1);
    Value output = op->getOperand(2);

    ShapedType inputTy = input.getType().cast<ShapedType>();
    Type elemTy = inputTy.getElementType();
    VectorType vecTy = VectorType::get(vecSize, elemTy);

    // Dims
    Value outN = rewriter.create<memref::DimOp>(loc, output, 0);
    Value outC = rewriter.create<memref::DimOp>(loc, output, 1);
    Value outH = rewriter.create<memref::DimOp>(loc, output, 2);
    Value outW = rewriter.create<memref::DimOp>(loc, output, 3);
    Value inC = rewriter.create<memref::DimOp>(loc, input, 1);
    Value kernelH = rewriter.create<memref::DimOp>(loc, filter, 2);
    Value kernelW = rewriter.create<memref::DimOp>(loc, filter, 3);

    // memref<1xvector<vecsize x elemTy>>
    MemRefType bufferTy = MemRefType::get(1, vecTy);
    Value buffer = rewriter.create<memref::AllocOp>(loc, bufferTy);

    // clang-format off
        // Step 1: Create outer most loops.
    affine::buildAffineLoopNest(rewriter, loc, c0, outN, 1, [&](OpBuilder &, Location loc, ValueRange ivRange) {
      Value ivA = ivRange.front();
      affine::buildAffineLoopNest(rewriter, loc, c0, outC, 1, [&](OpBuilder &, Location loc, ValueRange ivRange) {
        Value ivB = ivRange.front();
        affine::buildAffineLoopNest(rewriter, loc, c0, outW, 1, [&](OpBuilder &, Location loc, ValueRange ivRange) {
          Value ivD = ivRange.front();
          affine::buildAffineLoopNest(rewriter, loc, c0, outH, 1, [&](OpBuilder &builder, Location loc, ValueRange ivRange) {
            Value ivC = ivRange.front();
            Value t = builder.create<vector::SplatOp>(loc, vecTy, cf0);
            builder.create<memref::StoreOp>(loc, t, buffer, c0);
            affine::buildAffineLoopNest(rewriter, loc, c0, inC, 1, [&](OpBuilder &builder, Location loc, ValueRange ivRange) {
              Value ivE = ivRange.front();

              Value fixed = builder.create<affine::AffineApplyOp>(loc, AffineMap::get(1, 0, d0.ceilDiv(kernelM) * kernelM), ValueRange{kernelH});

              affine::buildAffineLoopNest(rewriter, loc, c0, fixed, kernelM, [&](OpBuilder &builder, Location loc, ValueRange ivRange) {
                Value ivF = ivRange.front();
                affine::buildAffineLoopNest(rewriter, loc, c0, kernelW, kernelN * vecSize, [&](OpBuilder &builder, Location loc, ValueRange ivRange) {
                  Value ivG = ivRange.front();

                  SmallVector<Value> iList;
                  SmallVector<Value> fList;
                  for (int i = 0; i < kernelM; ++i) {
                    Value rowInput = builder.create<affine::AffineApplyOp>(loc, AffineMap::get(2, 0, d0 + i + d1), ValueRange{ivC, ivF});
                    Value rowFilter = builder.create<affine::AffineApplyOp>(loc, AffineMap::get(1, 0, d0 + i), ivF);
                    for (int j = 0; j < kernelN; ++j) {
                      Value columnInput = builder.create<affine::AffineApplyOp>(loc, AffineMap::get(2, 0, d0 + d1 + j * vecSize), ValueRange{ivD, ivG});
                      Value columnFilter = builder.create<affine::AffineApplyOp>(loc, AffineMap::get(1, 0, d0 + j * vecSize), ivG);

                      Value i = builder.create<vector::TransferReadOp>(loc, vecTy, input, ValueRange{ivA, ivE, rowInput, columnInput});

                      auto protectedF =
                          builder.create<affine::AffineIfOp>(loc, vecTy, IntegerSet::get(1, 1, {s0 - 1 - d0}, {false}), ValueRange{rowFilter, kernelH}, true);

                      // if row in range, read normally.
                      auto thenBuilder = protectedF.getThenBodyBuilder();
                      Value normalReadVec = thenBuilder.create<vector::TransferReadOp>(loc, vecTy, filter, ValueRange{ivB, ivE, rowFilter, columnFilter});
                      thenBuilder.create<affine::AffineYieldOp>(loc, normalReadVec);

                      // if row out of range, give back a empty vector.
                      auto elseBuilder = protectedF.getElseBodyBuilder();
                      Value emptyVec = elseBuilder.create<vector::SplatOp>(loc, vecTy, cf0);
                      elseBuilder.create<affine::AffineYieldOp>(loc, emptyVec);

                      iList.push_back(i);
                      fList.push_back(protectedF->getOpResult(0));
                    }
                  }
                  Value lastResult = builder.create<memref::LoadOp>(loc, buffer, c0);
                  for (int i = 0; i < kernelM; ++i) {
                    for (int j = 0; j < kernelN; ++j) {
                      lastResult = builder.create<vector::FMAOp>(loc, vecTy, iList[i * kernelN + j], fList[i * kernelN + j], lastResult);
                    }
                  }
                  builder.create<memref::StoreOp>(loc, lastResult, buffer, c0);
                });
              });
            });

            Value reduceVec = builder.create<memref::LoadOp>(loc, buffer, c0);
            Value reducedRes = builder.create<vector::ReductionOp>(loc, vector::CombiningKind::ADD, reduceVec);
            Value bias = builder.create<memref::LoadOp>(loc, output, ValueRange{ivA, ivB, ivC, ivD});
            Value addRes = builder.create<arith::AddFOp>(loc, bias, reducedRes);
            builder.create<memref::StoreOp>(loc, addRes, output, ValueRange{ivA, ivB, ivC, ivD});
          });
        });
      });
    });
    // clang-format on

    rewriter.create<memref::DeallocOp>(loc, buffer);
    rewriter.eraseOp(op);
    return mlir::LogicalResult::success();
  }
};

class PoolingSumOptimizePattern : public mlir::ConversionPattern {
 public:
  explicit PoolingSumOptimizePattern(MLIRContext* context)
      : ConversionPattern(linalg::PoolingNchwSumOp::getOperationName(), 1, context) {}
  LogicalResult matchAndRewrite(Operation* op, ArrayRef<Value> operands,
                                ConversionPatternRewriter& rewriter) const override {
    if (!mlir::isa<mlir::linalg::PoolingNchwSumOp>(op)) { return mlir::LogicalResult::failure(); }

    // TODO

    return mlir::LogicalResult::success();
  }
};

class PoolingMaxOptimizePattern : public mlir::ConversionPattern {
 public:
  explicit PoolingMaxOptimizePattern(MLIRContext* context)
      : ConversionPattern(linalg::PoolingNchwMaxOp::getOperationName(), 1, context) {}

  LogicalResult matchAndRewrite(Operation* op, ArrayRef<Value> operands,
                                ConversionPatternRewriter& rewriter) const override {
    if (!mlir::isa<mlir::linalg::PoolingNchwMaxOp>(op)) { return mlir::LogicalResult::failure(); }

    // TODO

    return mlir::LogicalResult::success();
  }
};

class OptimizedConv2dToAffinePass
    : public impl::ConvertOptimizedConv2dToAffineBase<OptimizedConv2dToAffinePass> {
 public:
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(OptimizedConv2dToAffinePass)

  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<linalg::LinalgDialect, scf::SCFDialect, affine::AffineDialect,
                    vector::VectorDialect, func::FuncDialect>();
  }

  void runOnOperation() override {
    MLIRContext* context = &getContext();
    ModuleOp module = getOperation();

    RewritePatternSet patterns(context);
    patterns.add<ConvOptimizePattern, PoolingSumOptimizePattern, PoolingMaxOptimizePattern>(
        context);

    ConversionTarget target(*context);
    target.addLegalDialect<arith::ArithDialect, affine::AffineDialect, scf::SCFDialect,
                           func::FuncDialect, memref::MemRefDialect, vector::VectorDialect,
                           math::MathDialect, linalg::LinalgDialect, tensor::TensorDialect>();
    target.addLegalOp<ModuleOp, func::FuncOp, func::ReturnOp>();
    target.addIllegalOp<linalg::Conv2DNchwFchwOp>();

    if (failed(applyPartialConversion(module, target, std::move(patterns)))) {
      signalPassFailure();
    }
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createConvertOptimizedConv2dToAffinePass() {
  return std::make_unique<OptimizedConv2dToAffinePass>();
}
}  // namespace mlir::nncv