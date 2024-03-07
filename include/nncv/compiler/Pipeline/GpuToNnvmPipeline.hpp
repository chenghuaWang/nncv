#ifndef NNCV_C_GPU_NNVM_PIPELINE_HPP_
#define NNCV_C_GPU_NNVM_PIPELINE_HPP_

#include <cstdint>
#include <optional>
#include <string>
#include "mlir/Pass/PassOptions.h"

namespace nncv::compiler {
namespace pipeline {

struct GPUToNVVMPipelineOptions {
  int64_t indexBitWidth = 64;
  std::string cubinTriple = "nvptx64-nvidia-cuda";
  std::string cubinChip = "sm_50";
  std::string cubinFeatures = "+ptx60";
  std::string cubinFormat = "fatbin";
  int optLevel = 2;
  bool kernelUseBarePtrCallConv = false;
  bool hostUseBarePtrCallConv = false;
};

void buildLowerToNVVMPassPipeline(
    mlir::OpPassManager& pm, const ::nncv::compiler::pipeline::GPUToNVVMPipelineOptions& options);

}  // namespace pipeline
}  // namespace nncv::compiler

#endif  //! NNCV_C_GPU_NNVM_PIPELINE_HPP_