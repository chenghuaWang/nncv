#include "nncv/compiler/Conversion/Transforms/SplitParams.hpp"

#include "mlir/Conversion/LLVMCommon/ConversionTarget.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Dialect/Transform/IR/TransformDialect.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_SPLITPARAMS
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class SplitParamsPass : public impl::SplitParamsBase<SplitParamsPass> {
 public:
  void runOnOperation() override {
    // TODO
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createSplitParamsPass() { return std::make_unique<SplitParamsPass>(); }

}  // namespace mlir::nncv