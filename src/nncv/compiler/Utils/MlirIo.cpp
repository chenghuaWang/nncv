#include "nncv/compiler/Utils/MlirIo.hpp"
#include <system_error>

#include "llvm/Support/raw_ostream.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/IR/AsmState.h"

namespace nncv {
namespace compiler {
namespace utils {
bool SaveMlirModuleToFile(mlir::OwningOpRef<mlir::ModuleOp>& m, const std::string& filep) {
  std::error_code errCode;
  auto outputFile = llvm::raw_fd_ostream(filep, errCode);
  if (errCode.value() != 0) { return false; }
  m->print(outputFile);
  return true;
}
}  // namespace utils
}  // namespace compiler
}  // namespace nncv