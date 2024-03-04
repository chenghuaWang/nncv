#include "nncv/compiler/Conversion/Transforms/SplitParams.hpp"
#include <cstring>
#include <unordered_map>

#include "mlir/Conversion/LLVMCommon/ConversionTarget.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Dialect/Transform/IR/TransformDialect.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Location.h"
#include "mlir/IR/Operation.h"
#include "nncv/compiler/Utils/BinaryParams.hpp"

namespace mlir::nncv {
#define GEN_PASS_DEF_SPLITPARAMS
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class SplitParamsPass : public impl::SplitParamsBase<SplitParamsPass> {
 public:
  void runOnOperation() override {
    IRRewriter rewriter(&getContext());
    // go through all memref.global
    // the global op will not change in this place. So, put them in a vector list is ok.
    llvm::SmallVector<mlir::Operation*> globalOpCandidates;
    std::unordered_map<mlir::Operation*, int64_t /*uuid*/> globalOpMapIndexing;
    int64_t _cnt = 0;
    getOperation()->walk([&](mlir::memref::GlobalOp op) {
      if (op.getSymName() == "global_seed") return;
      globalOpCandidates.push_back(op);
      globalOpMapIndexing[op] = _cnt++;
    });

    // write to binary file. The function below will call the same function in libnncv
    auto MemRefFlatBufferInstancePtr = &::nncv::utils::MemRefFlatBuffer::getInstance();
    for (auto _op : globalOpCandidates) {
      auto op = mlir::cast<mlir::memref::GlobalOp>(_op);
      ::nncv::utils::MemRefIndexer indexer;

      // store name
      auto symbolName = op.getSymName();
      strcpy(indexer.name, symbolName.str().c_str());

      // get the MemRef Info
      auto memRefType = op.getType().cast<mlir::MemRefType>();
      auto shape = memRefType.getShape();
      auto eleTypeBitWidth = memRefType.getElementTypeBitWidth();
      auto aligned = op.getAlignment();

      // save
      indexer.dims = shape.size();
      for (size_t i = 0; i < shape.size(); ++i) { indexer.shape[i] = shape[i]; }
      indexer.eleWidth = eleTypeBitWidth / 8;
      indexer.aligned = aligned.has_value() ? aligned.value() : 0;

      // get the dense attribute
      if (!mlir::isa<mlir::DenseElementsAttr>(op.getInitialValue().value())) continue;
      auto dense = op.getInitialValue().value().cast<mlir::DenseElementsAttr>();
      printf("[ info ] Parameter of %s, Raw Data = %ld B \n", indexer.name,
             dense.getRawData().size());

      // save to instance
      MemRefFlatBufferInstancePtr->addMemRefIndexer(indexer, (void*)dense.getRawData().data());
    }

    // 1. find function with forward function name. rewrite it from forward(in, out) to forward(in,
    // out, params)
    // 2. chang all get_global to params and reshape.
    llvm::SmallVector<mlir::Operation*> funcCandidates;
    getOperation()->walk([&](mlir::func::FuncOp op) { funcCandidates.push_back(op); });
    for (auto _op : funcCandidates) {
      auto op = mlir::cast<mlir::func::FuncOp>(_op);
      if (op.getSymName() != "forward") continue;

      // below is the rewrite logic
      // -- 1. rewrite params
      auto newArgType = mlir::MemRefType::get(
          /*shape*/ {_cnt},
          /*eleType*/ mlir::UnrankedMemRefType::get(op.getArgumentTypes()[0], {}));
      // TODO
      // op.getBody().addArgument(newArgType, );

      // -- 2. dive into new funcOp
      // TODO
      break;
    }

    // if the all success, erease all global memref.
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createSplitParamsPass() { return std::make_unique<SplitParamsPass>(); }

}  // namespace mlir::nncv