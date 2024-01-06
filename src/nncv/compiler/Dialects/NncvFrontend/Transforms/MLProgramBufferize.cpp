#include "nncv/compiler/Dialects/NncvFrontend/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"

#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/MLProgram/IR/MLProgram.h"
#include "mlir/Dialect/Bufferization/IR/Bufferization.h"

//===----------------------------------------------------------------------===//
// MLProgram Bufferize
//===----------------------------------------------------------------------===//

static mlir::LogicalResult bufferizeMLProgramGlobalOp(mlir::ml_program::GlobalOp globalOp,
                                                      mlir::OpBuilder& b) {
  if (!globalOp.getValue().has_value()) {
    return globalOp.emitError("mlprogram global op must have a value");
  }

  auto tensorType = globalOp.getType().cast<mlir::RankedTensorType>();
  auto memrefType = mlir::MemRefType::get(tensorType.getShape(), tensorType.getElementType());

  b.setInsertionPointToStart(globalOp->getParentOfType<mlir::ModuleOp>().getBody());
  b.create<mlir::memref::GlobalOp>(mlir::UnknownLoc::get(b.getContext()), globalOp.getSymName(),
                                   /*sym_visibility=*/globalOp.getSymVisibilityAttr(),
                                   /*type=*/memrefType,
                                   /*initial_value=*/globalOp.getValue().value(),
                                   /*constant=*/globalOp.getIsMutable() ? false : true,
                                   /*alignment=*/nullptr);
  return mlir::success();
}

static mlir::LogicalResult bufferizeMLProgramGlobaLoadOp(
    mlir::ml_program::GlobalLoadOp globalLoadOp, mlir::OpBuilder& b,
    llvm::SmallVector<mlir::Operation*>& toErase) {
  auto tensorType = globalLoadOp.getType().cast<mlir::RankedTensorType>();
  auto memrefType = mlir::MemRefType::get(tensorType.getShape(), tensorType.getElementType());

  b.setInsertionPoint(globalLoadOp);
  mlir::Value globalVal = b.create<mlir::memref::GetGlobalOp>(
      globalLoadOp.getLoc(), memrefType, globalLoadOp.getGlobalAttr().getLeafReference());
  globalVal =
      b.create<mlir::bufferization::ToTensorOp>(globalLoadOp->getLoc(), tensorType, globalVal);

  globalLoadOp->getResult(0).replaceAllUsesWith(globalVal);
  return mlir::success();
}

static mlir::LogicalResult bufferizeMLProgramGlobaStoreOp(
    mlir::ml_program::GlobalStoreOp globalStoreOp, mlir::OpBuilder& b,
    llvm::SmallVector<mlir::Operation*>& toErase) {
  auto tensorType = globalStoreOp.getValue().getType().cast<mlir::RankedTensorType>();
  auto memrefType = mlir::MemRefType::get(tensorType.getShape(), tensorType.getElementType());

  b.setInsertionPoint(globalStoreOp);
  mlir::Value memref = b.create<mlir::memref::GetGlobalOp>(
      globalStoreOp.getLoc(), memrefType, globalStoreOp.getGlobalAttr().getLeafReference());
  mlir::Value copyValue = b.create<mlir::bufferization::ToMemrefOp>(
      globalStoreOp->getLoc(), memrefType, globalStoreOp.getValue());
  b.create<mlir::memref::CopyOp>(globalStoreOp->getLoc(), copyValue, memref);

  return mlir::success();
}

namespace {

class MLProgramBufferize : public mlir::nncv::MLProgramBufferizeBase<MLProgramBufferize> {
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::bufferization::BufferizationDialect, mlir::memref::MemRefDialect>();
  }

  void runOnOperation() override {
    auto module = getOperation();
    mlir::OpBuilder b(module.getBodyRegion());
    llvm::SmallVector<mlir::Operation*> toErase;

    auto walkResult = module.walk([&](mlir::ml_program::GlobalOp op) {
      if (auto type = op.getType().dyn_cast<mlir::RankedTensorType>()) {
        if (!type.hasStaticShape()) {
          // If the ml_program.global has dynamically shaped tensor.
          op.emitError("unimplemented: global op bufferization with dynamic shape");
          return mlir::WalkResult::interrupt();
        }
      } else {
        // If the ml_program.global is of non-tensor type.
        op.emitError("unsupported global op type");
        return mlir::WalkResult::interrupt();
      }

      if (failed(bufferizeMLProgramGlobalOp(op, b))) {
        op.emitError("bufferization for this op failed");
        return mlir::WalkResult::interrupt();
      }
      toErase.push_back(op);
      return mlir::WalkResult::advance();
    });

    if (walkResult.wasInterrupted()) return signalPassFailure();

    module.walk([&](mlir::ml_program::GlobalLoadOp op) {
      if (failed(bufferizeMLProgramGlobaLoadOp(op, b, toErase))) {
        op.emitError("bufferization for this op failed");
        return;
      }
      toErase.push_back(op);
    });

    module.walk([&](mlir::ml_program::GlobalStoreOp op) {
      if (failed(bufferizeMLProgramGlobaStoreOp(op, b, toErase))) {
        op.emitError("bufferization for this op failed");
        return;
      }
      toErase.push_back(op);
    });

    for (auto op : llvm::reverse(toErase)) op->erase();
  }
};

}  // namespace

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> mlir::nncv::createMLProgramBufferizePass() {
  return std::make_unique<MLProgramBufferize>();
}