#include "nncv/compiler/Utils/MlirIo.hpp"
#include <system_error>

#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Parser/Parser.h"
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

bool ImportMlirModuleFromFile(mlir::OwningOpRef<mlir::ModuleOp>& m, mlir::MLIRContext* ctx,
                              const std::string& filep) {
  std::string ErrorMessage;
  auto __file = mlir::openInputFile(filep, &ErrorMessage);
  if (!__file) {
    printf("[ Erro ] %s\n", ErrorMessage.c_str());
    return false;
  }
  std::unique_ptr<llvm::MemoryBuffer> Buffer = std::move(__file);
  llvm::SourceMgr SourceMgr;
  SourceMgr.AddNewSourceBuffer(std::move(Buffer), llvm::SMLoc());
  mlir::ParserConfig config(ctx);
  m = mlir::parseSourceFile<mlir::ModuleOp>(SourceMgr, config);
  return true;
}

}  // namespace utils
}  // namespace compiler
}  // namespace nncv