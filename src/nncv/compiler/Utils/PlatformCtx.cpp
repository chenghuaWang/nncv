#include "nncv/compiler/Utils/PlatformCtx.hpp"
#include "llvm/Support/CommandLine.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace nncv::compiler::utils {

void PlatformCtx::InitFromConfigFile() {
  // open json file
  std::string filePath = m_ConfigFilePath.empty() ? "config.json" : m_ConfigFilePath;

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
  //===----------------------------------------------------------------------===//
  // 1.2 Vec Size.
  //===----------------------------------------------------------------------===//
  auto vecSizeData = data["VecSize"];
  // MatMul
  this->MatMulVecCpu.vecSize = vecSizeData["Matmul"].get<std::vector<int64_t>>();
  // Generic
  this->LinalgGenericVecCpu.vecSize = vecSizeData["Generic"].get<std::vector<int64_t>>();
}

}  // namespace nncv::compiler::utils
