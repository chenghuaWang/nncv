#include "nncv/compiler/Conversion/LinalgOptimize/LinalgGenericTile.hpp"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/LinalgInterfaces.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_LINALGGENERICTILE
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {

namespace {
class LinalgGenericTilePass : public impl::LinalgGenericTileBase<LinalgGenericTilePass> {
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
      getOperation()->walk([&](linalg::LinalgOp op) {
        // This pass should work on tensor.
        if (op.hasBufferSemantics()) return signalPassFailure();
        // TODO
      });
    }
  }

  void setNvGPU(bool flag = true) { m_enableNvGPU = flag; }
  bool isNvGPUEnable() { return m_enableNvGPU; }

 private:
  bool m_enableNvGPU = false;
};
}  // namespace

std::unique_ptr<mlir::Pass> createLinalgGenericTilePass(bool flag) {
  auto res = std::make_unique<LinalgGenericTilePass>();
  res->setNvGPU(flag);
  return res;
}

}  // namespace nncv
}  // namespace mlir