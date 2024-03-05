#ifndef NNCV_LIB_NNCV_RT_DATA_TYPE_HPP_
#define NNCV_LIB_NNCV_RT_DATA_TYPE_HPP_

#include <cmath>
#include <complex>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

namespace nncv {
namespace rt /*runtime*/ {

enum class dataType : size_t {
  kFloat32 = 0x1,
  kFloat16,
  kInt32,
  kInt16,
  kUnknow,
};

typedef int16_t nncvInt16;
typedef int32_t nncvInt32;
typedef uint32_t nncvFloat32;
typedef uint16_t nncvFloat16;

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
  MemRefFlatBuffer() = delete;
  MemRefFlatBuffer(const dataType& dt) : m_dataType(dt) {}
  ~MemRefFlatBuffer();
  bool read(const std::string& path);
  bool write(const std::string& path);

  void addMemRefIndexer(const MemRefIndexer& indexer, void* data);

 private:
  void wrap();

  inline void* createMemRefDescriptor(MemRefIndexer& mri, void* data) {
    switch (m_dataType) {
      case dataType::kFloat16: {
        switch (mri.dims) {
          case 1: {
            auto _ptr = new MemRefDescriptor<nncvFloat16, 1>();
            _ptr->allocated = (nncvFloat16*)data;
            _ptr->aligned = nullptr;
            _ptr->offset = 0;
            _ptr->sizes[0] = mri.shape[0];
            _ptr->strides[0] = 1;
          }
        }
        break;
      }
      case dataType::kFloat32: {
        break;
      }
      case dataType::kInt16: {
        break;
      }
      case dataType::kInt32: {
        break;
      }
      case dataType::kUnknow: {
        return nullptr;
      }
    }
    return nullptr;
  }

  MemRefMagicHead m_head;
  std::vector<MemRefIndexer> m_indexer;
  std::vector<void*> m_data;
  dataType m_dataType;
};

}  // namespace rt
}  // namespace nncv

#endif  //! NNCV_LIB_NNCV_RT_DATA_TYPE_HPP_