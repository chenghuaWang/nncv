#include "nncv/vm/io/image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

namespace nncv {
namespace vm {
namespace io {

Tensor ImageRead(const std::string& _path, const ImageProcessBackend& _backend) {
  int w, h, c;
  void* data;
  switch (_backend) {
    case kStbImage: {
      data = (void*)stbi_load(_path.c_str(), &w, &h, &c, 0);
      Tensor ret = Tensor::Create(0, c, h, w, NNCV_INT8, kHost);
      // TODO reformat data to layouts [N = 0, C, H, W], for loop with openmp.
      free(data);
      return ret;
      break;
    }
    case kOpenCV: {
      // TODO
      break;
    }
  }
  return Tensor::Create(0, 0, 0, 0, NNCV_INT8, nullptr, kHost);
}

bool ImageWrite(const std::string& _path, const Tensor& _image,
                const ImageProcessBackend& _backend) {
  // TODO need add stb_image_write.h to this project.
  return false;
}
}  // namespace io
}  // namespace vm
}  // namespace nncv