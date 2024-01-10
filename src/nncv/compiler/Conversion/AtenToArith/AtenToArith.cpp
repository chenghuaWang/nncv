#include "nncv/compiler/Conversion/AtenToArith/AtenToArith.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_CONVERTAFFINETOSTANDARD
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createConvertAtenToArithPass() {}
}  // namespace nncv
}  // namespace mlir