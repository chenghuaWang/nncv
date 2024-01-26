// mlir build tools
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "llvm/ADT/TypeSwitch.h"

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

  // ignore index type
  converter.addConversion([&](mlir::IndexType type) -> mlir::Type { return type; });

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
    } else if (mlir::isa<mlir::aten::IntType>(op.getType())) /*normal aten.int*/ {
      value = rewriter.getIntegerAttr(newType,
                                      mlir::cast<mlir::aten::IntAttr>(op.getValue()).getValue());
    } else if (mlir::isa<mlir::FloatType>(op.getType())) {
      value = rewriter.getFloatAttr(newType, mlir::cast<mlir::FloatAttr>(op.getValue()).getValue());
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
    rewriter.replaceOpWithNewOp<mlir::func::CallOp>(op, op.getCalleeAttr(), types,
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

    // if is declaration only.
    if (op.isPrivate()) { funcOp.setPrivate(); }

    rewriter.eraseOp(op);
    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.bin to arith.xxx
//===----------------------------------------------------------------------===//
class AtenBinOpLowering : public OpConversionPattern<aten::BinOp> {
 public:
  using OpConversionPattern<aten::BinOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(aten::BinOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    mlir::Type newType = getTypeConverter()->convertType(op.getType());

    switch (op.getPredicate()) {
      case mlir::aten::BinOpPredicate::Mul: {
        if (newType.isa<mlir::IntegerType>()) {
          rewriter.replaceOpWithNewOp<mlir::arith::MulIOp>(op, newType, adaptor.getLhs(),
                                                           adaptor.getRhs());
        } else if (newType.isa<mlir::FloatType>()) {
          rewriter.replaceOpWithNewOp<mlir::arith::MulFOp>(op, newType, adaptor.getLhs(),
                                                           adaptor.getRhs());
        }
        break;
      }
      case mlir::aten::BinOpPredicate::Div: {
        if (newType.isa<mlir::IntegerType>()) {
          if (newType.isSignlessInteger()) {
            rewriter.replaceOpWithNewOp<mlir::arith::DivUIOp>(op, newType, adaptor.getLhs(),
                                                              adaptor.getRhs());
          }
        } else if (newType.isa<mlir::FloatType>()) {
          rewriter.replaceOpWithNewOp<mlir::arith::DivFOp>(op, newType, adaptor.getLhs(),
                                                           adaptor.getRhs());
        }
        break;
      }
      case mlir::aten::BinOpPredicate::Mod: {
        if (newType.isa<mlir::IntegerType>()) {
          if (newType.isSignlessInteger()) {
            rewriter.replaceOpWithNewOp<mlir::arith::RemUIOp>(op, newType, adaptor.getLhs(),
                                                              adaptor.getRhs());
          }
        } else if (newType.isa<mlir::FloatType>()) {
          rewriter.replaceOpWithNewOp<mlir::arith::RemFOp>(op, newType, adaptor.getLhs(),
                                                           adaptor.getRhs());
        }
        break;
      }
      case mlir::aten::BinOpPredicate::Add: {
        if (newType.isa<mlir::IntegerType>()) {
          rewriter.replaceOpWithNewOp<mlir::arith::AddIOp>(op, newType, adaptor.getLhs(),
                                                           adaptor.getRhs());
        } else {
          rewriter.replaceOpWithNewOp<mlir::arith::AddFOp>(op, newType, adaptor.getLhs(),
                                                           adaptor.getRhs());
        }
        break;
      }
      case mlir::aten::BinOpPredicate::Sub: {
        if (newType.isa<mlir::IntegerType>()) {
          rewriter.replaceOpWithNewOp<mlir::arith::SubIOp>(op, newType, adaptor.getLhs(),
                                                           adaptor.getRhs());
        } else {
          rewriter.replaceOpWithNewOp<mlir::arith::SubFOp>(op, newType, adaptor.getLhs(),
                                                           adaptor.getRhs());
        }
        break;
      }
      case mlir::aten::BinOpPredicate::And: {
        rewriter.replaceOpWithNewOp<mlir::arith::AndIOp>(op, newType, adaptor.getLhs(),
                                                         adaptor.getRhs());
        break;
      }
      case mlir::aten::BinOpPredicate::Xor: {
        rewriter.replaceOpWithNewOp<mlir::arith::XOrIOp>(op, newType, adaptor.getLhs(),
                                                         adaptor.getRhs());
        break;
      }
      case mlir::aten::BinOpPredicate::Or: {
        rewriter.replaceOpWithNewOp<mlir::arith::OrIOp>(op, newType, adaptor.getLhs(),
                                                        adaptor.getRhs());
        break;
      }
      case mlir::aten::BinOpPredicate::LogicAnd: {
        // l-bool and r-bool
        mlir::Value andV = rewriter.replaceOpWithNewOp<mlir::arith::AndIOp>(op, adaptor.getLhs(),
                                                                            adaptor.getRhs());

        // trunci to i1
        rewriter.create<mlir::arith::TruncIOp>(op.getLoc(), rewriter.getI1Type(), andV);
        break;
      }
      case mlir::aten::BinOpPredicate::LogicOr: {
        // l-bool and r-bool
        mlir::Value andV =
            rewriter.replaceOpWithNewOp<mlir::arith::OrIOp>(op, adaptor.getLhs(), adaptor.getRhs());

        // trunci to i1
        rewriter.create<mlir::arith::TruncIOp>(op.getLoc(), rewriter.getI1Type(), andV);
        break;
      }
    }

    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.unary to arith.xxx
//===----------------------------------------------------------------------===//
class AtenUnaryOpLowering : public OpConversionPattern<aten::UnaryOp> {
 public:
  using OpConversionPattern<aten::UnaryOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(aten::UnaryOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    auto oldInput = adaptor.getInput();
    auto oldType = getTypeConverter()->convertType(op.getType());

    switch (op.getPredicate()) {
      case mlir::aten::UnaryOpPredicate::Inc: {
        auto _1 = rewriter.create<mlir::arith::ConstantOp>(op.getLoc(), oldType,
                                                           mlir::IntegerAttr::get(oldType, 1));
        rewriter.replaceOpWithNewOp<mlir::arith::AddIOp>(op, oldType, oldInput, _1);
        break;
      }
      case mlir::aten::UnaryOpPredicate::Dec: {
        auto _1 = rewriter.create<mlir::arith::ConstantOp>(op.getLoc(), oldType,
                                                           mlir::IntegerAttr::get(oldType, 1));
        rewriter.replaceOpWithNewOp<mlir::arith::SubIOp>(op, oldType, oldInput, _1);
        break;
      }
      case mlir::aten::UnaryOpPredicate::Plus: {
        rewriter.replaceOp(op, op.getInput());
        break;
      }
      case mlir::aten::UnaryOpPredicate::Minus: {
        auto _0 = rewriter.create<mlir::arith::ConstantOp>(op.getLoc(), oldType,
                                                           mlir::IntegerAttr::get(oldType, 0));
        rewriter.replaceOpWithNewOp<mlir::arith::SubIOp>(op, oldType, _0, oldInput);
        break;
      }
      case mlir::aten::UnaryOpPredicate::Not: {
        auto _minusOne = rewriter.create<mlir::arith::ConstantOp>(
            op.getLoc(), oldType, mlir::IntegerAttr::get(oldType, -1));
        rewriter.replaceOpWithNewOp<mlir::arith::XOrIOp>(op, oldType, _minusOne, oldInput);
        break;
      }
    }

    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.cmp to arith.xxx
//===----------------------------------------------------------------------===//
class AtenCmpOpLowering : public OpConversionPattern<aten::CmpOp> {
 public:
  using OpConversionPattern<aten::CmpOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(aten::CmpOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    auto oldType = adaptor.getLhs().getType();
    auto integerType = mlir::IntegerType::get(getContext(), 1, mlir::IntegerType::Signless);

    auto lhsV = adaptor.getLhs();
    auto rhsV = adaptor.getRhs();

    if (mlir::isa<mlir::IndexType>(oldType)) {
      lhsV = rewriter.create<mlir::arith::IndexCastOp>(op->getLoc(), rewriter.getI64Type(),
                                                       adaptor.getLhs());
      rhsV = rewriter.create<mlir::arith::IndexCastOp>(op->getLoc(), rewriter.getI64Type(),
                                                       adaptor.getRhs());
    }

    mlir::Value newResult;
    switch (op.getPredicate()) {
      case mlir::aten::CmpOpPredicate::lt: {
        if (oldType.isa<mlir::IntegerType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::ult),
              lhsV, rhsV);
        } else if (oldType.isa<mlir::FloatType>()) {
          newResult = rewriter.create<mlir::arith::CmpFOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpFPredicateAttr::get(getContext(), mlir::arith::CmpFPredicate::ULT),
              lhsV, rhsV,
              mlir::arith::FastMathFlagsAttr::get(getContext(), mlir::arith::FastMathFlags::none));
        } else if (oldType.isa<mlir::IndexType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::ult),
              lhsV, rhsV);
        }
        break;
      }
      case mlir::aten::CmpOpPredicate::le: {
        if (oldType.isa<mlir::IntegerType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::ule),
              lhsV, rhsV);
        } else if (oldType.isa<mlir::FloatType>()) {
          newResult = rewriter.create<mlir::arith::CmpFOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpFPredicateAttr::get(getContext(), mlir::arith::CmpFPredicate::ULE),
              lhsV, rhsV,
              mlir::arith::FastMathFlagsAttr::get(getContext(), mlir::arith::FastMathFlags::none));
        } else if (oldType.isa<mlir::IndexType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::ule),
              lhsV, rhsV);
        }
        break;
      }
      case mlir::aten::CmpOpPredicate::gt: {
        if (oldType.isa<mlir::IntegerType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::ugt),
              lhsV, rhsV);
        } else if (oldType.isa<mlir::FloatType>()) {
          newResult = rewriter.create<mlir::arith::CmpFOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpFPredicateAttr::get(getContext(), mlir::arith::CmpFPredicate::UGT),
              lhsV, rhsV,
              mlir::arith::FastMathFlagsAttr::get(getContext(), mlir::arith::FastMathFlags::none));
        } else if (oldType.isa<mlir::IndexType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::ugt),
              lhsV, rhsV);
        }
        break;
      }
      case mlir::aten::CmpOpPredicate::ge: {
        if (oldType.isa<mlir::IntegerType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::uge),
              lhsV, rhsV);
        } else if (oldType.isa<mlir::FloatType>()) {
          newResult = rewriter.create<mlir::arith::CmpFOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpFPredicateAttr::get(getContext(), mlir::arith::CmpFPredicate::UGE),
              lhsV, rhsV,
              mlir::arith::FastMathFlagsAttr::get(getContext(), mlir::arith::FastMathFlags::none));
        } else if (oldType.isa<mlir::IndexType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::uge),
              lhsV, rhsV);
        }
        break;
      }
      case mlir::aten::CmpOpPredicate::eq: {
        if (oldType.isa<mlir::IntegerType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::eq),
              lhsV, rhsV);
        } else if (oldType.isa<mlir::FloatType>()) {
          newResult = rewriter.create<mlir::arith::CmpFOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpFPredicateAttr::get(getContext(), mlir::arith::CmpFPredicate::UEQ),
              lhsV, rhsV,
              mlir::arith::FastMathFlagsAttr::get(getContext(), mlir::arith::FastMathFlags::none));
        } else if (oldType.isa<mlir::IndexType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::eq),
              lhsV, rhsV);
        }
        break;
      }
      case mlir::aten::CmpOpPredicate::ne: {
        if (oldType.isa<mlir::IntegerType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::ne),
              lhsV, rhsV);
        } else if (oldType.isa<mlir::FloatType>()) {
          newResult = rewriter.create<mlir::arith::CmpFOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpFPredicateAttr::get(getContext(), mlir::arith::CmpFPredicate::UNE),
              lhsV, rhsV,
              mlir::arith::FastMathFlagsAttr::get(getContext(), mlir::arith::FastMathFlags::none));
        } else if (oldType.isa<mlir::IndexType>()) {
          newResult = rewriter.create<mlir::arith::CmpIOp>(
              op.getLoc(), integerType,
              mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::ne),
              lhsV, rhsV);
        }
        break;
      }
    }
    auto mlirResultTy = getTypeConverter()->convertType(op.getType());
    rewriter.replaceOpWithNewOp<mlir::arith::ExtUIOp>(op, mlirResultTy, newResult);

    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.yield to scf.yield. (Just erease aten.yield Op)
//===----------------------------------------------------------------------===//
class AtenYieldIfOpLowering : public OpConversionPattern<aten::YieldOp> {
 public:
  using OpConversionPattern<aten::YieldOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(aten::YieldOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    // scf will generate scf.yield when building. Just erase aten::YieldOp is OK.
    if (mlir::isa<mlir::aten::IfOp>(op->getParentOp())
        || mlir::isa<mlir::scf::IfOp>(op->getParentOp())) {
      rewriter.eraseOp(op);
    } else {
      return mlir::LogicalResult::failure();
    }
    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.yield to scf.yield. (Just erease aten.yield Op)
//===----------------------------------------------------------------------===//
class AtenYieldLoopOpLowering : public OpConversionPattern<aten::YieldOp> {
 public:
  using OpConversionPattern<aten::YieldOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(aten::YieldOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    // scf will generate scf.yield when building. Just erase aten::YieldOp is OK.
    if (mlir::isa<mlir::aten::LoopOp>(op->getParentOp())
        || mlir::isa<mlir::scf::WhileOp>(op->getParentOp())) {
      rewriter.eraseOp(op);
    } else {
      return mlir::LogicalResult::failure();
    }
    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.if to scf.if
//===----------------------------------------------------------------------===//
class AtenIfOpLowering : public OpConversionPattern<aten::IfOp> {
 public:
  using OpConversionPattern<aten::IfOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(aten::IfOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    // check if this value is not 1-bit sign
    auto cond = adaptor.getCondition();
    auto condType = cond.getType();
    auto newCond = cond;
    auto integerType = mlir::IntegerType::get(getContext(), 1, mlir::IntegerType::Signless);

    if (condType.isa<mlir::IntegerType>()) {
      auto cmpValue = rewriter.create<mlir::arith::ConstantOp>(
          op.getLoc(), rewriter.getIntegerAttr(condType, 0));
      newCond = rewriter.create<mlir::arith::CmpIOp>(
          op.getLoc(), integerType,
          mlir::arith::CmpIPredicateAttr::get(getContext(), mlir::arith::CmpIPredicate::ugt), cond,
          cmpValue);
    } else if (condType.isa<mlir::FloatType>()) {
      auto cmpValue = rewriter.create<mlir::arith::ConstantOp>(
          op.getLoc(), rewriter.getFloatAttr(condType, 0.0));
      newCond = rewriter.create<mlir::arith::CmpFOp>(
          op.getLoc(), integerType,
          mlir::arith::CmpFPredicateAttr::get(getContext(), mlir::arith::CmpFPredicate::UGT), cond,
          cmpValue,
          mlir::arith::FastMathFlagsAttr::get(getContext(), mlir::arith::FastMathFlags::none));
    }

    // get all regions from old op
    auto thenRegionPtr = &adaptor.getThenRegion();
    mlir::Region* elseRegionPtr = nullptr;
    if (!adaptor.getElseRegion().empty()) { elseRegionPtr = &adaptor.getElseRegion(); }

    // build new scf op
    auto ifOp =
        rewriter.create<mlir::scf::IfOp>(op->getLoc(), newCond, elseRegionPtr ? true : false);
    auto* ifOpThenBlock = &ifOp.getThenRegion().front();
    rewriter.inlineBlockBefore(&thenRegionPtr->front(), ifOpThenBlock, ifOpThenBlock->begin());
    if (elseRegionPtr) {
      auto* ifOpElseBlock = &ifOp.getElseRegion().front();
      rewriter.inlineBlockBefore(&elseRegionPtr->front(), ifOpElseBlock, ifOpElseBlock->begin());
    }
    rewriter.replaceOp(op, ifOp);

    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.loop to scf.while
//===----------------------------------------------------------------------===//
class AtenLoopOpLowering : public OpConversionPattern<aten::LoopOp> {
 public:
  using OpConversionPattern<aten::LoopOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(aten::LoopOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    // get mlir loacation
    auto mlirLocation = op->getLoc();

    // get all regions needed for create a scf.while
    auto stepRegion = &op.getStep();
    auto condRegion = &op.getCond();
    auto bodyRegion = &op.getBody();

    if (op.getKind() == mlir::aten::LoopOpPredict::For) {
      llvm::SmallVector<mlir::Type> tr;
      llvm::SmallVector<mlir::Value> vr;
      auto scfOp = rewriter.create<mlir::scf::WhileOp>(
          mlirLocation, /*type range*/ tr, /*value range*/ vr, /*before*/
          [&](OpBuilder& builder, Location location, ValueRange vr) {
            // insert condition at tail of before scope.

            // FIXME: for now, I supposed that the last value of conRegion is used for comparation.
            // the condition region only have one block. The back() means the last op in this block.
            mlir::Operation* storeOp = nullptr;
            auto _backOp = &condRegion->front().back();
            auto _frontOp = &condRegion->front().front();
            while (_backOp != _frontOp) {
              if (mlir::isa<mlir::memref::StoreOp>(_backOp)) {
                storeOp = _backOp;
                break;
              } else {
                _backOp = _backOp->getPrevNode();
              }
            }
            mlir::Value oldCondValue;
            if (storeOp) {
              auto allocaOp = storeOp->getPrevNode();
              auto extuiOrTrunciOp = allocaOp->getPrevNode();
              if (mlir::isa<mlir::arith::TruncIOp>(extuiOrTrunciOp)) {
                oldCondValue = extuiOrTrunciOp->getResults()[0];
              } else {
                auto cmpiOp = extuiOrTrunciOp->getPrevNode();
                if (mlir::isa<mlir::arith::CmpIOp>(cmpiOp)
                    || mlir::isa<mlir::arith::CmpFOp>(cmpiOp)) {
                  oldCondValue = cmpiOp->getResults()[0];
                } else {
                  printf("[ Erro ] When getting arith.cmp op for scf condition failed. Missing "
                         "arith.cmp op\n");
                  exit(-1);
                }
              }

            } else {
              printf("[ Erro ] When getting arith.cmp op for scf condition failed. Missing "
                     "memref.store op\n");
              exit(-1);
            }
            mlir::ValueRange emptyVr;
            builder.create<mlir::scf::ConditionOp>(location, oldCondValue, emptyVr);
          },
          /*after*/
          [&](OpBuilder& builder, Location location, ValueRange vr) {
            /*do something*/
            builder.create<mlir::scf::YieldOp>(location);
          });

      // copy cond op to scfOpBeforeBlock
      auto scfOpBeforeBlock = &scfOp.getBefore().front();
      rewriter.inlineBlockBefore(&condRegion->front(), scfOpBeforeBlock, scfOpBeforeBlock->begin());

      // copy step op to scfOpAfterBlock
      auto scfOpAfterBlock = &scfOp.getAfter().front();
      rewriter.inlineBlockBefore(&stepRegion->front(), scfOpAfterBlock, scfOpAfterBlock->begin());

      // copy body op to scfOpAfterBlock
      rewriter.inlineBlockBefore(&bodyRegion->front(), scfOpAfterBlock, scfOpAfterBlock->begin());

      rewriter.replaceOp(op, scfOp);
    } else if (op.getKind() == mlir::aten::LoopOpPredict::While) /*normal while loop*/ {
      llvm::SmallVector<mlir::Type> tr;
      llvm::SmallVector<mlir::Value> vr;
      auto scfOp = rewriter.create<mlir::scf::WhileOp>(
          mlirLocation, /*type range*/ tr, /*value range*/ vr, /*before*/
          [&](OpBuilder& builder, Location location, ValueRange vr) {
            // insert condition at tail of before scope.

            // FIXME: for now, I supposed that the last value of conRegion is used for comparation.
            // the condition region only have one block. The back() means the last op in this block.
            mlir::Operation* storeOp = nullptr;
            auto _backOp = &condRegion->front().back();
            auto _frontOp = &condRegion->front().front();
            while (_backOp != _frontOp) {
              if (mlir::isa<mlir::memref::StoreOp>(_backOp)) {
                storeOp = _backOp;
                break;
              } else {
                _backOp = _backOp->getPrevNode();
              }
            }
            mlir::Value oldCondValue;
            if (storeOp) {
              auto allocaOp = storeOp->getPrevNode();
              auto extuiOrTrunciOp = allocaOp->getPrevNode();
              if (mlir::isa<mlir::arith::TruncIOp>(extuiOrTrunciOp)) {
                oldCondValue = extuiOrTrunciOp->getResults()[0];
              } else {
                auto cmpiOp = extuiOrTrunciOp->getPrevNode();
                if (mlir::isa<mlir::arith::CmpIOp>(cmpiOp)
                    || mlir::isa<mlir::arith::CmpFOp>(cmpiOp)) {
                  oldCondValue = cmpiOp->getResults()[0];
                } else {
                  printf("[ Erro ] When getting arith.cmp op for scf condition failed. Missing "
                         "arith.cmp op\n");
                  exit(-1);
                }
              }

            } else {
              printf("[ Erro ] When getting arith.cmp op for scf condition failed. Missing "
                     "memref.store op\n");
              exit(-1);
            }
            mlir::ValueRange emptyVr;
            builder.create<mlir::scf::ConditionOp>(location, oldCondValue, emptyVr);
          },
          /*after*/
          [&](OpBuilder& builder, Location location, ValueRange vr) {
            /*do something*/
            builder.create<mlir::scf::YieldOp>(location);
          });

      // copy cond op to scfOpBeforeBlock
      auto scfOpBeforeBlock = &scfOp.getBefore().front();
      rewriter.inlineBlockBefore(&condRegion->front(), scfOpBeforeBlock, scfOpBeforeBlock->begin());

      // copy body op to scfOpAfterBlock
      auto scfOpAfterBlock = &scfOp.getAfter().front();
      rewriter.inlineBlockBefore(&bodyRegion->front(), scfOpAfterBlock, scfOpAfterBlock->begin());

      rewriter.replaceOp(op, scfOp);
    }

    return mlir::success();
  }
};

//===----------------------------------------------------------------------===//
// Convert aten.cast to arith.cast
//===----------------------------------------------------------------------===//
class AtenCastOpLowering : public OpConversionPattern<aten::CastOp> {
 public:
  using OpConversionPattern<aten::CastOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(aten::CastOp op, OpAdaptor adaptor,
                                mlir::ConversionPatternRewriter& rewriter) const override {
    // get all info and types
    auto castPredict = op.getPredicate();

    switch (castPredict) {
      case ::mlir::aten::CastPredicate::int_to_mlir_index: {
        // create arith.index_cast
        auto toNewType = getTypeConverter()->convertType(op.getType());
        rewriter.replaceOpWithNewOp<arith::IndexCastOp>(op, toNewType, adaptor.getInput());
        break;
      }
      case ::mlir::aten::CastPredicate::bool_to_int: {
        break;
      }
      case ::mlir::aten::CastPredicate::float_to_bool: {
        break;
      }
      case ::mlir::aten::CastPredicate::float_to_int: {
        auto toNewType = getTypeConverter()->convertType(op.getType());
        rewriter.replaceOpWithNewOp<mlir::arith::FPToSIOp>(op, toNewType, adaptor.getInput());
        break;
      }
      case ::mlir::aten::CastPredicate::floating: {
        break;
      }
      case ::mlir::aten::CastPredicate::int_to_bool: {
        break;
      }
      case ::mlir::aten::CastPredicate::int_to_float: {
        auto toNewType = getTypeConverter()->convertType(op.getType());
        rewriter.replaceOpWithNewOp<mlir::arith::SIToFPOp>(op, toNewType, adaptor.getInput());
        break;
      }
      case ::mlir::aten::CastPredicate::integral: {
        break;
      }
      case ::mlir::aten::CastPredicate::bool_to_mlir_i1: {
        rewriter.replaceOpWithNewOp<mlir::UnrealizedConversionCastOp>(
            op, /*resultT*/ rewriter.getI1Type(), adaptor.getInput());
        break;
      }
      case ::mlir::aten::CastPredicate::mlir_index_to_int: {
        auto toNewType = getTypeConverter()->convertType(op.getType());
        rewriter.replaceOpWithNewOp<mlir::arith::IndexCastOp>(op, toNewType, adaptor.getInput());
        break;
      }
      case ::mlir::aten::CastPredicate::mlir_int_to_aten_int: {
        rewriter.replaceOp(op, adaptor.getInput());
        break;
      }
      case ::mlir::aten::CastPredicate::aten_int_to_mlir_int: {
        rewriter.replaceOp(op, adaptor.getInput());
        break;
      }
      default: break;
    }

    return mlir::LogicalResult::success();
  }
};

//===----------------------------------------------------------------------===//
// Aten to mlir
//===----------------------------------------------------------------------===//
namespace {
class ConvertAtenToMlir : public impl::ConvertAtenToMlirBase<ConvertAtenToMlir> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                    mlir::memref::MemRefDialect, mlir::arith::ArithDialect,
                    mlir::cf::ControlFlowDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    RewritePatternSet patterns(&getContext());
    ConversionTarget target(getContext());

    auto converter = prepareTypeConverter();

    if (m_isClosure) {
      // set aten-lang as illegal
      target.addIllegalDialect<mlir::aten::AtenDialect>();

      // set those dialects as llegal
      target.addLegalDialect<mlir::arith::ArithDialect, mlir::affine::AffineDialect,
                             mlir::scf::SCFDialect, mlir::memref::MemRefDialect,
                             mlir::cf::ControlFlowDialect, mlir::func::FuncDialect>();
      target.addLegalOp<mlir::ModuleOp>();

      // prepare all patterns.
      populateAtenToMlirConversionPatterns_Closure(&patterns, converter);

      // do conversion and return if failured.
      if (failed(applyPartialConversion(getOperation(), target, std::move(patterns)))) {
        signalPassFailure();
      }
    } else {
      // set aten-lang as illegal
      // target.addIllegalDialect<mlir::aten::AtenDialect>();

      // set those dialects as llegal
      target.addLegalDialect<mlir::arith::ArithDialect, mlir::affine::AffineDialect,
                             mlir::scf::SCFDialect, mlir::memref::MemRefDialect,
                             mlir::cf::ControlFlowDialect, mlir::func::FuncDialect>();
      target.addLegalOp<mlir::ModuleOp>();

      // prepare all patterns.
      populateAtenToMlirConversionPatterns(&patterns, converter);

      // do conversion and return if failured.
      if (failed(applyPartialConversion(getOperation(), target, std::move(patterns)))) {
        signalPassFailure();
      }
    }
  }

  void setClosure(bool isClosure) { m_isClosure = isClosure; }

 private:
  bool m_isClosure = false;
};
}  // namespace

void populateAtenToMlirConversionPatterns(mlir::RewritePatternSet* patterns,
                                          mlir::TypeConverter& converter) {
  patterns->add<AtenReturnOpLowering>(patterns->getContext());

  patterns->add<AtenCmpOpLowering, AtenFuncOpLowering, AtenCallOpLowering, AtenUnaryOpLowering,
                AtenBinOpLowering, AtenLoadOpLowering, AtenConstOpLowering, AtenStoreOpLowering,
                AtenAllocaOpLowering, AtenIfOpLowering, AtenCastOpLowering, AtenYieldIfOpLowering>(
      converter, patterns->getContext());
}

void populateAtenToMlirConversionPatterns_Closure(mlir::RewritePatternSet* patterns,
                                                  mlir::TypeConverter& converter) {
  patterns->add<AtenReturnOpLowering>(patterns->getContext());

  patterns->add<AtenCmpOpLowering, AtenFuncOpLowering, AtenCallOpLowering, AtenUnaryOpLowering,
                AtenBinOpLowering, AtenLoadOpLowering, AtenConstOpLowering, AtenStoreOpLowering,
                AtenAllocaOpLowering, AtenIfOpLowering, AtenCastOpLowering, AtenYieldLoopOpLowering,
                AtenLoopOpLowering>(converter, patterns->getContext());
}

std::unique_ptr<mlir::Pass> createConvertAtenToMlirPass(bool isClosure) {
  auto res = std::make_unique<ConvertAtenToMlir>();
  res->setClosure(isClosure);
  return res;
}
}  // namespace nncv
}  // namespace mlir