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

namespace mlir {
#define GEN_PASS_REGISTRATION
#include "Conversion/Passes.h.inc"
}  // namespace mlir

#endif  //! NNCV_ATEN_CONVERSION_PASSES_H