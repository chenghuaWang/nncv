#ifndef NNCV_TENSOR_HPP
#define NNCV_TENSOR_HPP
#pragma once

#include <iostream>

#include "nncv/core/common/atomic.hpp"
#include "nncv/core/common/device.hpp"

#define NNCV_FLOAT16 2
#define NNCV_FLOAT32 4
#define NNCV_FLOAT64 8
#define NNCV_INT8 1
#define NNCV_INT16 2
#define NNCV_INT32 4
#define NNCV_INT64 8

namespace nncv {

enum TensorDataLayoutType : int {
  kNCHW = 0,
};

struct NNCV_EXPORT_DLL Shape {
  NNCV_FORCE_INLINE Shape(Shape&& _lhs)
      : n(std::move(_lhs.n)), c(std::move(_lhs.c)), h(std::move(_lhs.h)), w(std::move(_lhs.w)) {}
  NNCV_FORCE_INLINE Shape(int _w) : n(-1), c(-1), h(-1), w(_w), dims(1) {}
  NNCV_FORCE_INLINE Shape(int _h, int _w) : n(-1), c(-1), h(_h), w(_w), dims(2) {}
  NNCV_FORCE_INLINE Shape(int _c, int _h, int _w) : n(-1), c(_c), h(_h), w(_w), dims(3) {}
  NNCV_FORCE_INLINE Shape(int _n, int _c, int _h, int _w) : n(_n), c(_c), h(_h), w(_w), dims(4) {}

  std::ostream& operator<<(std::ostream& output) const {
    output << "Tensor Shape[" << n << ", " << c << ", " << h << ", " << w << "], dims=" << dims
           << "\n";
    return output;
  }

  NNCV_FORCE_INLINE int operator[](int idx) const {
    switch (idx) {
      case 0: return n;
      case 1: return c;
      case 2: return h;
      case 3: return w;
      default: return -1;
    }
  }

  int n, c, h, w;
  int dims;
};

/**
 * @brief Tensor is just a abstraction here. True memory alloc is in VM stage.
 *
 */
class NNCV_EXPORT_DLL Tensor {
 public:
  NNCV_FORCE_INLINE Tensor(int _w, size_t _size, const Device& _device = Device(DeviceType::kHost))
      : m_force_no_ref(false),
        m_data_ptr(nullptr),
        m_shape(_w),
        m_element_size(_size),
        m_device(_device),
        m_ref(nullptr) {}

  NNCV_FORCE_INLINE Tensor(int _h, int _w, size_t _size,
                           const Device& _device = Device(DeviceType::kHost))
      : m_force_no_ref(false),
        m_data_ptr(nullptr),
        m_shape(_h, _w),
        m_element_size(_size),
        m_device(_device),
        m_ref(nullptr) {}

  NNCV_FORCE_INLINE Tensor(int _c, int _h, int _w, size_t _size,
                           const Device& _device = Device(DeviceType::kHost))
      : m_force_no_ref(false),
        m_data_ptr(nullptr),
        m_shape(_c, _h, _w),
        m_element_size(_size),
        m_device(_device),
        m_ref(nullptr) {}

  NNCV_FORCE_INLINE Tensor(int _n, int _c, int _h, int _w, size_t _size,
                           const Device& _device = Device(DeviceType::kHost))
      : m_force_no_ref(false),
        m_data_ptr(nullptr),
        m_shape(_n, _c, _h, _w),
        m_element_size(_size),
        m_device(_device),
        m_ref(nullptr) {}

  NNCV_FORCE_INLINE Tensor(int _w, size_t _size, void* _ptr,
                           const Device& _device = Device(DeviceType::kHost))
      : m_force_no_ref(true),
        m_data_ptr(_ptr),
        m_shape(_w),
        m_element_size(_size),
        m_device(_device),
        m_ref(nullptr) {}

  NNCV_FORCE_INLINE Tensor(int _h, int _w, size_t _size, void* _ptr,
                           const Device& _device = Device(DeviceType::kHost))
      : m_force_no_ref(true),
        m_data_ptr(_ptr),
        m_shape(_h, _w),
        m_element_size(_size),
        m_device(_device),
        m_ref(nullptr) {}

  NNCV_FORCE_INLINE Tensor(int _c, int _h, int _w, size_t _size, void* _ptr,
                           const Device& _device = Device(DeviceType::kHost))
      : m_force_no_ref(true),
        m_data_ptr(_ptr),
        m_shape(_c, _h, _w),
        m_element_size(_size),
        m_device(_device),
        m_ref(nullptr) {}

  NNCV_FORCE_INLINE Tensor(int _n, int _c, int _h, int _w, size_t _size, void* _ptr,
                           const Device& _device = Device(DeviceType::kHost))
      : m_force_no_ref(true),
        m_data_ptr(_ptr),
        m_shape(_n, _c, _h, _w),
        m_element_size(_size),
        m_device(_device),
        m_ref(nullptr) {}

  NNCV_FORCE_INLINE void to(const std::string& _device_str) {
    // TODO
    // using device pool, to search if there has such device.
    // if has. Device = DevicePool.find(_device_str);
  }

  NNCV_FORCE_INLINE void RefIncrease() { NNCV_ATOMIC_ADD(m_ref, 1); }
  NNCV_FORCE_INLINE bool RefDecrease() {
    NNCV_ATOMIC_ADD(m_ref, -1);
    if (m_ref == 0)
      return true;  //! if m_ref == 0, this tensor should be freed by VM's memory manager
    return false;
  }

  NNCV_FORCE_INLINE const Shape& GetConstShape() const { return m_shape; }

  /**
   * Operator overload Section.
   *
   */

  template<typename T>
  NNCV_FORCE_INLINE operator T*() {
    if (m_data_ptr == nullptr) return nullptr;
    return (T*)m_data_ptr;
  }

  template<typename T>
  NNCV_FORCE_INLINE operator const T*() const {
    if (m_data_ptr == nullptr) return nullptr;
    return (const T*)m_data_ptr;
  }

  template<typename T>
  NNCV_FORCE_INLINE T& at(size_t idx) {
    return ((T*)m_data_ptr)[idx];
  }

  template<typename T>
  NNCV_FORCE_INLINE const T& at(size_t idx) const {
    return ((const T*)m_data_ptr)[idx];
  }

  NNCV_FORCE_INLINE float& operator[](size_t idx) { return ((float*)m_data_ptr)[idx]; }

  NNCV_FORCE_INLINE const float& operator[](size_t idx) const {
    return ((const float*)m_data_ptr)[idx];
  }

  template<typename T>
  NNCV_FORCE_INLINE Tensor& operator<<(T _value) {
    ((T*)m_data_ptr)[__iter_pointer++] = _value;
    return *this;
  }

  NNCV_FORCE_INLINE bool Empty() const { return (m_data_ptr == nullptr) ? true : false; }

  /**
   * Slice Tensor Section
   *
   * Batch Wise, Channel wise, Column and Row wise.
   *
   * numpy like [a:b] slice functions.
   *
   */

  // TODO This function not work before copy move function of Tensor is setted.
  NNCV_FORCE_INLINE const Tensor Batch(int idx) const {
    void* new_ptr = (void*)((unsigned char*)m_data_ptr
                            + (size_t)m_shape.w * m_shape.h * m_shape.c * m_element_size);
    return Tensor(1, m_shape.c, m_shape.h, m_shape.w, m_element_size, new_ptr, m_device);
  }

  // TODO This function not work before copy move function of Tensor is setted.
  NNCV_FORCE_INLINE Tensor Batch(int idx) {
    void* new_ptr = (void*)((unsigned char*)m_data_ptr
                            + (size_t)m_shape.w * m_shape.h * m_shape.c * m_element_size);
    return Tensor(1, m_shape.c, m_shape.h, m_shape.w, m_element_size, new_ptr, m_device);
  }

  template<typename T>
  NNCV_FORCE_INLINE T* GetBatchPtrOn4Dims(int _batch) {
    return (T*)((unsigned char*)m_data_ptr
                + (size_t)m_shape.w * m_shape.h * m_shape.c * m_element_size * _batch);
  }

  template<typename T>
  NNCV_FORCE_INLINE T* GetChannelPtrOn4Dims(int _batch, int _channel) {
    return (T*)((unsigned char*)m_data_ptr
                + (size_t)m_shape.w * m_shape.h * m_shape.c * m_element_size * _batch
                + (size_t)m_shape.w * m_shape.h * m_element_size * _channel);
  }

  template<typename T>
  NNCV_FORCE_INLINE T* GetRowPtrOn4Dims(int _b, int _c, int _h) {
    return (T*)((unsigned char*)m_data_ptr
                + (size_t)m_shape.w * m_shape.h * m_shape.c * m_element_size * _b
                + (size_t)m_shape.w * m_shape.h * m_element_size * _c
                + (size_t)m_shape.w * m_element_size * _h);
  }

  template<typename T>
  NNCV_FORCE_INLINE const T* GetBatchPtrOn4Dims(int _batch) const {
    return (const T*)((unsigned char*)m_data_ptr
                      + (size_t)m_shape.w * m_shape.h * m_shape.c * m_element_size * _batch);
  }

  template<typename T>
  NNCV_FORCE_INLINE const T* GetChannelPtrOn4Dims(int _batch, int _channel) const {
    return (const T*)((unsigned char*)m_data_ptr
                      + (size_t)m_shape.w * m_shape.h * m_shape.c * m_element_size * _batch
                      + (size_t)m_shape.w * m_shape.h * m_element_size * _channel);
  }

  template<typename T>
  NNCV_FORCE_INLINE const T* GetRowPtrOn4Dims(int _b, int _c, int _h) const {
    return (const T*)((unsigned char*)m_data_ptr
                      + (size_t)m_shape.w * m_shape.h * m_shape.c * m_element_size * _b
                      + (size_t)m_shape.w * m_shape.h * m_element_size * _c
                      + (size_t)m_shape.w * m_element_size * _h);
  }

  /**
   * Create function Section.
   *
   * Delete / Free function is no need. For Tensor created by user, `m_force_no_ref` is set to
   * false, this will enable reference counter, which will free memory automatically. For Tensor
   * created by VM, the memory pool maintained by VM will manage memory carefully(`m_force_no_ref`
   * is set to True).
   *
   */
  NNCV_FORCE_INLINE static Tensor Create(int _w, size_t _size,
                                         const Device& _device = Device(DeviceType::kHost)) {}

  NNCV_FORCE_INLINE static Tensor Create(int _h, int _w, size_t _size,
                                         const Device& _device = Device(DeviceType::kHost)) {}

  NNCV_FORCE_INLINE static Tensor Create(int _c, int _h, int _w, size_t _size,
                                         const Device& _device = Device(DeviceType::kHost)) {}

  NNCV_FORCE_INLINE static Tensor Create(int _n, int _c, int _h, int _w, size_t _size,
                                         const Device& _device = Device(DeviceType::kHost)) {}

  NNCV_FORCE_INLINE static Tensor Create(int _w, size_t _size, void* ptr,
                                         const Device& _device = Device(DeviceType::kHost)) {}

  NNCV_FORCE_INLINE static Tensor Create(int _h, int _w, size_t _size, void* ptr,
                                         const Device& _device = Device(DeviceType::kHost)) {}

  NNCV_FORCE_INLINE static Tensor Create(int _c, int _h, int _w, size_t _size, void* ptr,
                                         const Device& _device = Device(DeviceType::kHost)) {}

  NNCV_FORCE_INLINE static Tensor Create(int _n, int _c, int _h, int _w, size_t _size, void* ptr,
                                         const Device& _device = Device(DeviceType::kHost)) {}

 private:
  bool m_force_no_ref;  //! if set to true, it will ignore the m_ref's count
  int* m_ref;
  size_t m_element_size;
  void* m_data_ptr;
  Shape m_shape;
  Device m_device;
  TensorDataLayoutType m_layout;
  // for operator iter
  int __iter_pointer = 0;
};

}  // namespace nncv

#endif