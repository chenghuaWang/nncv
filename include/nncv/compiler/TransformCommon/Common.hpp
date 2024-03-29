#pragma once
#ifndef NNCV_C_TRANSFORM_C_COMMON_HPP_
#define NNCV_C_TRANSFORM_C_COMMON_HPP_

#include "mlir/Dialect/Transform/IR/TransformInterfaces.h"
#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/IR/ImplicitLocOpBuilder.h"

using TransformBuilderFunc = std::function<void(mlir::ImplicitLocOpBuilder&, mlir::Value)>;

namespace mlir {
namespace nncv {

transform::TransformOpInterface createTransformRegion(mlir::FunctionOpInterface entery,
                                                      TransformBuilderFunc func);

void transformHoistingSubsetFunc(mlir::ImplicitLocOpBuilder& b, mlir::Value funcOp);

void createTransformDecomposeLinalg(mlir::ImplicitLocOpBuilder& builder, mlir::Value v);

void _createTransformMapToGpuBlock(mlir::ImplicitLocOpBuilder& builder, mlir::Value v,
                                   int64_t blockX, int64_t blockY, int64_t blockZ,
                                   bool genGpuLaunch);

transform::TransformOpInterface createRegionTransformMapToGpuBlock(mlir::FunctionOpInterface entry,
                                                                   int64_t blockX, int64_t blockY,
                                                                   int64_t blockZ,
                                                                   bool genGpuLaunch);

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_TRANSFORM_C_COMMON_HPP_