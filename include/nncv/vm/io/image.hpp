#ifndef NNCV_IO_IMAGE_HPP
#define NNCV_IO_IMAGE_HPP

#pragma once

#include "nncv/core/base.hpp"
#include "nncv/core/common/tensor.hpp"

namespace nncv {
namespace vm{
namespace io{

Tensor ImageRead(const std::string& _path);

bool ImageWrite(const std::string& _path, const Tensor& _image);

}
}
}

#endif //! NNCV_IO_IMAGE_HPP