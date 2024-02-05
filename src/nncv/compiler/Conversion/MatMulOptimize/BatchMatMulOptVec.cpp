#include "nncv/compiler/Conversion/MatMulOptimize/BatchMatMulOptVec.hpp"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/IR/Operation.h"
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
#define GEN_PASS_DEF_MATMULOPTIMIZATION_FORBATCH
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {
namespace matmul_optimize {

namespace {

class BatchMatMulOptimizationVec
    : public impl::MatMulOptimization_ForBatchBase<BatchMatMulOptimizationVec> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry
        .insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    llvm::SmallVector<mlir::Operation*> candidates;
    IRRewriter rewriter(&getContext());

    getOperation().walk([&](linalg::BatchMatmulOp op) { candidates.emplace_back(op); });

    for (auto item : candidates) {
      auto op = mlir::cast<mlir::linalg::BatchMatmulOp>(item);
      auto numLoops = op.getNumLoops();

      llvm::SmallVector<int64_t> _tileSizes(numLoops, 0);
      _tileSizes[0] = 1;

      mlir::linalg::LinalgTilingOptions tileOption;
      tileOption.setTileSizes(_tileSizes);

      OpBuilder::InsertionGuard guard(rewriter);
      rewriter.setInsertionPoint(op);

      auto tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
      rewriter.replaceOp(op, tiledOps->tensorResults);
    }
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createMatMulOptimizationForBatchPass() {
  return std::make_unique<BatchMatMulOptimizationVec>();
}
}  // namespace matmul_optimize
}  // namespace nncv
}  // namespace mlir