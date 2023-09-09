#ifndef _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#endif
#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenAttrs.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"

#include "mlir/IR/Attributes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinAttributeInterfaces.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/Location.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Support/LogicalResult.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/TypeSwitch.h"

using namespace mlir;
using namespace mlir::aten;

static void printStructMembers(AsmPrinter& p, ArrayAttr members);
static ParseResult parseStructMembers(AsmParser& parser, ArrayAttr& members);

#define GET_ATTRDEF_CLASSES
#include "AutoTen/IR/AutoTenOpsAttributes.cpp.inc"

mlir::Attribute AtenDialect::parseAttribute(DialectAsmParser& parser, mlir::Type type) const {
  llvm::SMLoc typeLoc = parser.getCurrentLocation();
  StringRef mnemonic;
  Attribute genAttr;
  OptionalParseResult parseResult = generatedAttributeParser(parser, &mnemonic, type, genAttr);
  if (parseResult.has_value()) return genAttr;
  parser.emitError(typeLoc, "unknown attribute in Aten dialect");
  return Attribute();
}

void AtenDialect::printAttribute(Attribute attr, DialectAsmPrinter& os) const {
  if (failed(generatedAttributePrinter(attr, os))) llvm_unreachable("unexpected Aten type kind");
}

//===----------------------------------------------------------------------===//
// Struct Members
//===----------------------------------------------------------------------===//

static void printStructMembers(AsmPrinter& p, ArrayAttr members) {
  p << '{';
  llvm::interleaveComma(members, p);
  p << '}';
}

static ParseResult parseStructMembers(AsmParser& parser, ArrayAttr& members) {
  SmallVector<Attribute, 4> elts;

  auto delimiter = AsmParser::Delimiter::Braces;

  auto result = parser.parseCommaSeparatedList(delimiter, [&]() {
    TypedAttr attr;
    if (parser.parseAttribute(attr).failed()) return failure();
    elts.push_back(attr);
    return success();
  });

  if (result.failed()) return failure();

  members = ArrayAttr::get(parser.getContext(), elts);
  return success();
}

//===----------------------------------------------------------------------===//
// Const Struct Attr
//===----------------------------------------------------------------------===//

LogicalResult ConstStructAttr::verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError,
                                      ::mlir::Type type, ArrayAttr members) {
  auto theType = type.dyn_cast_or_null<mlir::aten::StructType>();
  if (!theType) {
    emitError() << "expected !aten.struct type, but get " << theType;
    return failure();
  }

  if (theType.getMembers().size() != members.size()) {
    emitError() << "Type: " << theType << " has member size " << theType.getMembers().size()
                << " , but get size: " << members.size() << " when init it";
    return failure();
  }

  unsigned attrIdx = 0;
  for (auto& member : theType.getMembers()) {
    auto m = members[attrIdx].dyn_cast_or_null<TypedAttr>();
    if (!m) {
      emitError() << "expected mlir::TypedAttr attribute";
      return failure();
    }
    if (member != m.getType()) {
      emitError() << "element at index " << attrIdx << " has type " << m.getType()
                  << " but return type for this element is " << member;
      return failure();
    }
    attrIdx++;
  }

  return success();
}

//===----------------------------------------------------------------------===//
// Int Attr
//===----------------------------------------------------------------------===//

LogicalResult IntAttr::verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError,
                              ::mlir::Type type, APInt value) {
  if (!type.isa<aten::IntType>()) {
    emitError() << "expected int type(i1, i8, i16, i32, i64)";
    return failure();
  }

  auto intType = type.cast<aten::IntType>();

  if (intType.getWidth() != 1 || intType.getWidth() != 8 || intType.getWidth() != 16
      || intType.getWidth() != 32 || intType.getWidth() != 64) {
    emitError() << "expected width in [1, 8, 16, 32, 64], but get width: " << intType.getWidth();
  }

  if (value.getBitWidth() != intType.getWidth()) {
    emitError() << "type and value's bit width mismatch: " << intType.getWidth()
                << " != " << value.getBitWidth();
    return failure();
  }
  return success();
}

Attribute aten::IntAttr::parse(::mlir::AsmParser& odsParser, ::mlir::Type odsType) {
  mlir::APInt APValue;

  if (!odsType.isa<IntType>()) { return {}; }
  auto type = odsType.cast<aten::IntType>();

  // eats `<`
  if (odsParser.parseLess()) return {};

  if (type.isSigned()) {
    int64_t value;
    if (odsParser.parseInteger(value)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "expected integer value");
    }
    APValue = mlir::APInt(type.getWidth(), value, type.isSigned());
    if (APValue.getSExtValue() != value) {
      odsParser.emitError(odsParser.getCurrentLocation(),
                          "integer value too large for the given type");
    }
  } else {
    uint64_t value;
    if (odsParser.parseInteger(value)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "expected integer value");
    }
    APValue = mlir::APInt(type.getWidth(), value, type.isSigned());
    if (APValue.getZExtValue() != value) {
      odsParser.emitError(odsParser.getCurrentLocation(),
                          "integer value too large for the given type");
    }
  }

  // eats `>`
  if (odsParser.parseGreater()) { return {}; }

  return IntAttr::get(type, APValue);
}

void aten::IntAttr::print(::mlir::AsmPrinter& odsPrinter) const {
  auto type = getType().cast<IntType>();
  odsPrinter << '<';
  if (type.isSigned()) {
    odsPrinter << getSInt();
  } else {
    odsPrinter << getUInt();
  }
  odsPrinter << '>';
}

//===----------------------------------------------------------------------===//
// Const Array Attr
//===----------------------------------------------------------------------===//

void ConstArrayAttr::print(::mlir::AsmPrinter& odsPrinter) const {
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElts());
  odsPrinter << ">";
}

mlir::Attribute ConstArrayAttr::parse(::mlir::AsmParser& odsParser, ::mlir::Type odsType) {
  ::mlir::FailureOr<::mlir::Type> resultTy;
  ::mlir::FailureOr<Attribute> resultVal;
  ::llvm::SMLoc loc = odsParser.getCurrentLocation();
  (void)loc;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  resultVal = ::mlir::FieldParser<Attribute>::parse(odsParser);
  if (failed(resultVal)) {
    odsParser.emitError(odsParser.getCurrentLocation(),
                        "failed to parse ConstArrayAttr parameter 'value' which is "
                        "to be a `Attribute`");
    return {};
  }

  // ArrayAttrrs have per-element type, not the type of the array...
  if (resultVal->dyn_cast<ArrayAttr>()) {
    // Array has implicit type: infer from const array type.
    if (odsParser.parseOptionalColon().failed()) {
      resultTy = odsType;
    } else {  // Array has explicit type: parse it.
      resultTy = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
      if (failed(resultTy)) {
        odsParser.emitError(odsParser.getCurrentLocation(),
                            "failed to parse ConstArrayAttr parameter 'type' which is "
                            "to be a `::mlir::Type`");
        return {};
      }
    }
  } else {
    assert(resultVal->isa<TypedAttr>() && "IDK");
    auto ta = resultVal->cast<TypedAttr>();
    resultTy = ta.getType();
    if (resultTy->isa<mlir::NoneType>()) {
      odsParser.emitError(odsParser.getCurrentLocation(),
                          "expected type declaration for string literal");
      return {};
    }
  }

  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  return odsParser.getChecked<ConstArrayAttr>(loc, odsParser.getContext(), resultTy.value(),
                                              resultVal.value());
}

LogicalResult mlir::aten::ConstArrayAttr::verify(
    ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type type,
    Attribute attr) {
  if (!(attr.isa<mlir::ArrayAttr>() || attr.isa<mlir::StringAttr>()))
    return emitError() << "constant array expects ArrayAttr or StringAttr";

  if (auto strAttr = attr.dyn_cast<mlir::StringAttr>()) {
    mlir::aten::ArrayType at = type.cast<mlir::aten::ArrayType>();
    auto intTy = at.getEleT().dyn_cast<aten::IntType>();

    if (!intTy || intTy.getWidth() != 8) {
      emitError() << "constant array element for string literals expects "
                     "!cir.int<u, 8> element type";
      return failure();
    }
    return success();
  }

  assert(attr.isa<mlir::ArrayAttr>());
  auto arrayAttr = attr.cast<mlir::ArrayAttr>();
  auto at = type.cast<ArrayType>();

  // Make sure both number of elements and subelement types match type.
  if (at.getSizeT() != arrayAttr.size())
    return emitError() << "constant array size should match type size";
  LogicalResult eltTypeCheck = success();
  arrayAttr.walkImmediateSubElements(
      [&](Attribute attr) {
        // Once we find a mismatch, stop there.
        if (eltTypeCheck.failed()) return;
        auto typedAttr = attr.dyn_cast<TypedAttr>();
        if (!typedAttr || typedAttr.getType() != at.getEleT()) {
          eltTypeCheck = failure();
          emitError() << "constant array element should match array element type";
        }
      },
      [&](Type type) {});
  return eltTypeCheck;
}

//===----------------------------------------------------------------------===//
// Aten Dialect Register
//===----------------------------------------------------------------------===//

void AtenDialect::registerAttributes() {
  addAttributes<
#define GET_ATTRDEF_LIST
#include "AutoTen/IR/AutoTenOpsAttributes.cpp.inc"
      >();
}
