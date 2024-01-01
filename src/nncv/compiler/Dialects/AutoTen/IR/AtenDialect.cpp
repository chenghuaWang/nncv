#ifndef _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#endif
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
#include "mlir/Interfaces/FunctionImplementation.h"
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
// Aten Dialect
//===----------------------------------------------------------------------===//
void aten::AtenDialect::initialize() {
  registerTypes();
  registerAttributes();
  addOperations<
#define GET_OP_LIST
#include "AutoTen/IR/AutoTenOps.cpp.inc"
      >();
}

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
      if (!resType.isa<mlir::FloatType>()) {
        return emitOpError() << "requires !aten.float for result";
      }
      return success();
    }
    case aten::CastPredicate::float_to_bool: {
      if (!inputType.isa<mlir::FloatType>()) { return emitOpError() << "requires float for input"; }
      if (!resType.isa<mlir::aten::BoolType>()) {
        return emitOpError() << "requires !aten.bool for result";
      }
      return success();
    }
    case aten::CastPredicate::float_to_int: {
      if (!inputType.isa<mlir::FloatType>()) { return emitOpError() << "requires float for input"; }
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
      if (!inputType.dyn_cast<mlir::FloatType>() || !resType.dyn_cast<mlir::FloatType>()) {
        return emitOpError() << "requires floating for input and result";
      }
      return success();
    }
    case aten::CastPredicate::integral: {
      if (!inputType.dyn_cast<mlir::aten::IntType>() || !resType.dyn_cast<mlir::aten::IntType>()) {
        return emitOpError() << "requires integer for input and result";
      }
      return success();
    }
  }
  llvm_unreachable("Unknown Cast way!");
}

//===----------------------------------------------------------------------===//
// Aten Unary Op
//===----------------------------------------------------------------------===//

LogicalResult UnaryOp::verify() {
  /// No need to guarantee any thing.
  switch (getPredicate()) {
    case aten::UnaryOpPredicate::Inc:
    case aten::UnaryOpPredicate::Dec:
    case aten::UnaryOpPredicate::Plus:
    case aten::UnaryOpPredicate::Minus:
    case aten::UnaryOpPredicate::Not:
      // Nothing to verify.
      return success();
  }
  return failure();
}

//===----------------------------------------------------------------------===//
// Aten Func Call Op
//===----------------------------------------------------------------------===//

OperandRange aten::CallOp::getArgOperands() { return {arg_operand_begin(), arg_operand_end()}; }

MutableOperandRange aten::CallOp::getArgOperandsMutable() { return getOperandsMutable(); }

CallInterfaceCallable aten::CallOp::getCallableForCallee() {
  return (*this)->getAttrOfType<SymbolRefAttr>("callee");
}

void aten::CallOp::setCalleeFromCallable(::mlir::CallInterfaceCallable callee) {
  if (auto calling = (*this)->getAttrOfType<mlir::SymbolRefAttr>(getCalleeAttrName()))
    (*this)->setAttr(getCalleeAttrName(), callee.get<mlir::SymbolRefAttr>());
  setOperand(0, callee.get<mlir::Value>());
}

LogicalResult aten::CallOp::verifySymbolUses(SymbolTableCollection& symbolTable) {
  // I just support flat attribute like what `func.func` does.
  // If you want nested symbol ref. I highly recommend you rename your symbol in a high level.
  auto funcAttr = (*this)->getAttrOfType<FlatSymbolRefAttr>("callee");
  if (!funcAttr) {
    // no callee is a indirect way.
    return success();
  }

  // check in the current module.
  FuncOp fn = symbolTable.lookupNearestSymbolFrom<mlir::aten::FuncOp>(*this, funcAttr);
  if (!fn) {
    return emitOpError() << "'" << funcAttr.getValue() << "' does not reference a valid function";
  }

  auto funcType = fn.getFunctionType();

  // func only have one return, so check it first for effective.
  if (funcType.isVoid() && getNumResults() != 0) {
    return emitOpError("callee returns void but call has results");
  }
  if (!funcType.isVoid() && getNumResults() != 1) {
    return emitOpError("incorrect number of results for callee");
  }
  if (!funcType.isVoid() && getResultTypes().front() != funcType.getReturnType()) {
    // parent function and return value types must match.
    // such as:
    // %0 = func.call() -> f32
    // check if %0 is f32 and ret is f32.
    return emitOpError("result type mismatch: expected ")
           << funcType.getReturnType() << ", but provided " << getResult(0).getType();
  }

  if (!funcType.isVarArg() && (getNumOperands() != funcType.getNumInputs())) {
    return emitOpError("incorrect number of operands for callee")
           << ", suppose nums: " << getNumOperands()
           << ", but get nums: " << funcType.getNumInputs();
  }
  for (unsigned i = 0, e = funcType.getNumInputs(); i != e; ++i) {
    if (getOperand(i).getType() != funcType.getInput(i)) {
      return emitOpError("operand type mismatch: expected operand type ")
             << funcType.getInput(i) << ", but provided " << getOperand(i).getType()
             << " for operand number " << i;
    }
  }

  return success();
}

ParseResult CallOp::parse(OpAsmParser& parser, OperationState& result) {
  mlir::FlatSymbolRefAttr calleeAttr;
  llvm::SmallVector<OpAsmParser::UnresolvedOperand, 4> ops;
  llvm::SMLoc opsLoc;
  (void)opsLoc;
  llvm::ArrayRef<mlir::Type> operandsTypes;
  llvm::ArrayRef<mlir::Type> allResultTypes;

  if (!parser.parseOptionalAttribute(calleeAttr, "callee", result.attributes).has_value()) {
    // enter in indirect call.
    OpAsmParser::UnresolvedOperand indirectVal;
    if (parser.parseOperand(indirectVal).failed()) { return failure(); }
    ops.push_back(indirectVal);
  }

  if (parser.parseLParen()) { return failure(); }

  opsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(ops)) { return failure(); }
  if (parser.parseRParen()) { return failure(); }
  if (parser.parseOptionalAttrDict(result.attributes)) { return failure(); }
  if (parser.parseColon()) { return failure(); }

  FunctionType opsFnTy;
  if (parser.parseType(opsFnTy)) { return failure(); }
  operandsTypes = opsFnTy.getInputs();
  allResultTypes = opsFnTy.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(ops, operandsTypes, opsLoc, result.operands)) { return failure(); }
  return success();
}

void CallOp::print(OpAsmPrinter& p) {
  auto operands = getOperands();
  p << ' ';
  if (getCallee()) {
    // direct call such as:
    // func.call @symbol : () -> ()
    p.printAttributeWithoutType(getCalleeAttr());
  } else {
    // indirect call such as:
    // %func = func.constant @my_func : (tensor<16xf32>, tensor<16xf32>) -> tensor<16xf32>
    // %result = func.call_indirect %func(%0, %1) : (tensor<16xf32>, tensor<16xf32>) ->
    // tensor<16xf32>
    p << operands.front();
    operands = operands.drop_front();
  }
  p << "(";
  p << operands;
  p << ")";
  llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("callee");
  // If the specified operation has attributes, print out an attribute dictionary with their values.
  // elidedAttrs allows the client to ignore specific well known attributes, commonly used if the
  // attribute value is printed some other way (like as a fixed operand).
  p.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  p << ' ' << ":";
  p << ' ';
  p.printFunctionalType(getOperands().getTypes(), getOperation()->getResultTypes());
}

//===----------------------------------------------------------------------===//
// Aten Func Op
//===----------------------------------------------------------------------===//

/// How to build a FuncOp
void aten::FuncOp::build(OpBuilder& builder, OperationState& result, StringRef name,
                         aten::FuncType type, ArrayRef<NamedAttribute> attrs,
                         ArrayRef<DictionaryAttr> argAttrs) {
  // Create a region that should be attached to the operation.
  result.addRegion();

  // attach this result with specified name (symbol).
  result.addAttribute(SymbolTable::getSymbolAttrName(), builder.getStringAttr(name));
  result.addAttribute(getFunctionTypeAttrName(result.name), TypeAttr::get(type));
  result.attributes.append(attrs.begin(), attrs.end());

  if (argAttrs.empty()) return;

  function_interface_impl::addArgAndResultAttrs(builder, result, argAttrs, std::nullopt,
                                                getArgAttrsAttrName(result.name),
                                                getResAttrsAttrName(result.name));
}

/// How to parse a FuncOp
ParseResult aten::FuncOp::parse(OpAsmParser& parser, OperationState& state) {
  llvm::SMLoc loc = parser.getCurrentLocation();

  // parse visibility
  auto visNameAttr = getSymVisibilityAttrName(state.name);
  ::llvm::StringRef visAttrStr;
  if (parser.parseOptionalKeyword(&visAttrStr, {"private", "public", "nested"}).succeeded()) {
    state.addAttribute(visNameAttr, parser.getBuilder().getStringAttr(visAttrStr));
  }

  StringAttr nameAttr;
  SmallVector<OpAsmParser::Argument, 8> arguments;
  SmallVector<DictionaryAttr, 1> argAttrs;
  SmallVector<DictionaryAttr, 1> resultAttrs;
  SmallVector<Type, 8> argTypes;
  SmallVector<Type, 4> resultTypes;
  auto& builder = parser.getBuilder();

  // parse the func name as a symbol.
  if (parser.parseSymbolName(nameAttr, SymbolTable::getSymbolAttrName(), state.attributes)) {
    return failure();
  }

  // parse the func args, types.
  bool isVariadic = false;
  if (function_interface_impl::parseFunctionSignature(parser, true, arguments, isVariadic,
                                                      resultTypes, resultAttrs)) {
    return failure();
  }
  for (auto& arg : arguments) argTypes.push_back(arg.type);
  if (resultTypes.size() > 1) {
    return parser.emitError(loc, "functions only supports results size <= 1");
  }

  // set return type to empty if return is void.
  mlir::Type returnType =
      (resultTypes.empty() ? mlir::aten::VoidType::get(builder.getContext()) : resultTypes.front());

  // build the func type
  auto funcType = mlir::aten::FuncType::get(argTypes, returnType, isVariadic);
  if (!funcType) { return failure(); }
  state.addAttribute(getFunctionTypeAttrName(state.name), TypeAttr::get(funcType));
  if (parser.parseOptionalAttrDictWithKeyword(state.attributes)) { return failure(); }

  // add the attributes to the function arguments.
  assert(resultAttrs.size() == resultTypes.size() && "resultAttrs.size() != resultTypes.size()");
  function_interface_impl::addArgAndResultAttrs(builder, state, arguments, resultAttrs,
                                                getArgAttrsAttrName(state.name),
                                                getResAttrsAttrName(state.name));

  // parse extra attr
  NamedAttrList extraAttrs;
  if (::mlir::succeeded(parser.parseOptionalKeyword("extra"))) {
    if (parser.parseLParen().failed()) { return failure(); }
    if (parser.parseOptionalAttrDict(extraAttrs).failed()) { return failure(); }
    if (parser.parseRParen().failed()) { return failure(); }
  }
  state.addAttribute(getExtraAttrsAttrName(state.name),
                     mlir::aten::ExtFuncAttr::get(builder.getContext(),
                                                  extraAttrs.getDictionary(builder.getContext())));

  // parse the optional region.
  auto* body = state.addRegion();
  OptionalParseResult parseResult =
      parser.parseOptionalRegion(*body, arguments, /*enableNameShadowing=*/false);
  if (parseResult.has_value()) {
    if (failed(*parseResult)) { return failure(); }
    if (body->empty()) {
      return parser.emitError(loc, "you give the function body, but this body is empty.");
    }
  }
  return success();
}

/// How to print FuncOp in MLIR.
void aten::FuncOp::print(OpAsmPrinter& p) {
  // indent.
  p << ' ';

  // visiblity is MLIR's response
  auto vis = getVisibility();
  p << vis << " ";

  // print function name, args, types.
  p.printSymbolName(getSymName());
  auto funcType = getFunctionType();
  llvm::SmallVector<Type, 1> resultType;
  if (!funcType.isVoid()) {
    // let mlir do it.
    function_interface_impl::printFunctionSignature(p, *this, funcType.getInputs(),
                                                    funcType.isVarArg(), funcType.getReturnTypes());
  } else {
    function_interface_impl::printFunctionSignature(p, *this, funcType.getInputs(),
                                                    funcType.isVarArg(), {});  // none return.
  }

  // print function attr
  function_interface_impl::printFunctionAttributes(
      p, *this, {getSymVisibilityAttrName(), getFunctionTypeAttrName(), getExtraAttrsAttrName()});
  if (!getExtraAttrs().getElements().empty()) {
    p << " extra(";
    p.printOptionalAttrDict(getExtraAttrs().getElements().getValue());
    p << " )";
  }

  // print the body if this is not an external function.
  Region& body = getOperation()->getRegion(0);
  if (!body.empty()) {
    p << ' ';
    p.printRegion(body, false, true);
  }
}

bool aten::FuncOp::isDeclaration() { return isExternal(); }

Region* aten::FuncOp::getCallableRegion() { return isExternal() ? nullptr : &getBody(); }

LogicalResult aten::FuncOp::verifyType() {
  auto type = getFunctionType();
  if (!type.isa<aten::FuncType>()) {
    return emitOpError("requires '" + getFunctionTypeAttrName().str()
                       + "' attribute as function type");
  }
  return success();
}

LogicalResult aten::FuncOp::verify() { return success(); }

//===----------------------------------------------------------------------===//
// Check Constant Op
//===----------------------------------------------------------------------===//

static mlir::LogicalResult __checkConstantTypes(Operation* op, Type opType,
                                                mlir::Attribute attrType) {
  /// Bool := boolAttr
  if (attrType.isa<mlir::aten::BoolAttr>()) {
    if (!opType.isa<mlir::aten::BoolType>()) {
      return op->emitOpError("result type (")
             << opType << ") must be '!aten.bool' for '" << attrType << "'";
    }
    return success();
  }

  /// ptr<?> := NilAttr
  if (attrType.isa<mlir::aten::NilAttr>()) {
    if (!opType.isa<mlir::aten::PointerType>()) {
      return op->emitOpError("result type (")
             << opType << ") must be '!aten.ptr<?>' for '" << attrType << "'";
    }
  }

  /// int | float := IntAttr | Float Attr
  if (attrType.isa<IntegerAttr, mlir::FloatAttr>()) {
    auto attr = attrType.cast<TypedAttr>();
    if (attr.getType() != opType) {
      return op->emitOpError("result type (")
             << opType << ") does not match value type (" << attr.getType() << ")";
    }
    return success();
  }

  if (attrType.isa<SymbolRefAttr>()) {
    if (opType.isa<::mlir::aten::PointerType>()) { return success(); }
    return op->emitOpError("To ref a symbol you need pointer type, but get pointer type(")
           << opType << "), with attribute " << attrType;
  }

  if (attrType.isa<mlir::aten::ConstArrayAttr>() || attrType.isa<mlir::aten::ConstStructAttr>()) {
    return success();
  }

  if (attrType.isa<mlir::aten::IntAttr>()) { return success(); }

  return op->emitOpError("type ") << attrType.cast<TypedAttr>().getType() << " not supported";
}

LogicalResult ConstantOp::verify() {
  return __checkConstantTypes(getOperation(), getType(), getValue());
}

static ParseResult parseConstantValue(OpAsmParser& parser, mlir::Attribute& valueAttr) {
  NamedAttrList attr;
  if (parser.parseAttribute(valueAttr, "value", attr).failed()) {
    return parser.emitError(parser.getCurrentLocation(),
                            "expected constant attribute to match type");
  }

  return success();
}

static void printConstant(OpAsmPrinter& p, Attribute value) { p.printAttribute(value); }

static void printConstantValue(OpAsmPrinter& p, aten::ConstantOp op, Attribute value) {
  printConstant(p, value);
}

OpFoldResult ConstantOp::fold(FoldAdaptor /*adaptor*/) { return getValue(); }

//===----------------------------------------------------------------------===//
// Aten Func Return Op
//===----------------------------------------------------------------------===//

static LogicalResult __checkReturnAndFunction(ReturnOp op, aten::FuncOp function) {
  if (op.getNumOperands() > 1) { return op.emitOpError() << "expects at most 1 return operand"; }

  auto expectedTy = function.getFunctionType().getReturnType();
  auto actualTy = (op.getNumOperands() == 0 ? mlir::aten::VoidType::get(op.getContext())
                                            : op.getOperand(0).getType());
  if (actualTy != expectedTy) {
    return op.emitOpError() << "returns " << actualTy << " but function op requires you to returns "
                            << expectedTy;
  }
  return mlir::success();
}

LogicalResult ReturnOp::verify() {
  auto* fnOp = getOperation()->getParentOp();
  if (__checkReturnAndFunction(*this, cast<aten::FuncOp>(fnOp)).failed()) { return failure(); }

  return success();
}

//===----------------------------------------------------------------------===//
// Aten make_struct_symbol
//===----------------------------------------------------------------------===//

void aten::MakeStructSymbol::build(OpBuilder& odsBuilder, OperationState& odsState,
                                   StringRef sym_name, Type sym_type) {
  odsState.addAttribute(getSymNameAttrName(odsState.name), odsBuilder.getStringAttr(sym_name));
  odsState.addAttribute(getSymTypeAttrName(odsState.name), ::mlir::TypeAttr::get(sym_type));
}

LogicalResult aten::MakeStructSymbol::verify() { return success(); }

static void printStructSymbolOpTypeAndInitialValue(OpAsmPrinter& p, MakeStructSymbol op,
                                                   TypeAttr type, Attribute initAttr,
                                                   mlir::Region& ctorRegion) {
  if (initAttr) { op->emitError("initAttr is optional, but you should set it to None!!!"); }
  if (!ctorRegion.empty()) {
    op->emitError("ctorRegion is optional, but you should set it to None!!!");
  }
  p << ": " << type;
}

static ParseResult parseStructSymbolOpTypeAndInitialValue(OpAsmParser& parser, TypeAttr& typeAttr,
                                                          Attribute& initialValueAttr,
                                                          mlir::Region& ctorRegion) {
  mlir::Type opTy;
  if (parser.parseColonType(opTy)) { return failure(); }
  typeAttr = TypeAttr::get(opTy);
  return success();
}

//===----------------------------------------------------------------------===//
// Aten Get Ref Op.
//===----------------------------------------------------------------------===//

LogicalResult aten::GetRefOp::inferReturnTypes(
    ::mlir::MLIRContext* context, ::std::optional<::mlir::Location> location,
    ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes,
    ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions,
    ::llvm::SmallVectorImpl<::mlir::Type>& inferredReturnTypes) {
  if (operands.size() != 1) { return failure(); }
  auto theType = operands[0].getType();
  auto ptr2TheType = aten::PointerType::get(context, theType);
  inferredReturnTypes.insert(inferredReturnTypes.end(), ptr2TheType);
  return success();
}

//===----------------------------------------------------------------------===//
// Aten Load Op
//===----------------------------------------------------------------------===//

LogicalResult aten::LoadOp::verify() { return success(); }

//===----------------------------------------------------------------------===//
// Aten store Op
//===----------------------------------------------------------------------===//

LogicalResult aten::StoreOp::verify() { return success(); }

//===----------------------------------------------------------------------===//
// Aten MakeStructSymbol Op.
//===----------------------------------------------------------------------===//

void aten::MakeStructSymbol::getSuccessorRegions(mlir::RegionBranchPoint point,
                                                 SmallVectorImpl<RegionSuccessor>& regions) {
  auto region = &getCtorRegion();
  region = nullptr;
}

//===----------------------------------------------------------------------===//
// Aten self defined traits
//===----------------------------------------------------------------------===//

LogicalResult OpTrait::impl::verifySameFirstOperandAndResultType(Operation* op) {
  if (failed(verifyAtLeastNOperands(op, 1)) || failed(verifyOneResult(op))) return failure();

  auto type = op->getResult(0).getType();
  auto opType = op->getOperand(0).getType();

  if (type != opType)
    return op->emitOpError() << "requires the same type for first operand and result";

  return success();
}

#define GET_OP_CLASSES
#include "AutoTen/IR/AutoTenOps.cpp.inc"