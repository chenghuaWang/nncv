// mlir build tools
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

// All dialect
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlow.h"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"

// This file's head
#include "nncv/compiler/Conversion/AtenToMlir/AtenToMlir.h"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"

namespace mlir::nncv {
#define GEN_PASS_DEF_CONVERTATENTOMLIR
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {
//===----------------------------------------------------------------------===//
// Prepare all type converter
//===----------------------------------------------------------------------===//
static mlir::TypeConverter prepareTypeConverter() {
  mlir::TypeConverter converter;

  // pointer to memref
  converter.addConversion([&](mlir::aten::PointerType type) -> mlir::Type {
    auto ty = converter.convertType(type.getPointee());
    return mlir::MemRefType::get({}, ty);
  });

  // float type
  converter.addConversion([&](mlir::FloatType type) -> mlir::Type { return type; });

  // bool type
  converter.addConversion([&](mlir::aten::BoolType type) -> mlir::Type {
    return mlir::IntegerType::get(type.getContext(), 8);
  });

  // int type
  converter.addConversion([&](mlir::aten::IntType type) -> mlir::Type {
    return mlir::IntegerType::get(type.getContext(), type.getWidth(),
                                  mlir::IntegerType::SignednessSemantics::Signless);
  });

  // memref type
  converter.addConversion([&](mlir::MemRefType type) -> mlir::Type { return type; });
  converter.addConversion([&](mlir::UnrankedMemRefType type) -> mlir::Type { return type; });

  // array type
  converter.addConversion([&](mlir::aten::ArrayType type) -> mlir::Type {
    auto elementType = converter.convertType(type.getEleT());
    return mlir::MemRefType::get(type.getSizeT(), elementType);
  });

  // ignore mlir int type
  converter.addConversion([&](mlir::IntegerType type) -> mlir::Type { return type; });

  return converter;
}

//===----------------------------------------------------------------------===//
// Convert aten.load to memref.load
//===----------------------------------------------------------------------===//
class AtenLoadOpLowering : public OpConversionPattern<aten::LoadOp> {
 public:
  using OpConversionPattern<aten::LoadOp>::OpConversionPattern;

  LogicalResult matchAndRewrite(aten::LoadOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    rewriter.replaceOpWithNewOp<mlir::memref::LoadOp>(op, adaptor.getAddr());
    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.store to memref.store
//===----------------------------------------------------------------------===//
class AtenStoreOpLowering : public OpConversionPattern<aten::StoreOp> {
 public:
  using OpConversionPattern<aten::StoreOp>::OpConversionPattern;

  LogicalResult matchAndRewrite(aten::StoreOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    rewriter.replaceOpWithNewOp<mlir::memref::StoreOp>(op, adaptor.getValue(), adaptor.getAddr());
    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.alloca to memref.alloca
//===----------------------------------------------------------------------===//
class AtenAllocaOpLowering : public OpConversionPattern<aten::AllocaOp> {
 public:
  using OpConversionPattern<aten::AllocaOp>::OpConversionPattern;

  LogicalResult matchAndRewrite(aten::AllocaOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    auto oldType = adaptor.getAllocaType();
    auto newType = getTypeConverter()->convertType(oldType);
    auto memrefType = mlir::MemRefType::get({}, newType);

    rewriter.replaceOpWithNewOp<mlir::memref::AllocaOp>(op, memrefType, op.getAlignmentAttr());
    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.const to arith.const
//===----------------------------------------------------------------------===//
class AtenConstOpLowering : public OpConversionPattern<aten::ConstantOp> {
 public:
  using OpConversionPattern<aten::ConstantOp>::OpConversionPattern;

  LogicalResult matchAndRewrite(aten::ConstantOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    auto newType = getTypeConverter()->convertType(op.getType());
    mlir::TypedAttr value;

    if (mlir::isa<mlir::aten::BoolType>(op.getType())) {
      auto boolV = mlir::cast<mlir::aten::BoolAttr>(op.getValue());
      value = rewriter.getIntegerAttr(newType, boolV.getValue());
    } else /*normal aten.int*/ {
      value = rewriter.getIntegerAttr(newType,
                                      mlir::cast<mlir::aten::IntAttr>(op.getValue()).getValue());
    }
    rewriter.replaceOpWithNewOp<mlir::arith::ConstantOp>(op, newType, value);
    return success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.return to func.return
//===----------------------------------------------------------------------===//
class AtenReturnOpLowering : public OpConversionPattern<aten::ReturnOp> {
 public:
  using OpConversionPattern<aten::ReturnOp>::OpConversionPattern;

  LogicalResult matchAndRewrite(aten::ReturnOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    rewriter.replaceOpWithNewOp<mlir::func::ReturnOp>(op, adaptor.getOperands());
    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.call to func.call
//===----------------------------------------------------------------------===//
class AtenCallOpLowering : public OpConversionPattern<aten::CallOp> {
 public:
  using OpConversionPattern<aten::CallOp>::OpConversionPattern;

  LogicalResult matchAndRewrite(aten::CallOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    llvm::SmallVector<mlir::Type> types;
    if (mlir::failed(getTypeConverter()->convertTypes(op.getResultTypes(), types))) {
      return mlir::failure();
    }
    rewriter.replaceOpWithNewOp<mlir::func::CallOp>(op, mlir::SymbolRefAttr::get(op), types,
                                                    adaptor.getOperands());
    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.func to func.func
//===----------------------------------------------------------------------===//
class AtenFuncOpLowering : public OpConversionPattern<aten::FuncOp> {
 public:
  using OpConversionPattern<aten::FuncOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(aten::FuncOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    auto funcType = op.getFunctionType();
    mlir::TypeConverter::SignatureConversion signatureConversion(funcType.getNumInputs());

    for (const auto& argType : enumerate(funcType.getInputs())) {
      auto convertedType = typeConverter->convertType(argType.value());
      if (!convertedType) { return mlir::failure(); }
      signatureConversion.addInputs(argType.index(), convertedType);
    }

    mlir::Type resultType = getTypeConverter()->convertType(funcType.getReturnType());

    auto funcOp = rewriter.create<mlir::func::FuncOp>(
        op.getLoc(), op.getName(),
        rewriter.getFunctionType(signatureConversion.getConvertedTypes(),
                                 resultType ? mlir::TypeRange(resultType) : mlir::TypeRange()));

    rewriter.inlineRegionBefore(op.getBody(), funcOp.getBody(), funcOp.end());

    if (failed(
            rewriter.convertRegionTypes(&funcOp.getBody(), *typeConverter, &signatureConversion))) {
      return mlir::failure();
    }

    rewriter.eraseOp(op);
    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.bin to arith.xxx
// TODO
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Convert aten.unary to arith.xxx
// TODO
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Convert aten.cmp to arith.xxx
// TODO
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Convert aten.yield to arith.xxx
// TODO
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Aten to mlir
//===----------------------------------------------------------------------===//
namespace {
class ConvertAtenToMlir : public impl::ConvertAtenToMlirBase<ConvertAtenToMlir> {
 public:
  void runOnOperation() override {
    RewritePatternSet patterns(&getContext());
    ConversionTarget target(getContext());

    auto converter = prepareTypeConverter();

    // set aten-lang as illegal
    target.addIllegalDialect<mlir::aten::AtenDialect>();

    // set those dialects as llegal
    target.addLegalDialect<mlir::arith::ArithDialect, mlir::affine::AffineDialect,
                           mlir::scf::SCFDialect, mlir::memref::MemRefDialect,
                           mlir::cf::ControlFlowDialect, mlir::func::FuncDialect>();

    // prepare all patterns.
    populateAtenToMlirConversionPatterns(&patterns, converter);

    // do conversion and return if failured.
    if (failed(applyPartialConversion(getOperation(), target, std::move(patterns))))
      signalPassFailure();
  }
};
}  // namespace

void populateAtenToMlirConversionPatterns(mlir::RewritePatternSet* patterns,
                                          mlir::TypeConverter& converter) {
  patterns->add<AtenConstOpLowering>(patterns->getContext());
}

std::unique_ptr<mlir::Pass> createConvertAtenToMlirPass() {
  return std::make_unique<ConvertAtenToMlir>();
}

}  // namespace nncv
}  // namespace mlir