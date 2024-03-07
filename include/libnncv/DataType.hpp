#ifndef NNCV_LIB_NNCV_RT_DATA_TYPE_HPP_
#define NNCV_LIB_NNCV_RT_DATA_TYPE_HPP_

#include <cmath>
#include <complex>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

#define WRAP_FOR_MEMREF_ARRAY(type)          \
  auto _ptr = new MemRefDescriptor<type, 1>; \
  _ptr->aligned = (type*)m_binaryData;       \
  _ptr->allocated = (type*)m_binaryData;     \
  _ptr->offset = 0;                          \
  _ptr->strides[0] = 1;                      \
  _ptr->sizes[0] = size_0;                   \
  m_wraped = _ptr;

#define WRAPED_PARAMS_TYPE(type) MemRefDescriptor<UnrankedMemRefType<type>, 1>

#define WRAP_ALL_TO_ONE_DIM_MEMREF(type)                                    \
  auto _ptr = new MemRefDescriptor<UnrankedMemRefType<type>, 1>;            \
  _ptr->allocated = (UnrankedMemRefType<type>*)m_wrapedUnrankMemRef.data(); \
  _ptr->aligned = (UnrankedMemRefType<type>*)m_wrapedUnrankMemRef.data();   \
  _ptr->offset = 0;                                                         \
  _ptr->sizes[0] = m_indexer.size();                                        \
  _ptr->strides[0] = 1;                                                     \
  m_wraped = (void*)_ptr;

#define ADD_DEC_TO_UNRANK_MEMREF(type)        \
  auto _ptr = new UnrankedMemRefType<type>(); \
  _ptr->descriptor = describe;                \
  _ptr->rank = rank;                          \
  return (void*)_ptr;

#define ADD_SHAPES_INFER_FOR_MEMREF(type)                                           \
  switch (mri.dims) {                                                               \
    case 1: {                                                                       \
      auto _ptr = new MemRefDescriptor<type, 1>();                                  \
      _ptr->allocated = (type*)data;                                                \
      _ptr->aligned = (type*)data;                                                  \
      _ptr->offset = 0;                                                             \
      _ptr->sizes[0] = mri.shape[0];                                                \
      _ptr->strides[0] = 1;                                                         \
      return (void*)_ptr;                                                           \
      break;                                                                        \
    }                                                                               \
    case 2: {                                                                       \
      auto _ptr = new MemRefDescriptor<type, 2>();                                  \
      _ptr->allocated = (type*)data;                                                \
      _ptr->aligned = (type*)data;                                                  \
      _ptr->offset = 0;                                                             \
      _ptr->sizes[0] = mri.shape[0];                                                \
      _ptr->sizes[1] = mri.shape[1];                                                \
      _ptr->strides[0] = 1;                                                         \
      _ptr->strides[1] = mri.shape[0];                                              \
      return (void*)_ptr;                                                           \
      break;                                                                        \
    }                                                                               \
    case 3: {                                                                       \
      auto _ptr = new MemRefDescriptor<type, 3>();                                  \
      _ptr->allocated = (type*)data;                                                \
      _ptr->aligned = (type*)data;                                                  \
      _ptr->offset = 0;                                                             \
      _ptr->sizes[0] = mri.shape[0];                                                \
      _ptr->sizes[1] = mri.shape[1];                                                \
      _ptr->sizes[2] = mri.shape[2];                                                \
      _ptr->strides[0] = 1;                                                         \
      _ptr->strides[1] = mri.shape[0];                                              \
      _ptr->strides[2] = mri.shape[0] * mri.shape[1];                               \
      return (void*)_ptr;                                                           \
      break;                                                                        \
    }                                                                               \
    case 4: {                                                                       \
      auto _ptr = new MemRefDescriptor<type, 4>();                                  \
      _ptr->allocated = (type*)data;                                                \
      _ptr->aligned = (type*)data;                                                  \
      _ptr->offset = 0;                                                             \
      _ptr->sizes[0] = mri.shape[0];                                                \
      _ptr->sizes[1] = mri.shape[1];                                                \
      _ptr->sizes[2] = mri.shape[2];                                                \
      _ptr->sizes[3] = mri.shape[3];                                                \
      _ptr->strides[0] = 1;                                                         \
      _ptr->strides[1] = mri.shape[0];                                              \
      _ptr->strides[2] = mri.shape[0] * mri.shape[1];                               \
      _ptr->strides[3] = mri.shape[0] * mri.shape[1] * mri.shape[2];                \
      return (void*)_ptr;                                                           \
      break;                                                                        \
    }                                                                               \
    case 5: {                                                                       \
      auto _ptr = new MemRefDescriptor<type, 5>();                                  \
      _ptr->allocated = (type*)data;                                                \
      _ptr->aligned = (type*)data;                                                  \
      _ptr->offset = 0;                                                             \
      _ptr->sizes[0] = mri.shape[0];                                                \
      _ptr->sizes[1] = mri.shape[1];                                                \
      _ptr->sizes[2] = mri.shape[2];                                                \
      _ptr->sizes[3] = mri.shape[3];                                                \
      _ptr->sizes[4] = mri.shape[4];                                                \
      _ptr->strides[0] = 1;                                                         \
      _ptr->strides[1] = mri.shape[0];                                              \
      _ptr->strides[2] = mri.shape[0] * mri.shape[1];                               \
      _ptr->strides[3] = mri.shape[0] * mri.shape[1] * mri.shape[2];                \
      _ptr->strides[4] = mri.shape[0] * mri.shape[1] * mri.shape[2] * mri.shape[3]; \
      return (void*)_ptr;                                                           \
      break;                                                                        \
    }                                                                               \
  }

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

class MemRefFlatArray {
 public:
  MemRefFlatArray() = delete;
  MemRefFlatArray(const dataType& dt) : m_dataType(dt) {}
  ~MemRefFlatArray();
  bool read(const std::string& path);
  bool write(const std::string& path);

  void addMemRefIndexer(const MemRefIndexer& indexer, void* data);

  template<typename T>
  inline T* getWrapedData() {
    return (T*)m_wraped;
  }

  inline void* get() { return m_wraped; }

 private:
  void wrap();

 private:
  // magic head
  MemRefMagicHead m_head;

  // register will use vars below
  std::vector<MemRefIndexer> m_indexer;
  std::vector<void*> m_data;
  dataType m_dataType;

  // read file and write to this two var.
  void* m_wraped;
  char* m_binaryData;
};

// The Flat Buffer uses UnrankedMemref to pass a set of memref, which is buggy now. Try to use
// MemRefFlatArray now.
//
// see-discuss:
// https://discourse.llvm.org/t/how-to-pass-a-set-of-memrefs-to-an-mlir-function-from-the-c-side/77424/1
// see-patch: https://reviews.llvm.org/D96397#change-2RDEmSq5iVxi
//
// write/read from file.
struct MemRefFlatBuffer {
  MemRefFlatBuffer() = delete;
  MemRefFlatBuffer(const dataType& dt) : m_dataType(dt) {}
  ~MemRefFlatBuffer();
  bool read(const std::string& path);
  bool write(const std::string& path);

  void addMemRefIndexer(const MemRefIndexer& indexer, void* data);

  template<typename T>
  inline T* getWrapedData() {
    return (T*)m_wraped;
  }

  inline void printInfo() {
    int cnt = 0;
    for (int iv = 0; iv < m_indexer.size(); ++iv) {
      auto item = m_indexer[iv];
      printf("idx: %d, shape[", cnt++);
      for (int i = 0; i < item.dims - 1; ++i) { printf("%ld, ", item.shape[i]); }
      printf("%ld], at %p\n", item.shape[item.dims - 1], m_data[iv]);
    }
  }

 private:
  void wrap();

  inline void* createUnarnkedMemRef(int64_t rank, void* describe) {
    switch (m_dataType) {
      case dataType::kFloat16: {
        ADD_DEC_TO_UNRANK_MEMREF(nncvFloat16)
        break;
      }
      case dataType::kFloat32: {
        ADD_DEC_TO_UNRANK_MEMREF(nncvFloat32)
        break;
      }
      case dataType::kInt16: {
        ADD_DEC_TO_UNRANK_MEMREF(nncvInt16)
        break;
      }
      case dataType::kInt32: {
        ADD_DEC_TO_UNRANK_MEMREF(nncvInt32)
        break;
      }
      case dataType::kUnknow: {
        return nullptr;
      }
    }
  }

  inline void* createMemRefDescriptor(MemRefIndexer& mri, void* data) {
    switch (m_dataType) {
      case dataType::kFloat16: {
        ADD_SHAPES_INFER_FOR_MEMREF(nncvFloat16)
        break;
      }
      case dataType::kFloat32: {
        ADD_SHAPES_INFER_FOR_MEMREF(nncvFloat32)
        break;
      }
      case dataType::kInt16: {
        ADD_SHAPES_INFER_FOR_MEMREF(nncvInt16)
        break;
      }
      case dataType::kInt32: {
        ADD_SHAPES_INFER_FOR_MEMREF(nncvInt32)
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
  std::vector<void*> m_wrapedUnrankMemRef;
  dataType m_dataType;
  void* m_wraped;
};

}  // namespace rt
}  // namespace nncv

#endif  //! NNCV_LIB_NNCV_RT_DATA_TYPE_HPP_