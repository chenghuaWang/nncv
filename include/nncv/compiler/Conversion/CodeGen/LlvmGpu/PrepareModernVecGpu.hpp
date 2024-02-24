#ifndef NNCV_C_CODEGEN_PREPARE_MODERN_VEC_GPU_HPP_
#define NNCV_C_CODEGEN_PREPARE_MODERN_VEC_GPU_HPP_

#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_PREPAREMODERNVECGPU
#include "Conversion/Passes.h.inc"

namespace mlir::nncv {

namespace {}

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createPrepareModernVecGpuPass();

}  // namespace mlir::nncv

#endif  //! NNCV_C_CODEGEN_PREPARE_MODERN_VEC_GPU_HPP_