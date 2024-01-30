#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptVec.hpp"
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
#define GEN_PASS_DEF_MATMULOPTIMIZATION_VEC
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {
namespace matmul_optimize {

namespace {

class MatMulOptimizationVec : public impl::MatMulOptimization_VecBase<MatMulOptimizationVec> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry
        .insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    IRRewriter rewriter(&getContext());
    if (m_enableNvGPU) {
    } else {
      // Step 1.1 Tiling outter loops
      getOperation()->walk([&](linalg::MatmulOp op) {
        // This pass should work on tensor.
        if (op.hasBufferSemantics()) return signalPassFailure();
        // [Linalg + Tensor] High Level Tile
        SmallVector<int64_t, 3> tiles(op.getNumLoops());
        tiles[0] =
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileCpu.outerLevelLoops[0];
        tiles[1] =
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileCpu.outerLevelLoops[1];
        tiles[2] =
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileCpu.outerLevelLoops[2];

        linalg::LinalgTilingOptions tileOption;
        tileOption.setTileSizes(tiles);

        OpBuilder::InsertionGuard guard(rewriter);
        rewriter.setInsertionPoint(op);

        FailureOr<linalg::TiledLinalgOp> tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
        rewriter.replaceOp(op, tiledOps->tensorResults);
      });

      // Step 1.1 Tiling inner loops
      getOperation()->walk([&](linalg::MatmulOp op) {
        // This pass should work on tensor.
        if (op.hasBufferSemantics()) return signalPassFailure();
        // [Linalg + Tensor] High Level Tile
        SmallVector<int64_t, 3> tiles(op.getNumLoops());
        tiles[0] =
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileCpu.innerLevelLoops[0];
        tiles[1] =
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileCpu.innerLevelLoops[1];
        tiles[2] =
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileCpu.innerLevelLoops[2];

        linalg::LinalgTilingOptions tileOption;
        tileOption.setTileSizes(tiles);

        OpBuilder::InsertionGuard guard(rewriter);
        rewriter.setInsertionPoint(op);

        FailureOr<linalg::TiledLinalgOp> tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
        rewriter.replaceOp(op, tiledOps->tensorResults);
      });

      // Step 1.1 Tiling register loops
      getOperation()->walk([&](linalg::MatmulOp op) {
        // This pass should work on tensor.
        if (op.hasBufferSemantics()) return signalPassFailure();
        // [Linalg + Tensor] High Level Tile
        SmallVector<int64_t, 3> tiles(op.getNumLoops());
        tiles[0] =
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileCpu.registerLevelLoops[0];
        tiles[1] =
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileCpu.registerLevelLoops[1];
        tiles[2] =
            ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTileCpu.registerLevelLoops[2];

        linalg::LinalgTilingOptions tileOption;
        tileOption.setTileSizes(tiles);

        OpBuilder::InsertionGuard guard(rewriter);
        rewriter.setInsertionPoint(op);

        FailureOr<linalg::TiledLinalgOp> tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
        rewriter.replaceOp(op, tiledOps->tensorResults);
      });
    }

    // Step 2.
    mlir::RewritePatternSet patterns(&getContext());
    linalg::populateLinalgTilingCanonicalizationPatterns(patterns);
    if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      signalPassFailure();
    }
  }

  void setNvGPU(bool flag = true) { m_enableNvGPU = flag; }
  bool isNvGPUEnable() { return m_enableNvGPU; }

 private:
  bool m_enableNvGPU = false;
};

}  // namespace

std::unique_ptr<mlir::Pass> createMatMulOptimizationVecPass(bool flag) {
  auto res = std::make_unique<MatMulOptimizationVec>();
  res->setNvGPU(flag);
  return res;
}
}  // namespace matmul_optimize
}  // namespace nncv
}  // namespace mlir