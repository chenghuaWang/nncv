#ifndef NNCV_ATEN_CONVERSION_PASSES_H
#define NNCV_ATEN_CONVERSION_PASSES_H

#include "nncv/compiler/Conversion/ConvOptimize/ConvertOptimizedConv2dToAffine.hpp"
#include "nncv/compiler/Conversion/ConvOptimize/OptimizeConv2dUsingCB.hpp"
#include "nncv/compiler/Conversion/ConvOptimize/OptimizeConv2dUsingWinograd.hpp"
#include "nncv/compiler/Conversion/ConvOptimize/Conv2dTile.hpp"

#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptDefault.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/BatchMatMulOptVec.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptParallelVec.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptVec.hpp"
#include "nncv/compiler/Conversion/MatMulOptimize/MatMul2NvMMA.hpp"

#include "nncv/compiler/Conversion/AtenToMlir/AtenToMlir.h"
#include "nncv/compiler/Conversion/AtenToMlir/AtenMlirToLlvm.hpp"

#include "nncv/compiler/Conversion/Vectorization/Vec.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/LinalgGenericTile.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/LinalgPoolTile.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/CastAwayTensorLeadingOneDim.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/RegisterLinalgOps.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/OneShotTiling.hpp"
#include "nncv/compiler/Conversion/LinalgOptimize/DecomposeTransGen.hpp"

#include "nncv/compiler/Conversion/Transforms/NestedTransformErasePass.hpp"
#include "nncv/compiler/Conversion/Vectorization/VectorizePad.hpp"
#include "nncv/compiler/Conversion/Vectorization/OptimizeInsertExtractSlices.hpp"

#include "nncv/compiler/Conversion/CodeGen/LlvmCpu/ModernTile.hpp"
#include "nncv/compiler/Conversion/CodeGen/LlvmCpu/ModernVec.hpp"
#include "nncv/compiler/Conversion/CodeGen/LlvmCpu/PrepareModernVec.hpp"
#include "nncv/compiler/Conversion/CodeGen/LlvmCpu/PeelAfterTile.hpp"
#include "nncv/compiler/Conversion/CodeGen/LlvmCpu/LoweringScfForAllToParallel.hpp"

#include "nncv/compiler/Conversion/CodeGen/LlvmGpu/ModernTileGpu.hpp"
#include "nncv/compiler/Conversion/CodeGen/LlvmGpu/ModernVecGpu.hpp"
#include "nncv/compiler/Conversion/CodeGen/LlvmGpu/PrepareModernVecGpu.hpp"

#include "nncv/compiler/Conversion/Transforms/RemoveSelfMemRefCopy.hpp"
#include "nncv/compiler/Conversion/Transforms/SplitParams.hpp"
#include "nncv/compiler/Conversion/Transforms/SplitParamsFlatArray.hpp"
#include "nncv/compiler/Conversion/Transforms/RegisterMemToGpu.hpp"

namespace mlir {
#define GEN_PASS_REGISTRATION
#include "Conversion/Passes.h.inc"
}  // namespace mlir

namespace mlir::nncv {
void populateVectorTransferTensorSliceTransforms(mlir::RewritePatternSet& patterns,
                                                 mlir::PatternBenefit benefit = 1);
}

namespace mlir::nncv::codegen_llvm_cpu {
void addTilePassPipeline(mlir::PassManager& pm);
}  // namespace mlir::nncv::codegen_llvm_cpu

#endif  //! NNCV_ATEN_CONVERSION_PASSES_H