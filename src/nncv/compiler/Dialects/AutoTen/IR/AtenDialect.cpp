#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenAttrs.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Diagnostics.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/FunctionImplementation.h"
#include "mlir/IR/Location.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/IR/StorageUniquerSupport.h"
#include "mlir/IR/TypeUtilities.h"
#include "mlir/Interfaces/InferTypeOpInterface.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Support/LogicalResult.h"

using namespace mlir;
using namespace mlir::aten;

#include "AutoTen/IR/AutoTenOpsEnums.cpp.inc"
#include "AutoTen/IR/AutoTenOpsAttributes.cpp.inc"
#include "AutoTen/IR/AutoTenOpsDialect.cpp.inc"

//===----------------------------------------------------------------------===//
// Check Constant Op
//===----------------------------------------------------------------------===//

// TODO

//===----------------------------------------------------------------------===//
// CastOp
//===----------------------------------------------------------------------===//
LogicalResult CastOp::verify() {
  auto resType = getResult().getType();
  auto inputType = getInput().getType();
  switch (getPredicate()) {
    case aten::CastPredicate::array_to_ptrdecay: {
      auto arrayPtrTy = inputType.dyn_cast<mlir::aten::PointerType>();
      auto dstPtrTy = resType.dyn_cast<mlir::aten::PointerType>();

      if (!arrayPtrTy || !dstPtrTy) {
        return emitOpError() << "The input and result should both be !aten.ptr. But get inputType["
                             << inputType << "], resultType[" << resType << "]";
      }

      auto arrayTy = arrayPtrTy.getPointee().dyn_cast<mlir::aten::ArrayType>();
      if (!arrayTy) {
        return emitOpError() << "requires !aten.array as pointee, but get " << inputType;
      }

      if (arrayTy.getEleT() != dstPtrTy.getPointee()) {
        return emitOpError() << "requires same type for array element and pointee result."
                             << "But get inputType[" << inputType << "], resultType[" << resType
                             << "]";
      }
      return success();
    }
    case aten::CastPredicate::int_to_bool: {
      if (!inputType.isa<mlir::aten::IntType>()) {
        return emitOpError() << "requires !aten.int type for input";
      }
      if (!resType.isa<mlir::aten::BoolType>()) {
        return emitOpError() << "requires !aten.bool type for result";
      }
      return success();
    }
    case aten::CastPredicate::int_to_float: {
      if (!inputType.isa<mlir::aten::IntType>()) {
        return emitOpError() << "requires !aten.int for input";
      }
      if (!resType.isa<mlir::aten::FloatType>()) {
        return emitOpError() << "requires !aten.float for result";
      }
      return success();
    }
    case aten::CastPredicate::float_to_bool: {
      if (!inputType.isa<mlir::aten::FloatType>()) {
        return emitOpError() << "requires float for input";
      }
      if (!resType.isa<mlir::aten::BoolType>()) {
        return emitOpError() << "requires !aten.bool for result";
      }
      return success();
    }
    case aten::CastPredicate::float_to_int: {
      if (!inputType.isa<mlir::aten::FloatType>()) {
        return emitOpError() << "requires float for input";
      }
      if (!resType.isa<mlir::aten::IntType>()) {
        return emitOpError() << "requires !aten.bool for result";
      }
      return success();
    }
    case aten::CastPredicate::bitcast: {
      if (!inputType.dyn_cast<mlir::aten::PointerType>()
          || !resType.dyn_cast<mlir::aten::PointerType>()) {
        return emitOpError() << "requires !aten.ptr type for input and result";
      }
      return success();
    }
    case aten::CastPredicate::bool_to_int: {
      if (!inputType.isa<mlir::aten::BoolType>()) {
        return emitOpError() << "requires float for input";
      }
      if (!resType.isa<mlir::aten::IntType>()) {
        return emitOpError() << "requires !aten.bool for result";
      }
      return success();
    }
    case aten::CastPredicate::floating: {
      if (!inputType.dyn_cast<mlir::aten::FloatType>()
          || !resType.dyn_cast<mlir::aten::FloatType>()) {
        return emitOpError() << "requries floating for input and result";
      }
      return success();
    }
    case aten::CastPredicate::integral: {
      if (!inputType.dyn_cast<mlir::aten::IntType>() || !resType.dyn_cast<mlir::aten::IntType>()) {
        return emitOpError() << "requries integer for input and result";
      }
      return success();
    }
  }
  llvm_unreachable("Unknown Cast way!");
}

//===----------------------------------------------------------------------===//
// Aten Unary Op
//===----------------------------------------------------------------------===//

// TODO
