#ifndef NNCV_TENSOR_HPP
#define NNCV_TENSOR_HPP
#pragma once

#include <iostream>

#include "nncv/core/common/atomic.hpp"
#include "nncv/core/common/device.hpp"

namespace nncv {

enum TensorDataLayoutType : int {
  kNCHW = 0,
};

struct NNCV_EXPORT_DLL Shape {
  Shape(Shape&& _lhs)
      : n(std::move(_lhs.n)), c(std::move(_lhs.c)), h(std::move(_lhs.h)), w(std::move(_lhs.w)) {}
  Shape(int _w) : n(-1), c(-1), h(-1), w(_w), dims(1) {}
  Shape(int _h, int _w) : n(-1), c(-1), h(_h), w(_w), dims(2) {}
  Shape(int _c, int _h, int _w) : n(-1), c(_c), h(_h), w(_w), dims(3) {}
  Shape(int _n, int _c, int _h, int _w) : n(_n), c(_c), h(_h), w(_w), dims(4) {}

  std::ostream& operator<<(std::ostream& output) {
    output << "Tensor Shape[" << n << ", " << c << ", " << h << ", " << w << "], dims=" << dims
           << "\n";
    return output;
  }

  int operator[](int idx) {
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
  NNCV_FORCE_INLINE Tensor(int _w, size_t _size, const Device& _device = Device(DeviceType::kHost))
      : m_shape(_w), m_element_size(_size), m_device(_device) {}

  NNCV_FORCE_INLINE Tensor(int _h, int _w, size_t _size,
                           const Device& _device = Device(DeviceType::kHost))
      : m_shape(_h, _w), m_element_size(_size), m_device(_device) {}

  NNCV_FORCE_INLINE Tensor(int _c, int _h, int _w, size_t _size,
                           const Device& _device = Device(DeviceType::kHost))
      : m_shape(_c, _h, _w), m_element_size(_size), m_device(_device) {}

  NNCV_FORCE_INLINE Tensor(int _n, int _c, int _h, int _w, size_t _size,
                           const Device& _device = Device(DeviceType::kHost))
      : m_shape(_n, _c, _h, _w), m_element_size(_size), m_device(_device) {}

  NNCV_FORCE_INLINE void to(const std::string& _device_str) {
    // TODO
    // using device pool, to search if there has such device.
    // if has. Device = DevicePool.find(_device_str);
  }

  NNCV_FORCE_INLINE void RefIncrease() { NNCV_ATOMIC_ADD(m_ref, 1); }
  NNCV_FORCE_INLINE bool RefDecrease() {
    (*m_ref)--;
    if (*m_ref == 0)
      return true;  //! if m_ref == 0, this tensor should be freed by VM's memory manager
    return false;
  }

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

 private:
  atomic_int m_ref;
  size_t m_element_size;
  void* m_data_ptr;
  Shape m_shape;
  Device m_device;
  TensorDataLayoutType m_layout;
};

}  // namespace nncv

#endif