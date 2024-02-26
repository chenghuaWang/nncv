#include "nncv/compiler/TransformCommon/Common.hpp"
#include "mlir/Dialect/Linalg/TransformOps/LinalgMatchOps.h"
#include "mlir/Dialect/Linalg/TransformOps/LinalgTransformOps.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Transform/IR/TransformDialect.h"
#include "mlir/Dialect/Transform/IR/TransformInterfaces.h"
#include "mlir/Dialect/Transform/IR/TransformOps.h"
#include "mlir/Dialect/Transform/IR/TransformTypes.h"
#include "mlir/IR/Attributes.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Dialect/Transform/LoopExtension/LoopExtensionOps.h"
#include "mlir/Dialect/GPU/TransformOps/GPUTransformOps.h"

namespace mlir {
namespace nncv {

transform::TransformOpInterface createTransformRegion(mlir::FunctionOpInterface entry,
                                                      TransformBuilderFunc func) {
  auto ctx = entry.getContext();
  auto loc = entry.getLoc();
  mlir::OpBuilder builder(ctx);

  builder.setInsertionPointAfter(entry);

  auto TransformModule = builder.create<mlir::ModuleOp>(loc);
  TransformModule->setAttr(mlir::transform::TransformDialect::kWithNamedSequenceAttrName,
                           builder.getUnitAttr());
  Region& TransformModuleRegion = TransformModule.getBodyRegion();
  builder.setInsertionPointToStart(&TransformModuleRegion.front());

  auto AnyOpType = mlir::transform::AnyOpType::get(builder.getContext());
  auto TransformSequence = builder.create<mlir::transform::NamedSequenceOp>(
      loc,
      /*symName=*/
      std::string(transform::TransformDialect::kTransformEntryPointSymbolName.str()),
      /*rootType*/ AnyOpType,
      /*resultTypes=*/TypeRange{},
      /*bodyBuilder=*/[&](OpBuilder& b, Location loc, Value variantH) {
        ImplicitLocOpBuilder ib(loc, b);
        func(ib, variantH);
        b.create<transform::YieldOp>(loc);
      });
  return TransformSequence;
}

void transformHoistingSubsetFunc(mlir::ImplicitLocOpBuilder& builder, mlir::Value funcOp) {
  // Value Loops =
  //     builder.create<mlir::transform::MatchOp>(funcOp, mlir::scf::ForOp::getOperationName());
  // builder.create<mlir::transform::HoistLoopInvariantSubsetsOp>(Loops);
}

void createTransformDecomposeLinalg(mlir::ImplicitLocOpBuilder& builder, mlir::Value v) {
  auto AnyOpType = mlir::transform::AnyOpType::get(builder.getContext());
  ArrayRef<StringRef> opNames = {"linalg.conv_2d_nchw_fchw", "linalg.pooling_nchw_sum",
                                 "linalg.pooling_nchw_max"};
  auto matched = builder.create<transform::MatchOp>(v, opNames);
  builder.create<transform::DecomposeOp>(AnyOpType, matched);
}

void _createTransformMapToGpuBlock(mlir::ImplicitLocOpBuilder& builder, mlir::Value v,
                                   int64_t blockX, int64_t blockY, int64_t blockZ,
                                   bool genGpuLaunch) {
  auto AnyOpType = mlir::transform::AnyOpType::get(builder.getContext());
  auto gridDims = builder.getDenseI64ArrayAttr({blockX, blockY, blockZ});
  builder.create<mlir::transform::MapForallToBlocks>(AnyOpType, v, gridDims, genGpuLaunch);
}

transform::TransformOpInterface createRegionTransformMapToGpuBlock(mlir::FunctionOpInterface entry,
                                                                   int64_t blockX, int64_t blockY,
                                                                   int64_t blockZ,
                                                                   bool genGpuLaunch) {
  auto ctx = entry.getContext();
  auto loc = entry.getLoc();
  mlir::OpBuilder builder(ctx);

  builder.setInsertionPointAfter(entry);

  auto TransformModule = builder.create<mlir::ModuleOp>(loc);
  TransformModule->setAttr(mlir::transform::TransformDialect::kWithNamedSequenceAttrName,
                           builder.getUnitAttr());
  Region& TransformModuleRegion = TransformModule.getBodyRegion();
  builder.setInsertionPointToStart(&TransformModuleRegion.front());

  auto AnyOpType = mlir::transform::AnyOpType::get(builder.getContext());
  auto TransformSequence = builder.create<mlir::transform::NamedSequenceOp>(
      loc,
      /*symName=*/
      std::string(transform::TransformDialect::kTransformEntryPointSymbolName.str()),
      /*rootType*/ AnyOpType,
      /*resultTypes=*/TypeRange{},
      /*bodyBuilder=*/[&](OpBuilder& b, Location loc, Value variantH) {
        ImplicitLocOpBuilder ib(loc, b);
        _createTransformMapToGpuBlock(ib, variantH, blockX, blockY, blockZ, genGpuLaunch);
        b.create<transform::YieldOp>(loc);
      });
  return TransformSequence;
}

}  // namespace nncv
}  // namespace mlir