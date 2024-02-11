#include "nncv/compiler/Conversion/MatMulOptimize/MatMul2NvMMA.hpp"
#include "mlir/Dialect/Tensor/Transforms/Transforms.h"
#include "nncv/compiler/Utils/PlatformCtx.hpp"

#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
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
#define GEN_PASS_DEF_MATMULOPTIMIZATION_NVMMA
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {
namespace matmul_optimize {

namespace {
class MatMulOptimizationNvMMAPass
    : public impl::MatMulOptimization_NvMMABase<MatMulOptimizationNvMMAPass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                    mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect,
                    mlir::linalg::LinalgDialect>();
  }

  void runOnOperation() override {
    //===----------------------------------------------------------------------===//
    // 1. Tiling
    //===----------------------------------------------------------------------===//
    IRRewriter rewriter(&getContext());
    llvm::SmallVector<mlir::linalg::MatmulOp> candidates;
    getOperation()->walk([&](linalg::MatmulOp op) { candidates.emplace_back(op); });
    for (auto& _op : candidates) {
      FailureOr<linalg::TiledLinalgOp> tiledOps;
      mlir::linalg::MatmulOp op = _op;
      ///<------------------------ Step 1.1. Tilling out loop
      {
        linalg::LinalgTilingOptions tileOption;
        tileOption.setTileSizes(
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileNvGpu.outerLevelLoops);

        OpBuilder::InsertionGuard guard(rewriter);
        rewriter.setInsertionPoint(op);

        tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
        rewriter.replaceOp(op, tiledOps->tensorResults);

        op = mlir::cast<mlir::linalg::MatmulOp>(tiledOps->op);
      }

      ///<------------------------ Step 1.2. Tilling inner loop
      {
        linalg::LinalgTilingOptions tileOption;
        tileOption.setTileSizes(
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileNvGpu.innerLevelLoops);

        OpBuilder::InsertionGuard guard0(rewriter);
        rewriter.setInsertionPoint(op);

        tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
        rewriter.replaceOp(op, tiledOps->tensorResults);

        op = mlir::cast<mlir::linalg::MatmulOp>(tiledOps->op);
      }

      ///<------------------------ Step 1.3. Tilling register loop
      {
        linalg::LinalgTilingOptions tileOption;
        tileOption.setTileSizes(
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileNvGpu.registerLevelLoops);

        OpBuilder::InsertionGuard guard(rewriter);
        rewriter.setInsertionPoint(op);

        FailureOr<linalg::TiledLinalgOp> tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
        rewriter.replaceOp(op, tiledOps->tensorResults);
      }
    }
  }
};
}  // namespace

std::unique_ptr<mlir::Pass> createMatMulOptimizationNvMMA() {
  return std::make_unique<MatMulOptimizationNvMMAPass>();
}

}  // namespace matmul_optimize
}  // namespace nncv
}  // namespace mlir