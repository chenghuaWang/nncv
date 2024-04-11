#include "nncv/compiler/Conversion/CodeGen/Advance/FinalVec.hpp"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlowOps.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/Passes.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_ADVANCEDFINALVEC
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {}

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createAdvancedFinalVecPass() {}

}  // namespace mlir::nncv