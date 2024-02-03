#include "nncv/compiler/Utils/PlatformCtx.hpp"
#include "llvm/Support/CommandLine.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace nncv::compiler::utils {

void PlatformCtx::InitFromConfigFile() {
  // open json file
  llvm::cl::opt<std::string> configFilePathOption(
      "config-file-path", llvm::cl::desc("<config file path>"), llvm::cl::Optional);
  std::string filePath =
      configFilePathOption.getValue().empty() ? "config.json" : configFilePathOption.getValue();

  // read json
  std::ifstream f(filePath);
  json data = json::parse(f);

  //===----------------------------------------------------------------------===//
  // 1.1 Tile Size.
  //===----------------------------------------------------------------------===//
  auto tileSizeData = data["TileSize"];
  // MatMul
  this->MatMulTileCpu.outerLevelLoops = tileSizeData["Matmul"]["outer"].get<std::vector<int64_t>>();
  this->MatMulTileCpu.innerLevelLoops = tileSizeData["Matmul"]["inner"].get<std::vector<int64_t>>();
  this->MatMulTileCpu.registerLevelLoops =
      tileSizeData["Matmul"]["register"].get<std::vector<int64_t>>();
  // Generic
  this->LinalgGenericTileCpu.outerLevelLoops =
      tileSizeData["Generic"]["outer"].get<std::vector<int64_t>>();
  this->LinalgGenericTileCpu.innerLevelLoops =
      tileSizeData["Generic"]["inner"].get<std::vector<int64_t>>();
  this->LinalgGenericTileCpu.registerLevelLoops =
      tileSizeData["Generic"]["register"].get<std::vector<int64_t>>();
}

}  // namespace nncv::compiler::utils
