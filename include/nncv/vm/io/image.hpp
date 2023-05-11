#ifndef NNCV_IO_IMAGE_HPP
#define NNCV_IO_IMAGE_HPP

#pragma once

#include "nncv/core/base.hpp"
#include "nncv/core/common/tensor.hpp"

namespace nncv {
namespace vm {
namespace io {

enum ImageProcessBackend : int { kOpenCV = 0, kStbImage = 1 };

#if NNCV_ENABLE_OPENCV == 1
static bool is_opencv_as_backend = true;
#elif NNCV_ENABLE_STB_IMAGE == 1
static bool is_opencv_as_backend = false;
static bool is_stb_image_as_backend = true;
#endif

Tensor ImageRead(const std::string& _path, const ImageProcessBackend& _backend = kStbImage);

bool ImageWrite(const std::string& _path, const Tensor& _image,
                const ImageProcessBackend& _backend = kStbImage);

}  // namespace io
}  // namespace vm
}  // namespace nncv

#endif  //! NNCV_IO_IMAGE_HPP