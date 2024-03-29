/**
 * @file MemSolver.hpp
 * @author chenghua.wang (chenghua.wang.edu@gmail.com)
 * @brief 2D-BinPack-like Algorithm to solve memory reuse and management issues
 * The algorithm I used here is a improvement of `greedy by size for offset calculation`. See ref
 * 'EFFICIENT MEMORY MANAGEMENT FOR DEEP NEURAL NET INFERENCE' https://arxiv.org/pdf/2001.03288.pdf
 * @version 0.1
 * @date 2023-08-31
 *
 * @details Do not use this memory solver on GPU or NPU. Or to say, in circumstance that memory
 * resource is abundance and need parallel between Ops.
 *
 * Notes: It's quite hard to solve parallel memory management using this greedy algorithm. Parallel
 * Ops has too many cases that it's inefficient to figure out how to manage memory before run. I
 * will use stream-like method on GPU or other accelerating cards. And this Solver is the backend of
 * MemStream on CPU and other light-weighted device(Soc).
 *
 * The `buffer.alloc` in mlir will be warped to `MemStream` and Lowering to GPU/CPU. The `MemStream`
 * of CPU will using this mem solver class when lowering to llvm. And GPU Stream will lowering to
 * binary file directly.
 *
 * You can use the flag --no-prealloc to disable the memory pre-alloc.
 * `nncv-c --no-prealloc ./net.mlir -o net.nncv`
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef NNCV_COMPILER_OPT_MEM_SOLVER_HPP_
#define NNCV_COMPILER_OPT_MEM_SOLVER_HPP_

#include <stdint.h>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include <string.h>

namespace nncv {
namespace compiler {
namespace optimizer {

typedef int32_t MemSolverOpUUID_t;  ///< for user to figure the Ops.

struct TensorUsageInterval {
  TensorUsageInterval() : firstOp(-1), lastOp(-1) {}
  TensorUsageInterval(size_t s, size_t e) : firstOp(s), lastOp(e) {}
  int32_t firstOp;
  int32_t lastOp;
};

struct TensorUsageRecord {
  TensorUsageRecord(const TensorUsageInterval _interval, size_t _size)
      : interval(_interval), size(_size), offset(-1) {}
  TensorUsageInterval interval;
  size_t size;
  int32_t offset;
};

// don't need impl the memory allocate. This class just solve the memory manage problem in logic way
// two pass is needed. One pass to generate op uuid to mlir. Another pass judge the life time of
// tensor, and size.
class MemSolver {
 public:
  // [lifeTimeS, lifeTimeE] both size included. One op is one life time.
  void registerTensor(int32_t lifeTimeS, int32_t lifeTimeE, size_t size);

  bool solve();

  bool writeHtmlChart(const std::string& fpath);
  void showInTerminal();

  inline int32_t getTotalConsumption() const { return totalConsumption; }

 private:
  int32_t totalConsumption;
  std::vector<TensorUsageRecord> tensorUsageRecords;
};

}  // namespace optimizer
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_OPT_MEM_SOLVER_HPP_