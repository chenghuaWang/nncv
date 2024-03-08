#ifndef NNCV_C_CONVERSION_REGISTER_MEM_TO_GPU_HPP_
#define NNCV_C_CONVERSION_REGISTER_MEM_TO_GPU_HPP_

#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_REGISTERMEMTOGPU
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createRegisterMemToGpuPass();
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_REGISTER_MEM_TO_GPU_HPP_