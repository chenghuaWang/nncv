#include "nncv/compiler/Optimizer/MemSolver.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>

using namespace nncv::compiler::optimizer;

void MemSolver::registerTensor(int32_t lifeTimeS, int32_t lifeTimeE, size_t size) {
  tensorUsageRecords.emplace_back(
      TensorUsageRecord(TensorUsageInterval(lifeTimeS, lifeTimeE), size));
}

bool MemSolver::solve() {
  // sort tensor usage records in non-increasing order of size
  std::sort(
      tensorUsageRecords.begin(), tensorUsageRecords.end(),
      [](TensorUsageRecord& lhs, TensorUsageRecord& rhs) -> bool { return lhs.size > rhs.size; });
  // loop the tensor usage records.
  totalConsumption = 0;
  std::vector<TensorUsageRecord> orderedAllocatedIds;
  for (auto& t : tensorUsageRecords) {
    int32_t prevOffset = 0;
    int32_t bestOffset = -1;
    int32_t smallestGap = std::numeric_limits<int32_t>::max();
    // to check if overlapped.
    for (auto& x : orderedAllocatedIds) {
      int32_t maxFirstOp = std::max(t.interval.firstOp, x.interval.firstOp);
      int32_t minLastOp = std::min(t.interval.lastOp, x.interval.lastOp);
      if (maxFirstOp <= minLastOp) {
        int32_t gap = x.offset - prevOffset;
        if (gap >= (int32_t)t.size && gap < smallestGap) {
          smallestGap = gap;
          bestOffset = prevOffset;
        }
        prevOffset = std::max(prevOffset, x.offset + (int32_t)x.size);
      }
    }
    if (bestOffset == -1) { bestOffset = prevOffset; }
    t.offset = bestOffset;
    totalConsumption = std::max(totalConsumption, bestOffset + (int32_t)t.size);
    orderedAllocatedIds.emplace_back(t);
  }
  tensorUsageRecords = orderedAllocatedIds;
  return true;
}

bool MemSolver::writeHtmlChart(const std::string& fpath) {
  // TODO
  return false;
}

void MemSolver::showInTerminal() {
  // TODO
}