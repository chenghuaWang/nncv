#include "libnncv/DataType.hpp"
#include "libnncv/SystemIo.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <malloc.h>
#include <chrono>
#include <stdlib.h>

using namespace std::chrono;

using namespace nncv::rt;

#define B 1
#define C 3
#define H 256
#define W 256

extern "C" {
void _mlir_ciface_forward(
    /*output*/ MemRefDescriptor<float, 2>* dst,
    /*input*/ MemRefDescriptor<float, 4>* src,
    /*params*/ void*);
}

int main() {
  // 1. read params
  MemRefFlatArray params(dataType::kFloat32);
  if (!params.read("model.bin")) { return -1; }

  // 2. create input and output
  float* _dst_data_ptr = (float*)malloc(sizeof(float) * (long long)1 * 1000);
  float* _src_data_ptr = (float*)malloc(sizeof(float) * (long long)B * C * H * W);

  // read image
  int width, height, channels;
  unsigned char* data = stbi_load("cat_256x256.jpg", &width, &height, &channels, 0);
  std::cout << width << " " << height << " " << channels << std::endl;
  for (int i = 0; i < B * C * H * W; ++i) _src_data_ptr[i] = (float)data[i] / 255.f;

  // transform HxWxC to CxHxW
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      unsigned char* pixelOffset = data + (j + i * width) * channels;
      unsigned char r = pixelOffset[0];
      unsigned char g = pixelOffset[1];
      unsigned char b = pixelOffset[2];

      // store to nncv's format
      _src_data_ptr[H * W * 0 + j + i * width] = r / 255.f;
      _src_data_ptr[H * W * 1 + j + i * width] = g / 255.f;
      _src_data_ptr[H * W * 2 + j + i * width] = b / 255.f;
    }
  }

  stbi_image_free(data);

  // normalize
  for (int b = 0; b < B; ++b) {
    for (int c = 0; c < C; ++c) {
      for (int l = 0; l < H * W; ++l) {
        switch (c) {
          case 0: {
            _src_data_ptr[c * H * W + l] = (_src_data_ptr[c * H * W + l] - 0.485f) / 0.229f;
            break;
          }
          case 1: {
            _src_data_ptr[c * H * W + l] = (_src_data_ptr[c * H * W + l] - 0.456f) / 0.224f;
            break;
          }
          case 2: {
            _src_data_ptr[c * H * W + l] = (_src_data_ptr[c * H * W + l] - 0.406f) / 0.225f;
            break;
          }
        }
      }
    }
  }

  MemRefDescriptor<float, 2> dst = {
      _dst_data_ptr,  // allocated
      _dst_data_ptr,  // aligned
      0,              // offset
      {1, 1000},      // sizes[N]
      {1000, 1},      // strides[N]
  };

  MemRefDescriptor<float, 4> src = {
      _src_data_ptr,             // allocated
      _src_data_ptr,             // aligned
      0,                         // offset
      {B, C, H, W},              // sizes[N]
      {C * H * W, H * W, H, 1},  // strides[N]
  };

  auto startTime = system_clock::now();
  _mlir_ciface_forward(&dst, &src, params.get());
  auto endTime = system_clock::now();
  auto tt = duration_cast<milliseconds>(endTime - startTime);
  std::cout << "Time: " << tt.count() << "ms" << std::endl;

  auto dmt = nncv::rt::wrapToIndexableTensor<float>(2, &dst);

  // max
  float max = -100.f;
  int idx = 0;
  for (int i = 0; i < 1000; ++i) {
    if (dmt[At{0, i}] > max) {
      max = dmt[At{0, i}];
      idx = i;
    }
  }

  //   nncv::rt::printMemrefF32(2, &dst);
  std::cout << idx << std::endl;

  free(_dst_data_ptr);
  free(_src_data_ptr);
}
