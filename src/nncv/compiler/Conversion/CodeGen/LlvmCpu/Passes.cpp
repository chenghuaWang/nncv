#include "nncv/compiler/Conversion/Passes.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"
#include "nncv/compiler/Conversion/CodeGen/ModernTile.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/DecomposeTransGen.hpp"

namespace mlir::nncv::codegen_llvm_cpu {

// 1. tile all linalg.ops
// 2. do some decompose on conv interface op.
void addTilePassPipeline(mlir::PassManager& pm) {
  pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createModernOneShotTileAllPass());
  pm.addNestedPass<mlir::func::FuncOp>(mlir::nncv::createDecomposeTransformGenPass());
  pm.addNestedPass<mlir::func::FuncOp>(mlir::createCSEPass());
}

}  // namespace mlir::nncv::codegen_llvm_cpu