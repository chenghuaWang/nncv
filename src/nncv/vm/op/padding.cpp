#include "nncv/vm/op/padding.hpp"

namespace nncv {
namespace vm {
namespace op {
template<typename T>
void copy_make_border_padding(const Tensor& src, Tensor& dst, const PaddingType& type, T v,
                              bool vm_involved) {}
}  // namespace op
}  // namespace vm
}  // namespace nncv