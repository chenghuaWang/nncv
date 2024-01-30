#include "nncv/compiler/TransformCommon/Common.hpp"
#include "mlir/Dialect/Linalg/TransformOps/LinalgMatchOps.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Transform/IR/TransformDialect.h"
#include "mlir/Dialect/Transform/IR/TransformOps.h"
#include "mlir/Dialect/Transform/IR/TransformTypes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Dialect/Transform/LoopExtension/LoopExtensionOps.h"

namespace mlir {
namespace nncv {

void createTransformRegion(mlir::FunctionOpInterface entry, TransformBuilderFunc func) {
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
  (void)TransformSequence;
}

void transformHoistingSubsetFunc(mlir::ImplicitLocOpBuilder& builder, mlir::Value funcOp) {
  // Value Loops =
  //     builder.create<mlir::transform::MatchOp>(funcOp, mlir::scf::ForOp::getOperationName());
  // builder.create<mlir::transform::HoistLoopInvariantSubsetsOp>(Loops);
}

}  // namespace nncv
}  // namespace mlir