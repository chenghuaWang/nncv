#pragma once

#ifndef NNCV_COMPILER_OPT_TILE_SOLVER_HPP_
#define NNCV_COMPILER_OPT_TILE_SOLVER_HPP_

#define TILE_SOLVER_SET_SOLVED_SIZES(op, func) m_Dict[__m_link_to_dict[op]].tileSizes = func(op);

#include <string>
#include <map>
#include <vector>
#include "mlir/IR/Location.h"
#include "mlir/IR/Operation.h"

namespace nncv {
namespace compiler {
namespace optimizer {

struct TileOpsNode {
  TileOpsNode() = default;
  TileOpsNode(const std::string& _opsName, mlir::Operation* _op) : opsName(_opsName), op(_op) {}

  inline int64_t getUUID() const { return uuid; }
  inline void setUUID(int64_t _uuid) { uuid = _uuid; }
  inline mlir::Operation* getOp() const { return op; }
  inline std::string getUniqueName() const { return opsName + "_uuid_" + std::to_string(uuid); }

 private:
  std::string opsName;
  mlir::Operation* op;
  int64_t uuid;
};

struct __cmp_tile_ops_node {
  typedef TileOpsNode value_type;
  // compare must be made to const.
  bool operator()(const value_type& ls, const value_type& rs) const {
    return ls.getUUID() < rs.getUUID();
  }
};

struct TileOptions {
  // tile
  std::vector<std::vector<int64_t>> tileSizes;

  // thread dispatch
  // TODO
};

class TileSolver {
 public:
  TileSolver() = default;
  ~TileSolver() = default;
  TileSolver(const TileSolver&) = delete;
  TileSolver& operator=(const TileSolver&) = delete;
  static TileSolver& getInstance() {
    static TileSolver instance;
    return instance;
  }

  void registerOp(const std::string& opsName, mlir::Operation* op);
  void solveTileSize();
  void solveThreadDispatch();
  TileOptions getRecommendOption(mlir::Operation* op);
  void dump();

  // a iteration function
  // the operation is sorted by uuid, so the iteration sequence is match the network.
  // TODO

 private:
  // Tiles
  std::vector<std::vector<int64_t>> solveTileSizesMatMul(mlir::Operation* op);
  std::vector<std::vector<int64_t>> solveTileSizesPooling(mlir::Operation* op);
  std::vector<std::vector<int64_t>> solveTileSizesConv2d(mlir::Operation* op);
  std::vector<std::vector<int64_t>> solveTileSizesGeneric(mlir::Operation* op);

  bool isDynamic(const std::vector<int64_t>& shape);
  int64_t get2sPowOrSelf(int64_t i);

 private:
  int64_t m_UUID = 0;
  std::map<mlir::Operation*, TileOpsNode> __m_link_to_dict;
  std::map<TileOpsNode, TileOptions, __cmp_tile_ops_node> m_Dict;
};

}  // namespace optimizer
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_OPT_TILE_SOLVER_HPP_