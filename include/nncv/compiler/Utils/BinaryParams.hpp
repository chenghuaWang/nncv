#ifndef NNCV_C_BINARY_PARAMS_HPP_
#define NNCV_C_BINARY_PARAMS_HPP_

#include <cmath>
#include <complex>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

namespace nncv {
namespace utils {

typedef int16_t NoType16bType;
typedef int32_t NoType32bType;

template<typename T, size_t N>
struct MemRefDescriptor {
  T* allocated;
  T* aligned;
  intptr_t offset;
  intptr_t sizes[N];
  intptr_t strides[N];
};

template<typename T>
struct UnrankedMemRefType {
  int64_t rank;
  void* descriptor;
};

struct MemRefIndexer {
  char name[128];
  size_t dims;
  size_t shape[8];
  size_t eleWidth;
  size_t aligned;
  size_t dataOffset;
};

// - MemRefMagicHead -
// - MemRefIndexer 1 -
// - MemRefIndexer 2 -
// - data of Ref 1   -
// - data of Ref 2   -
struct MemRefMagicHead {
  int64_t magicNumber = 0x42;
  size_t memRefIndexStartOffset;
  size_t numMemRefIndex;
};

// write/read from file.
struct MemRefFlatBuffer {
  bool read(const std::string& path);
  bool write(const std::string& path);
  inline void* getBuffer() { return m_unrankedBuffer; };

  void addMemRefIndexer(const MemRefIndexer& indexer, void* data);

  MemRefFlatBuffer() = default;
  ~MemRefFlatBuffer() {}
  MemRefFlatBuffer(const MemRefFlatBuffer&) = delete;
  MemRefFlatBuffer& operator=(const MemRefFlatBuffer&) = delete;

  static MemRefFlatBuffer& getInstance() {
    static MemRefFlatBuffer instance;
    return instance;
  }

  MemRefMagicHead m_head;
  std::vector<MemRefIndexer> m_indexer;
  std::vector<void*> m_data;
  void* m_unrankedBuffer;
};

}  // namespace utils
}  // namespace nncv

#endif  //! NNCV_C_BINARY_PARAMS_HPP_