#ifndef NNCV_C_CODEGEN_MODERN_TILE_HPP_
#define NNCV_C_CODEGEN_MODERN_TILE_HPP_

#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_MODERNTILE
#include "Conversion/Passes.h.inc"

namespace mlir::nncv {

namespace {}

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createModernOneShotTileAllPass();

}  // namespace mlir::nncv

#endif  //! NNCV_C_CODEGEN_MODERN_TILE_HPP_