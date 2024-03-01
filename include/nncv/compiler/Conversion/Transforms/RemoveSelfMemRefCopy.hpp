#ifndef NNCV_C_CONVERSION_REMOVE_MEMREF_COPY_SELF_ERASE_
#define NNCV_C_CONVERSION_REMOVE_MEMREF_COPY_SELF_ERASE_

#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_REMOVESELFMEMREFCOPY
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createRemoveSelfMemRefCopyPass();
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_REMOVE_MEMREF_COPY_SELF_ERASE_