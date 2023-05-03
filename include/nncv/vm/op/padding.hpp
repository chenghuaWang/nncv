#ifndef NNCV_PADDING_HPP
#define NNCV_PADDING_HPP

#include "nncv/core/common/tensor.hpp"

namespace nncv {
namespace vm {
namespace op {

enum PaddingType : int {

};

template<typename T>
void copy_make_border_padding(const Tensor& src, Tensor& dst, const PaddingType& type, T v,
                              bool vm_involved);

}  // namespace op
}  // namespace vm
}  // namespace nncv

#endif