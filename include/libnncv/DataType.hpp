#ifndef NNCV_LIB_NNCV_RT_DATA_TYPE_HPP_
#define NNCV_LIB_NNCV_RT_DATA_TYPE_HPP_

#include <array>
#include <cassert>
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

// memref printer. ref from
// https://github.com/llvm/llvm-project/blob/9d3bf9b639eafeded82c6be295031262735d1dac/mlir/include/mlir/ExecutionEngine/RunnerUtils.h
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
template<int N>
void dropFront(int64_t arr[N], int64_t* res) {
  for (unsigned i = 1; i < N; ++i) *(res + i - 1) = arr[i];
}

template<typename T, int Rank>
class StridedMemrefIterator;

/// StridedMemRef descriptor type with static rank.
template<typename T, int N>
struct StridedMemRefType {
  T* basePtr;
  T* data;
  int64_t offset;
  int64_t sizes[N];
  int64_t strides[N];

  template<typename Range, typename sfinae = decltype(std::declval<Range>().begin())>
  T& operator[](Range&& indices) {
    assert(indices.size() == N && "indices should match rank in memref subscript");
    int64_t curOffset = offset;
    for (int dim = N - 1; dim >= 0; --dim) {
      int64_t currentIndex = *(indices.begin() + dim);
      assert(currentIndex < sizes[dim] && "Index overflow");
      curOffset += currentIndex * strides[dim];
    }
    return data[curOffset];
  }

  StridedMemrefIterator<T, N> begin() { return {*this, offset}; }
  StridedMemrefIterator<T, N> end() { return {*this, -1}; }

  // This operator[] is extremely slow and only for sugaring purposes.
  StridedMemRefType<T, N - 1> operator[](int64_t idx) {
    StridedMemRefType<T, N - 1> res;
    res.basePtr = basePtr;
    res.data = data;
    res.offset = offset + idx * strides[0];
    dropFront<N>(sizes, res.sizes);
    dropFront<N>(strides, res.strides);
    return res;
  }
};

/// StridedMemRef descriptor type specialized for rank 1.
template<typename T>
struct StridedMemRefType<T, 1> {
  T* basePtr;
  T* data;
  int64_t offset;
  int64_t sizes[1];
  int64_t strides[1];

  template<typename Range, typename sfinae = decltype(std::declval<Range>().begin())>
  T& operator[](Range indices) {
    assert(indices.size() == 1 && "indices should match rank in memref subscript");
    return (*this)[*indices.begin()];
  }

  StridedMemrefIterator<T, 1> begin() { return {*this, offset}; }
  StridedMemrefIterator<T, 1> end() { return {*this, -1}; }

  T& operator[](int64_t idx) { return *(data + offset + idx * strides[0]); }
};

/// StridedMemRef descriptor type specialized for rank 0.
template<typename T>
struct StridedMemRefType<T, 0> {
  T* basePtr;
  T* data;
  int64_t offset;

  template<typename Range, typename sfinae = decltype(std::declval<Range>().begin())>
  T& operator[](Range indices) {
    assert((indices.size() == 0) && "Expect empty indices for 0-rank memref subscript");
    return data[offset];
  }

  StridedMemrefIterator<T, 0> begin() { return {*this, offset}; }
  StridedMemrefIterator<T, 0> end() { return {*this, offset + 1}; }
};

/// Iterate over all elements in a strided memref.
template<typename T, int Rank>
class StridedMemrefIterator {
 public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using reference = T&;

  StridedMemrefIterator(StridedMemRefType<T, Rank>& descriptor, int64_t offset = 0)
      : offset(offset), descriptor(&descriptor) {}
  StridedMemrefIterator<T, Rank>& operator++() {
    int dim = Rank - 1;
    while (dim >= 0 && indices[dim] == (descriptor->sizes[dim] - 1)) {
      offset -= indices[dim] * descriptor->strides[dim];
      indices[dim] = 0;
      --dim;
    }
    if (dim < 0) {
      offset = -1;
      return *this;
    }
    ++indices[dim];
    offset += descriptor->strides[dim];
    return *this;
  }

  reference operator*() { return descriptor->data[offset]; }
  pointer operator->() { return &descriptor->data[offset]; }

  const std::array<int64_t, Rank>& getIndices() { return indices; }

  bool operator==(const StridedMemrefIterator& other) const {
    return other.offset == offset && other.descriptor == descriptor;
  }

  bool operator!=(const StridedMemrefIterator& other) const { return !(*this == other); }

 private:
  /// Offset in the buffer. This can be derived from the indices and the
  /// descriptor.
  int64_t offset = 0;

  /// Array of indices in the multi-dimensional memref.
  std::array<int64_t, Rank> indices = {};

  /// Descriptor for the strided memref.
  StridedMemRefType<T, Rank>* descriptor;
};

/// Iterate over all elements in a 0-ranked strided memref.
template<typename T>
class StridedMemrefIterator<T, 0> {
 public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using reference = T&;

  StridedMemrefIterator(StridedMemRefType<T, 0>& descriptor, int64_t offset = 0)
      : elt(descriptor.data + offset) {}

  StridedMemrefIterator<T, 0>& operator++() {
    ++elt;
    return *this;
  }

  reference operator*() { return *elt; }
  pointer operator->() { return elt; }

  // There are no indices for a 0-ranked memref, but this API is provided for
  // consistency with the general case.
  const std::array<int64_t, 0>& getIndices() {
    // Since this is a 0-array of indices we can keep a single global const
    // copy.
    static const std::array<int64_t, 0> indices = {};
    return indices;
  }

  bool operator==(const StridedMemrefIterator& other) const { return other.elt == elt; }

  bool operator!=(const StridedMemrefIterator& other) const { return !(*this == other); }

 private:
  /// Pointer to the single element in the zero-ranked memref.
  T* elt;
};

//===----------------------------------------------------------------------===//
// DynamicMemRefType type.
//===----------------------------------------------------------------------===//
template<typename T>
class DynamicMemRefIterator;

// A reference to one of the StridedMemRef types.
template<typename T>
class DynamicMemRefType {
 public:
  int64_t rank;
  T* basePtr;
  T* data;
  int64_t offset;
  const int64_t* sizes;
  const int64_t* strides;

  explicit DynamicMemRefType(const StridedMemRefType<T, 0>& memRef)
      : rank(0),
        basePtr(memRef.basePtr),
        data(memRef.data),
        offset(memRef.offset),
        sizes(nullptr),
        strides(nullptr) {}
  template<int N>
  explicit DynamicMemRefType(const StridedMemRefType<T, N>& memRef)
      : rank(N),
        basePtr(memRef.basePtr),
        data(memRef.data),
        offset(memRef.offset),
        sizes(memRef.sizes),
        strides(memRef.strides) {}
  explicit DynamicMemRefType(const UnrankedMemRefType<T>& memRef) : rank(memRef.rank) {
    auto* desc = static_cast<StridedMemRefType<T, 1>*>(memRef.descriptor);
    basePtr = desc->basePtr;
    data = desc->data;
    offset = desc->offset;
    sizes = rank == 0 ? nullptr : desc->sizes;
    strides = sizes + rank;
  }

  template<typename Range, typename sfinae = decltype(std::declval<Range>().begin())>
  T& operator[](Range&& indices) {
    assert(indices.size() == rank && "indices should match rank in memref subscript");
    if (rank == 0) return data[offset];

    int64_t curOffset = offset;
    for (int dim = rank - 1; dim >= 0; --dim) {
      int64_t currentIndex = *(indices.begin() + dim);
      assert(currentIndex < sizes[dim] && "Index overflow");
      curOffset += currentIndex * strides[dim];
    }
    return data[curOffset];
  }

  DynamicMemRefIterator<T> begin() { return {*this, offset}; }
  DynamicMemRefIterator<T> end() { return {*this, -1}; }

  // This operator[] is extremely slow and only for sugaring purposes.
  DynamicMemRefType<T> operator[](int64_t idx) {
    assert(rank > 0 && "can't make a subscript of a zero ranked array");

    DynamicMemRefType<T> res(*this);
    --res.rank;
    res.offset += idx * res.strides[0];
    ++res.sizes;
    ++res.strides;
    return res;
  }

  // This operator* can be used in conjunction with the previous operator[] in
  // order to access the underlying value in case of zero-ranked memref.
  T& operator*() {
    assert(rank == 0 && "not a zero-ranked memRef");
    return data[offset];
  }
};

/// Iterate over all elements in a dynamic memref.
template<typename T>
class DynamicMemRefIterator {
 public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using reference = T&;

  DynamicMemRefIterator(DynamicMemRefType<T>& descriptor, int64_t offset = 0)
      : offset(offset), descriptor(&descriptor) {
    indices.resize(descriptor.rank, 0);
  }

  DynamicMemRefIterator<T>& operator++() {
    if (descriptor->rank == 0) {
      offset = -1;
      return *this;
    }

    int dim = descriptor->rank - 1;

    while (dim >= 0 && indices[dim] == (descriptor->sizes[dim] - 1)) {
      offset -= indices[dim] * descriptor->strides[dim];
      indices[dim] = 0;
      --dim;
    }

    if (dim < 0) {
      offset = -1;
      return *this;
    }

    ++indices[dim];
    offset += descriptor->strides[dim];
    return *this;
  }

  reference operator*() { return descriptor->data[offset]; }
  pointer operator->() { return &descriptor->data[offset]; }

  const std::vector<int64_t>& getIndices() { return indices; }

  bool operator==(const DynamicMemRefIterator& other) const {
    return other.offset == offset && other.descriptor == descriptor;
  }

  bool operator!=(const DynamicMemRefIterator& other) const { return !(*this == other); }

 private:
  /// Offset in the buffer. This can be derived from the indices and the
  /// descriptor.
  int64_t offset = 0;

  /// Array of indices in the multi-dimensional memref.
  std::vector<int64_t> indices = {};

  /// Descriptor for the dynamic memref.
  DynamicMemRefType<T>* descriptor;
};

namespace impl {
static inline void printSpace(std::ostream& os, int count) {
  for (int i = 0; i < count; ++i) { os << ' '; }
}

template<typename T>
struct MemRefDataPrinter {
  static void print(std::ostream& os, T* base, int64_t dim, int64_t rank, int64_t offset,
                    const int64_t* sizes, const int64_t* strides);
  static void printFirst(std::ostream& os, T* base, int64_t dim, int64_t rank, int64_t offset,
                         const int64_t* sizes, const int64_t* strides);
  static void printLast(std::ostream& os, T* base, int64_t dim, int64_t rank, int64_t offset,
                        const int64_t* sizes, const int64_t* strides);
};

template<typename T>
void MemRefDataPrinter<T>::printFirst(std::ostream& os, T* base, int64_t dim, int64_t rank,
                                      int64_t offset, const int64_t* sizes,
                                      const int64_t* strides) {
  os << "[";
  print(os, base, dim - 1, rank, offset, sizes + 1, strides + 1);
  // If single element, close square bracket and return early.
  if (sizes[0] <= 1) {
    os << "]";
    return;
  }
  os << ", ";
  if (dim > 1) os << "\n";
}

template<typename T>
void MemRefDataPrinter<T>::print(std::ostream& os, T* base, int64_t dim, int64_t rank,
                                 int64_t offset, const int64_t* sizes, const int64_t* strides) {
  if (dim == 0) {
    os << base[offset];
    return;
  }
  printFirst(os, base, dim, rank, offset, sizes, strides);
  for (unsigned i = 1; i + 1 < sizes[0]; ++i) {
    printSpace(os, rank - dim + 1);
    print(os, base, dim - 1, rank, offset + i * strides[0], sizes + 1, strides + 1);
    os << ", ";
    if (dim > 1) os << "\n";
  }
  if (sizes[0] <= 1) return;
  printLast(os, base, dim, rank, offset, sizes, strides);
}

template<typename T>
void MemRefDataPrinter<T>::printLast(std::ostream& os, T* base, int64_t dim, int64_t rank,
                                     int64_t offset, const int64_t* sizes, const int64_t* strides) {
  printSpace(os, rank - dim + 1);
  print(os, base, dim - 1, rank, offset + (sizes[0] - 1) * (*strides), sizes + 1, strides + 1);
  os << "]";
}

template<typename T, typename StreamType>
void printMemRefMetaData(StreamType& os, const DynamicMemRefType<T>& v) {
  // Make the printed pointer format platform independent by casting it to an
  // integer and manually formatting it to a hex with prefix as tests expect.
  os << "base@ = " << std::hex << std::showbase << reinterpret_cast<std::intptr_t>(v.data)
     << std::dec << std::noshowbase << " rank = " << v.rank << " offset = " << v.offset;
  auto print = [&](const int64_t* ptr) {
    if (v.rank == 0) return;
    os << ptr[0];
    for (int64_t i = 1; i < v.rank; ++i) os << ", " << ptr[i];
  };
  os << " sizes = [";
  print(v.sizes);
  os << "] strides = [";
  print(v.strides);
  os << "]";
}

template<typename T>
void printMemRef(const DynamicMemRefType<T>& m) {
  printMemRefMetaData(std::cout, m);
  std::cout << " data = \n";
  if (m.rank == 0) std::cout << "[";
  MemRefDataPrinter<T>::print(std::cout, m.data, m.rank, m.rank, m.offset, m.sizes, m.strides);
  if (m.rank == 0) std::cout << "]";
  std::cout << '\n' << std::flush;
}

template<typename T>
void printMemRef(UnrankedMemRefType<T>& m) {
  std::cout << "Unranked Memref ";
  printMemRef(DynamicMemRefType<T>(m));
}

extern "C" void _printMemrefF32(UnrankedMemRefType<float>* m);
}  // namespace impl

extern "C" void printMemrefF32(int64_t rank, void* ptr);

template<typename T>
DynamicMemRefType<T> wrapToIndexableTensor(int64_t rank, void* ptr) {
  UnrankedMemRefType<float> descriptor = {rank, ptr};
  return DynamicMemRefType<float>(descriptor);
}

typedef std::initializer_list<int> At;

// image class
class Image {};

// utils for create image and memref. Alloc and Dealloc.

}  // namespace rt
}  // namespace nncv

#endif  //! NNCV_LIB_NNCV_RT_DATA_TYPE_HPP_