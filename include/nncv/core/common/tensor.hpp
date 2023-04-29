#ifndef NNCV_TENSOR_HPP
#define NNCV_TENSOR_HPP

#pragma once

#include "nncv/core/common/device.hpp"

namespace nncv {

enum TensorDataLayoutType : int {
  kNCHW = 0,
};

template<int dims = 4>
struct EXPORT_DLL Shape {
  Shape(Shape&& _lhs) : m_last_dim(std::move(_lhs.m_last_dim)), m_data(std::move(_lhs.m_data)) {}
  int m_last_dim = -1;
  int m_data[dims];
};

template<typename value_type, int dims = 4, DeviceType device_type = DeviceType::kHost>
class EXPORT_DLL Tensor {
 public:
  Tensor() : m_data_ptr(nullptr), m_shape(dims), m_device_type(device_type) {}

 private:
  value_type* m_data_ptr;
  Shape<dims> m_shape;
  DeviceType m_device_type;
  TensorDataLayoutType m_layout = TensorDataLayoutType::kNCHW;
};

template<int dims>
EXPORT_DLL Shape<dims> MakeShape2D(int _1, int _2) {
  Shape<dims> ans;
  ans.m_last_dim = _2;
  ans.m_data[0] = _1;
  ans.m_data[1] = _2;
  return ans;
}

template<int dims>
EXPORT_DLL Shape<dims> MakeShape3D(int _1, int _2, int _3) {
  Shape<dims> ans;
  ans.m_last_dim = _3;
  ans.m_data[0] = _1;
  ans.m_data[1] = _2;
  ans.m_data[2] = _3;
  return ans;
}

template<int dims>
EXPORT_DLL Shape<dims> MakeShape4D(int _1, int _2, int _3, int _4) {
  Shape<dims> ans;
  ans.m_last_dim = _4;
  ans.m_data[0] = _1;
  ans.m_data[1] = _2;
  ans.m_data[2] = _3;
  ans.m_data[3] = _4;
  return ans;
}

}  // namespace nncv

#endif