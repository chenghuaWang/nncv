#include "nncv/compiler/Conversion/Transforms/SplitParams.hpp"
#include <cstring>
#include <unordered_map>

#include "llvm/ADT/StringRef.h"
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
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Location.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/ValueRange.h"
#include "nncv/compiler/Utils/BinaryParams.hpp"

namespace mlir::nncv {
#define GEN_PASS_DEF_SPLITPARAMS
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

void replaceGetGlobalWithParams(IRRewriter& rewriter, mlir::func::FuncOp op,
                                int64_t paramsIdxInArgList,
                                std::unordered_map<std::string, int64_t /*uuid*/>& mapIndexing,
                                std::unordered_map<std::string, mlir::Type>& typeIndexing) {
  mlir::Value params = op.getArguments()[paramsIdxInArgList];
  auto paramsEleType = params.getType().cast<mlir::MemRefType>().getElementType();
  op.walk([&](mlir::memref::GetGlobalOp ggop) {
    auto symbolName = ggop->getAttr("name").cast<::mlir::FlatSymbolRefAttr>().getValue().str();
    if (mapIndexing.end() == mapIndexing.find(symbolName)) {
      printf("[ Warn ] Global Memref %s can't be erase", symbolName.c_str());
      return;
    }
    int64_t uuid = mapIndexing[symbolName];

    // insertion point
    mlir::OpBuilder::InsertionGuard guard(rewriter);
    rewriter.setInsertionPointAfter(ggop);  // insert after ggop

    // get element
    mlir::Value indexValue =
        rewriter.create<mlir::arith::ConstantOp>(ggop.getLoc(), rewriter.getIndexAttr(uuid));
    mlir::ValueRange vr{indexValue};
    mlir::Value memRefPtr =
        rewriter.create<mlir::memref::LoadOp>(ggop->getLoc(), paramsEleType, params, vr);

    // reshape
    auto toType = typeIndexing[symbolName];
    auto newGgop = rewriter.create<mlir::memref::CastOp>(ggop.getLoc(), /*toType*/ toType,
                                                         /*fromValue*/ memRefPtr);

    // remove ggop
    rewriter.replaceOp(ggop, newGgop);
  });
}

class SplitParamsPass : public impl::SplitParamsBase<SplitParamsPass> {
 public:
  void runOnOperation() override {
    IRRewriter rewriter(&getContext());
    // go through all memref.global
    // the global op will not change in this place. So, put them in a vector list is ok.
    llvm::SmallVector<mlir::Operation*> globalOpCandidates;
    std::unordered_map<std::string, int64_t /*uuid*/> globalOpMapIndexing;
    std::unordered_map<std::string, mlir::Type> typeMapIndexing;
    int64_t _cnt = 0;
    getOperation()->walk([&](mlir::memref::GlobalOp op) {
      if (op.getSymName() == "global_seed") return;
      globalOpCandidates.push_back(op);
      globalOpMapIndexing[op.getSymName().str()] = _cnt++;
      typeMapIndexing[op.getSymName().str()] = op.getType();
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
      // -- 1. rewrite params.
      auto newArgType = mlir::MemRefType::get(
          /*shape*/ {_cnt},
          /*eleType*/ mlir::UnrankedMemRefType::get(
              op.getArgumentTypes()[0].cast<mlir::MemRefType>().getElementType(), {}));
      op.insertArgument(1, newArgType, {}, op->getLoc());

      // -- 2. dive into new funcOp, change the get_global op.
      replaceGetGlobalWithParams(rewriter, op, /*the params index in arg list*/ 1,
                                 globalOpMapIndexing, typeMapIndexing);

      // -- 3. erase all global memref.
      for (auto _op : globalOpCandidates) {
        auto op = mlir::cast<mlir::memref::GlobalOp>(_op);
        rewriter.eraseOp(op);
      }
    }

    // if the all success, erease all global memref.
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createSplitParamsPass() { return std::make_unique<SplitParamsPass>(); }

}  // namespace mlir::nncv