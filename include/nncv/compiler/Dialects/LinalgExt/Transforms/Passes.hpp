#ifndef NNCV_COMPILER_NNCV_LINALG_EXT_TRANSFORMS_PASS_HPP_
#define NNCV_COMPILER_NNCV_LINALG_EXT_TRANSFORMS_PASS_HPP_

#include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtOps.hpp"
#include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtDialect.hpp"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/SCF/Transforms/TileUsingInterface.h"
#include "mlir/Pass/Pass.h"

namespace mlir::nncv {
class ConversionTarget;
class TypeConverter;

namespace linalg_ext {
std::unique_ptr<OperationPass<func::FuncOp>> createTileAndDecomposeWinogradTransformPass();
}

}  // namespace mlir::nncv

#endif  //! NNCV_COMPILER_NNCV_LINALG_EXT_TRANSFORMS_PASS_HPP_