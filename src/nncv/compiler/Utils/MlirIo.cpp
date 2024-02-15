#include "nncv/compiler/Utils/MlirIo.hpp"
#include "nncv/compiler/Optimizer/TileSolver.hpp"

#include <string>
#include <system_error>

#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/IR/AsmState.h"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

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

bool SaveTileOpsConfigFile(const std::string& filep) {
  std::ofstream f(filep);
  if (!f.good()) return false;

  auto dict = ::nncv::compiler::optimizer::TileSolver::getInstance().getDict();

  json data;

  for (auto& item : dict) {
    auto node = item.first;
    auto options = item.second;
    auto key = node.getUniqueName();

    for (size_t i = 0; i < options.tileSizes.size(); ++i) {
      data[key]["tile"]["level-" + std::to_string(i)] = options.tileSizes[i];
    }

    // TODO save thread dispatch data.
  }

  f << std::setw(4) << data << std::endl;
  f.close();

  return true;
}

bool ReadTileOpsConfigFile(const std::string& filep) {
  std::ifstream f(filep);
  if (!f.good()) return false;

  auto dict = ::nncv::compiler::optimizer::TileSolver::getInstance().getDict();
  if (dict.empty()) {
    printf("[ Erro ] You shoudl run register linalg ops pass first before load a config file.\n");
  }

  json data = json::parse(f);
  for (auto& item : dict) {
    // TODO
  }

  return true;
}

}  // namespace utils
}  // namespace compiler
}  // namespace nncv