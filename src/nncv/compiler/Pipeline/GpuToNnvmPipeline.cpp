#include "mlir/Conversion/AffineToStandard/AffineToStandard.h"
#include "mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/Conversion/FuncToLLVM/ConvertFuncToLLVMPass.h"
#include "mlir/Conversion/GPUCommon/GPUCommonPass.h"
#include "mlir/Conversion/GPUToNVVM/GPUToNVVMPass.h"
#include "mlir/Conversion/IndexToLLVM/IndexToLLVM.h"
#include "mlir/Conversion/MathToLLVM/MathToLLVM.h"
#include "mlir/Conversion/MemRefToLLVM/MemRefToLLVM.h"
#include "mlir/Conversion/NVGPUToNVVM/NVGPUToNVVM.h"
#include "mlir/Conversion/NVVMToLLVM/NVVMToLLVM.h"
#include "mlir/Conversion/ReconcileUnrealizedCasts/ReconcileUnrealizedCasts.h"
#include "mlir/Conversion/SCFToControlFlow/SCFToControlFlow.h"
#include "mlir/Conversion/VectorToLLVM/ConvertVectorToLLVMPass.h"
#include "mlir/Conversion/VectorToSCF/VectorToSCF.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/GPU/IR/GPUDialect.h"
#include "mlir/Dialect/GPU/Transforms/Passes.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/Linalg/Passes.h"
#include "mlir/Dialect/MemRef/Transforms/Passes.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassOptions.h"
#include "mlir/Transforms/Passes.h"
#include "nncv/compiler/Pipeline/GpuToNnvmPipeline.hpp"

using namespace mlir;

namespace nncv::compiler {
namespace pipeline {

namespace {
//===----------------------------------------------------------------------===//
// Common pipeline
//===----------------------------------------------------------------------===//
void buildCommonPassPipeline(OpPassManager& pm,
                             const ::nncv::compiler::pipeline::GPUToNVVMPipelineOptions& options) {
  pm.addPass(createConvertNVGPUToNVVMPass());
  pm.addPass(createGpuKernelOutliningPass());
  pm.addPass(createConvertVectorToSCFPass());
  pm.addPass(createConvertSCFToCFPass());
  pm.addPass(createConvertNVVMToLLVMPass());
  pm.addPass(createConvertFuncToLLVMPass());
  pm.addPass(memref::createExpandStridedMetadataPass());

  GpuNVVMAttachTargetOptions nvvmTargetOptions;
  nvvmTargetOptions.triple = options.cubinTriple;
  nvvmTargetOptions.chip = options.cubinChip;
  nvvmTargetOptions.features = options.cubinFeatures;
  nvvmTargetOptions.optLevel = options.optLevel;
  pm.addPass(createGpuNVVMAttachTarget(nvvmTargetOptions));
  pm.addPass(createLowerAffinePass());
  pm.addPass(createArithToLLVMConversionPass());
  ConvertIndexToLLVMPassOptions convertIndexToLLVMPassOpt;
  convertIndexToLLVMPassOpt.indexBitwidth = options.indexBitWidth;
  pm.addPass(createConvertIndexToLLVMPass(convertIndexToLLVMPassOpt));
  pm.addPass(createCanonicalizerPass());
  pm.addPass(createCSEPass());
}

//===----------------------------------------------------------------------===//
// GPUModule-specific stuff.
//===----------------------------------------------------------------------===//
void buildGpuPassPipeline(OpPassManager& pm,
                          const ::nncv::compiler::pipeline::GPUToNVVMPipelineOptions& options) {
  pm.addNestedPass<gpu::GPUModuleOp>(createStripDebugInfoPass());
  ConvertGpuOpsToNVVMOpsOptions opt;
  opt.useBarePtrCallConv = options.kernelUseBarePtrCallConv;
  opt.indexBitwidth = options.indexBitWidth;
  pm.addNestedPass<gpu::GPUModuleOp>(createConvertGpuOpsToNVVMOps(opt));
  pm.addNestedPass<gpu::GPUModuleOp>(createCanonicalizerPass());
  pm.addNestedPass<gpu::GPUModuleOp>(createCSEPass());
  pm.addNestedPass<gpu::GPUModuleOp>(createReconcileUnrealizedCastsPass());
}

//===----------------------------------------------------------------------===//
// Host Post-GPU pipeline
//===----------------------------------------------------------------------===//
void buildHostPostPipeline(OpPassManager& pm,
                           const ::nncv::compiler::pipeline::GPUToNVVMPipelineOptions& options) {
  GpuToLLVMConversionPassOptions opt;
  opt.hostBarePtrCallConv = options.hostUseBarePtrCallConv;
  opt.kernelBarePtrCallConv = options.kernelUseBarePtrCallConv;
  pm.addPass(createGpuToLLVMConversionPass(opt));

  GpuModuleToBinaryPassOptions gpuModuleToBinaryPassOptions;
  gpuModuleToBinaryPassOptions.compilationTarget = options.cubinFormat;
  pm.addPass(createGpuModuleToBinaryPass(gpuModuleToBinaryPassOptions));
  pm.addPass(createConvertMathToLLVMPass());
  pm.addPass(createCanonicalizerPass());
  pm.addPass(createCSEPass());
  pm.addPass(createReconcileUnrealizedCastsPass());
}
}  // namespace

void buildLowerToNVVMPassPipeline(
    OpPassManager& pm, const ::nncv::compiler::pipeline::GPUToNVVMPipelineOptions& options) {
  // Common pipelines
  buildCommonPassPipeline(pm, options);

  // GPUModule-specific stuff
  buildGpuPassPipeline(pm, options);

  // Host post-GPUModule-specific stuff
  buildHostPostPipeline(pm, options);
}

}  // namespace pipeline
}  // namespace nncv::compiler
