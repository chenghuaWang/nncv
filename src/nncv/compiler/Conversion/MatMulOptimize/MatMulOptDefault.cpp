#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptDefault.hpp"
#include "mlir/IR/BuiltinTypeInterfaces.h"
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
#define GEN_PASS_DEF_MATMULOPTIMIZATION_DEFAULT
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {
namespace matmul_optimize {

namespace {
//===----------------------------------------------------------------------===//
// MatMul optimization(default method)
//
// Using vectorization to accelerate mat mul speed. Before create this pass, you
// should first init the `kernel` size and `vector` capability in PlatformCtx struct.
//
// !!! This optimization is performed on shaped tensor. You should infer the tensor
// shape before doing this transform.
//
// The Tiling kernel size is M x N
//===----------------------------------------------------------------------===//
class MatMulOptimizePattern : public ConversionPattern {
 public:
  explicit MatMulOptimizePattern(MLIRContext* context, int64_t vecSizeParam, int64_t kernelMParam,
                                 int64_t kernelNParam)
      : ConversionPattern(linalg::MatmulOp::getOperationName(), 1, context) {
    m_VecSize = vecSizeParam;
    m_KernelM = kernelMParam;
    m_KernelN = kernelNParam;
  }

  LogicalResult matchAndRewrite(Operation* op, ArrayRef<Value> /*operands*/,
                                ConversionPatternRewriter& rewriter) const override {
    if (!mlir::cast<linalg::MatmulOp>(op)) { return mlir::failure(); }

    // get the location of a mlir op.
    auto mlirLocation = op->getLoc();

    // get all operand. dst = lhs @ rhs.
    auto lhs = op->getOperand(0);
    auto rhs = op->getOperand(1);
    auto dst = op->getOperand(2);

    // get the shape type of all operand.
    auto lhsShapeType = lhs.getType().cast<mlir::ShapedType>();

    /// Prepare dims and symbols for Affine Tilling.
    const Value c0 = rewriter.create<arith::ConstantOp>(mlirLocation, rewriter.getIndexAttr(0));
    const Value c1 = rewriter.create<arith::ConstantOp>(mlirLocation, rewriter.getIndexAttr(1));

    const AffineExpr s0 = rewriter.getAffineSymbolExpr(0);
    const AffineExpr s1 = rewriter.getAffineSymbolExpr(1);
    const AffineExpr d0 = rewriter.getAffineDimExpr(0);
    const AffineExpr d1 = rewriter.getAffineDimExpr(1);

    const AffineMap mapBroadcast = AffineMap::get(2, 0, rewriter.getAffineConstantExpr(0));
    const VectorType vectorType = VectorType::get(16, lhsShapeType.getElementType());

    // Configs
    int64_t kNLen = m_VecSize * m_KernelN;

    // Dims.
    // lhs: a x b; rhs: b x c; dst: a x c;
    // M = a
    // N = c
    // K = b
    Value M = rewriter.create<memref::DimOp>(mlirLocation, lhs, 0);
    Value N = rewriter.create<memref::DimOp>(mlirLocation, rhs, 1);
    Value K = rewriter.create<memref::DimOp>(mlirLocation, lhs, 1);

    // do Affine algorithm
    // out-most loop from c0(0) to C. Step is kernelN * vecSize.
    affine::buildAffineLoopNest(
        rewriter, mlirLocation, {c0}, {N}, kNLen,
        [&](OpBuilder& builder, Location loc, ValueRange ivRange) {
          auto affine_index_J = ivRange.front();
          // 2nd loop from 0 to a, Step is KernelM.
          affine::buildAffineLoopNest(
              builder, loc, {c0}, {M}, m_KernelM,
              [&](OpBuilder& builder, Location loc, ValueRange ivRange) {
                Value affine_index_I = ivRange.front();

                SmallVector<memref::SubViewOp> lhs_ptrs;
                SmallVector<memref::SubViewOp> dst_ptrs;

                for (int i = 0; i < m_KernelM; ++i) {
                  Value fixedIV = affine_index_I;
                  if (i != 0) {
                    fixedIV = builder.create<affine::AffineMinOp>(
                        loc, AffineMap::get(1, 1, {d0 + i, s0 - 1}, builder.getContext()),
                        SmallVector<Value>{affine_index_I, M});
                  }
                  MemRefType resTy =
                      MemRefType::get(lhsShapeType.getShape(), lhsShapeType.getElementType(),
                                      AffineMap::get(2, 2, d0 * s1 + s0 + d1));
                  auto __lhs_ptr = builder.create<memref::SubViewOp>(
                      loc, resTy, lhs, SmallVector<OpFoldResult>{fixedIV, c0},
                      SmallVector<OpFoldResult>{c1, K}, SmallVector<OpFoldResult>{c1, c1});
                  lhs_ptrs.push_back(__lhs_ptr);
                }

                for (int i = 0; i < m_KernelM; ++i) {
                  Value fixedIV = builder.create<affine::AffineMinOp>(
                      loc, AffineMap::get(1, 1, {d0 + i, s0 - 1}, builder.getContext()),
                      SmallVector<Value>{affine_index_I, M});
                  MemRefType resTy =
                      MemRefType::get(lhsShapeType.getShape(), lhsShapeType.getElementType(),
                                      AffineMap::get(2, 2, d0 * s1 + s0 + d1));
                  auto _dst_ptr = builder.create<memref::SubViewOp>(
                      loc, resTy, dst, SmallVector<OpFoldResult>{fixedIV, c0},
                      SmallVector<OpFoldResult>{c1, N}, SmallVector<OpFoldResult>{c1, c1});
                  dst_ptrs.push_back(_dst_ptr);
                }
                // 3rd loop from 0 to b, Step is 1.
                affine::buildAffineLoopNest(
                    builder, loc, {c0}, {K}, 1,
                    [&](OpBuilder& builder, Location loc, ValueRange ivRange) {
                      Value affine_index_k = ivRange.front();
                      SmallVector<Value> lhsS;
                      SmallVector<Value> rhsS;
                      SmallVector<Value> dstS;

                      for (int i = 0; i < m_KernelM; ++i) {
                        Value a = builder.create<vector::TransferReadOp>(
                            loc, vectorType, lhs_ptrs[i], ValueRange{c0, affine_index_k},
                            mapBroadcast);
                        lhsS.push_back(a);
                      }

                      for (int i = 0; i < m_KernelM; ++i) {
                        Value c = dst_ptrs[i];
                        for (int j = 0; j < m_KernelN; ++j) {
                          Value fixedIV = builder.create<affine::AffineApplyOp>(
                              loc, AffineMap::get(1, 0, d0 + j * m_VecSize), affine_index_J);
                          Value d = builder.create<vector::TransferReadOp>(loc, vectorType, c,
                                                                           ValueRange{c0, fixedIV});
                          dstS.push_back(d);
                        }
                      }

                      for (int i = 0; i < m_KernelN; ++i) {
                        Value fixedIV = affine_index_J;
                        if (i != 0) {
                          fixedIV = builder.create<affine::AffineApplyOp>(
                              loc, AffineMap::get(1, 0, d0 + i * m_VecSize), affine_index_J);
                        }
                        Value b = builder.create<vector::TransferReadOp>(
                            loc, vectorType, rhs, ValueRange{affine_index_k, fixedIV});
                        rhsS.push_back(b);
                      }

                      for (int i = 0; i < m_KernelM; ++i) {
                        for (int j = 0; j < m_KernelN; ++j) {
                          rhsS[i * m_KernelN + j] = builder.create<vector::FMAOp>(
                              loc, vectorType, lhsS[i], rhsS[j], dstS[i * m_KernelN + j]);
                        }
                      }

                      for (int i = 0; i < m_KernelM; ++i) {
                        for (int j = 0; j < m_KernelN; ++j) {
                          Value fixedIV = builder.create<affine::AffineApplyOp>(
                              loc, AffineMap::get(1, 0, d0 + j * m_VecSize), affine_index_J);
                          builder.create<vector::TransferWriteOp>(
                              loc, rhsS[i * m_KernelN + j], dst_ptrs[i], ValueRange{c0, fixedIV});
                        }
                      }
                    });
              });
        });

    rewriter.eraseOp(op);
    return mlir::success();
  }

 private:
  int64_t m_VecSize;
  int64_t m_KernelM;
  int64_t m_KernelN;
};

class MatMulOptimizationDefaultPass
    : public impl::MatMulOptimization_DefaultBase<MatMulOptimizationDefaultPass> {
 public:
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(MatMulOptimizationDefaultPass)

  explicit MatMulOptimizationDefaultPass(int64_t vecSizeParam, int64_t kernelMParam,
                                         int64_t kernelNParam) {
    m_VecSize = vecSizeParam;
    m_KernelM = kernelMParam;
    m_KernelN = kernelNParam;
  }

  void runOnOperation() override {
    MLIRContext* context = &getContext();
    ModuleOp module = getOperation();

    ConversionTarget target(*context);
    target.addLegalDialect<arith::ArithDialect, affine::AffineDialect, scf::SCFDialect,
                           memref::MemRefDialect, vector::VectorDialect>();
    target.addLegalOp<ModuleOp, func::FuncOp, func::ReturnOp>();
    target.addLegalOp<linalg::FillOp>();

    RewritePatternSet patterns(context);
    patterns.add<MatMulOptimizePattern>(context, m_VecSize, m_KernelM, m_KernelN);

    if (failed(applyPartialConversion(module, target, std::move(patterns)))) signalPassFailure();
  }

  void getDependentDialects(DialectRegistry& registry) const override {
    registry.insert<linalg::LinalgDialect, scf::SCFDialect, affine::AffineDialect,
                    vector::VectorDialect>();
  }

 private:
  int64_t m_VecSize;
  int64_t m_KernelM;
  int64_t m_KernelN;
};

}  // namespace

std::unique_ptr<mlir::Pass> createMatMulOptimizationDefaultPass() {
  return std::make_unique<MatMulOptimizationDefaultPass>(
      ::nncv::compiler::utils::PlatformCtx::getInstance().MatMul_VecSize,
      ::nncv::compiler::utils::PlatformCtx::getInstance().MatMul_Kernel_M,
      ::nncv::compiler::utils::PlatformCtx::getInstance().MatMul_Kernel_N);
}
}  // namespace matmul_optimize
}  // namespace nncv
}  // namespace mlir