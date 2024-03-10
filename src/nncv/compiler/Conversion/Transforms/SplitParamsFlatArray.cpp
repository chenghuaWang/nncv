#include "nncv/compiler/Conversion/Transforms/SplitParamsFlatArray.hpp"
#include <algorithm>
#include <cstring>
#include <unordered_map>

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/ErrorHandling.h"
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
#define GEN_PASS_DEF_SPLITPARAMSFLATARRAY
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

void replaceGetGlobalWithParams(IRRewriter& rewriter, mlir::func::FuncOp op,
                                int64_t paramsIdxInArgList,
                                std::unordered_map<std::string, int64_t /*uuid*/>& mapIndexing,
                                std::unordered_map<std::string, mlir::Type>& typeIndexing,
                                std::vector<::nncv::utils::MemRefIndexer>& memrefIndexer) {
  // check indexer size
  if (!memrefIndexer.size())
    printf("[ Erro ] The MemRefIndexer size is 0. This error may occured becauce of "
           "dense_resource<__elided__>, which means thers is no data.\n");
  // get params in func op
  mlir::Value params = op.getArguments()[paramsIdxInArgList];

  int64_t offset = 0;
  std::unordered_map<int64_t /*uuid*/, int64_t /*offset*/> uuidToOffset;
  for (auto& indexer : memrefIndexer) {
    auto uuid = mapIndexing[indexer.name];
    uuidToOffset[uuid] = offset;
    int64_t acc = 1;
    for (size_t i = 0; i < indexer.dims; ++i) { acc *= indexer.shape[i]; }
    offset += acc;
  }

  op.walk([&](mlir::memref::GetGlobalOp ggop) {
    auto symbolName = ggop->getAttr("name").cast<::mlir::FlatSymbolRefAttr>().getValue().str();
    if (mapIndexing.end() == mapIndexing.find(symbolName)) {
      printf("[ Warn ] Global Memref %s can't be erase", symbolName.c_str());
      return;
    }
    int64_t uuid = mapIndexing[symbolName];
    auto indexer = memrefIndexer[uuid];

    // insertion point
    mlir::OpBuilder::InsertionGuard guard(rewriter);
    rewriter.setInsertionPointAfter(ggop);  // insert after ggop

    // reinterpret cast Op
    auto toType = typeIndexing[symbolName];
    llvm::SmallVector<int64_t> reshapedSizes;
    std::vector<int64_t> __reshapedStrides;
    llvm::SmallVector<int64_t> reshapedStrides;
    int64_t ss = 1;
    for (size_t i = 0; i < indexer.dims; ++i) {
      reshapedSizes.push_back(indexer.shape[i]);
      __reshapedStrides.push_back(ss);
      ss *= indexer.shape[indexer.dims - i - 1];
    }
    std::reverse(__reshapedStrides.begin(), __reshapedStrides.end());
    for (auto item : __reshapedStrides) reshapedStrides.push_back(item);
    auto reinterpretTypeLayoutAttr =
        mlir::StridedLayoutAttr::get(rewriter.getContext(), uuidToOffset[uuid], reshapedStrides);
    auto reinterpretType = mlir::MemRefType::get(toType.cast<mlir::MemRefType>().getShape(),
                                                 toType.cast<mlir::MemRefType>().getElementType(),
                                                 reinterpretTypeLayoutAttr);
    auto reshaped = rewriter.create<mlir::memref::ReinterpretCastOp>(
        op->getLoc(), /*result type*/ reinterpretType, /*source*/ params,
        /*offset*/ uuidToOffset[uuid],
        /*shape*/ reshapedSizes, /*strides*/ reshapedStrides);

    // erase All
    rewriter.replaceOp(ggop, reshaped);
  });
}

class SplitParamsFlatArrayPass : public impl::SplitParamsFlatArrayBase<SplitParamsFlatArrayPass> {
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
      auto denseEleType = dense.getElementType();

      // TODO modified the code below, add a raw data fetch method.
      if (denseEleType.isa<mlir::Float16Type>()) {
        printf("[ info ] Parameter of %s, Raw Data = %ld elements with [f16] type \n", indexer.name,
               dense.getValues<llvm::APFloat>().size());
        // TODO half is different.
      } else if (denseEleType.isa<mlir::Float32Type>()) {
        auto denseArray = dense.getValues<float>();
        auto flattenSize = denseArray.size();
        printf("[ info ] Parameter of %s, Raw Data = %ld elements with [f32] type \n", indexer.name,
               flattenSize);
        float* ptr = new float[flattenSize];
        for (size_t i = 0; i < flattenSize; ++i) { ptr[i] = denseArray[i]; }
        MemRefFlatBufferInstancePtr->addMemRefIndexer(indexer, ptr);
      } else if (denseEleType.isa<mlir::IntegerType>()
                 && denseEleType.getIntOrFloatBitWidth() != 32) {
        auto denseArray = dense.getValues<int32_t>();
        auto flattenSize = denseArray.size();
        printf("[ info ] Parameter of %s, Raw Data = %ld elements with [i32] type \n", indexer.name,
               dense.getValues<int32_t>().size());
        int32_t* ptr = new int32_t[flattenSize];
        for (size_t i = 0; i < flattenSize; ++i) { ptr[i] = denseArray[i]; }
        MemRefFlatBufferInstancePtr->addMemRefIndexer(indexer, ptr);
      } else {
        llvm_unreachable("can't handle type not in [f32, f16, i32]");
      }
    }

    // get all sizes
    int64_t size_0 = 0;
    for (auto item : MemRefFlatBufferInstancePtr->m_indexer) {
      size_t eleLen = 1;
      for (size_t idx = 0; idx < item.dims; ++idx) { eleLen *= item.shape[idx]; }
      size_0 += eleLen;
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
          /*shape*/ {size_0},
          /*eleType*/ op.getArgumentTypes()[0].cast<mlir::MemRefType>().getElementType());
      op.insertArgument(1, newArgType, {}, op->getLoc());

      // -- 2. dive into new funcOp, change the get_global op.
      replaceGetGlobalWithParams(rewriter, op, /*the params index in arg list*/ 1,
                                 globalOpMapIndexing, typeMapIndexing,
                                 MemRefFlatBufferInstancePtr->m_indexer);

      // -- 3. erase all global memref.
      for (auto _op : globalOpCandidates) {
        auto op = mlir::cast<mlir::memref::GlobalOp>(_op);
        rewriter.eraseOp(op);
      }
    }
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createSplitParamsFlatArrayPass() {
  return std::make_unique<SplitParamsFlatArrayPass>();
}

};  // namespace mlir::nncv
