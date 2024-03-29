#ifndef _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#include <cstdint>
#endif
#include "mlir/IR/Types.h"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"

#include "mlir/IR/Attributes.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/Support/LogicalResult.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/TypeSwitch.h"
#include "llvm/Support/ErrorHandling.h"

static ::mlir::ParseResult parseFuncTypeArgs(::mlir::AsmParser& p,
                                             ::llvm::SmallVector<::mlir::Type>& params,
                                             bool& isVarArg);
static void printFuncTypeArgs(::mlir::AsmPrinter& p, ::mlir::ArrayRef<::mlir::Type> params,
                              bool isVarArg);

#define GET_TYPEDEF_CLASSES
#include "AutoTen/IR/AutoTenOpsTypes.cpp.inc"

using namespace mlir;
using namespace mlir::aten;

mlir::Type AtenDialect::parseType(DialectAsmParser& parser) const {
  llvm::SMLoc typeLoc = parser.getCurrentLocation();
  StringRef mnemonic;
  Type genType;
  OptionalParseResult parseResult = generatedTypeParser(parser, &mnemonic, genType);
  if (parseResult.has_value()) return genType;
  parser.emitError(typeLoc, "unknown type in Aten dialect");
  return mlir::Type();
}

void AtenDialect::printType(Type type, DialectAsmPrinter& os) const {
  if (failed(generatedTypePrinter(type, os))) llvm_unreachable("unexpected Aten type kind");
}

//===----------------------------------------------------------------------===//
// Char Type
//===----------------------------------------------------------------------===//

/// printer
void CharType::print(mlir::AsmPrinter& p) const {
  p << '<';
  p << getWidth();
  p << '>';
}

/// parser
mlir::Type CharType::parse(mlir::AsmParser& p) {
  unsigned width;

  if (p.parseLess()) { return mlir::Type(); }
  if (p.parseInteger(width)) { return mlir::Type(); }
  if (width != 8 && width != 16) { return mlir::Type(); }
  if (p.parseGreater()) return mlir::Type();

  return CharType::get(p.getContext(), width, /*isUtf*/ width == 8 ? false : true);
}

//===----------------------------------------------------------------------===//
// Int Type
//===----------------------------------------------------------------------===//

/// printer
void IntType::print(mlir::AsmPrinter& p) const {
  auto sign = isSigned() ? 's' : 'u';
  p << '<';
  p << sign;
  p << ", ";
  p << getWidth();
  p << '>';
}

/// parser
mlir::Type IntType::parse(mlir::AsmParser& p) {
  bool isSigned;
  unsigned width;

  if (p.parseLess()) { return mlir::Type(); }

  llvm::StringRef sign;
  if (p.parseKeyword(&sign)) return mlir::Type();
  if (sign.equals("s")) {
    isSigned = true;
  } else if (sign.equals("u")) {
    isSigned = false;
  } else {
    return mlir::Type();
  }

  if (p.parseComma()) { return mlir::Type(); }
  if (p.parseInteger(width)) { return mlir::Type(); }

  if (width != 1 && width != 8 && width != 16 && width != 32 && width != 64) {
    return mlir::Type();
  }

  if (p.parseGreater()) return mlir::Type();

  return IntType::get(p.getContext(), width, isSigned);
}

//===----------------------------------------------------------------------===//
// Pointer Type
//===----------------------------------------------------------------------===//

/// printer
void PointerType::print(mlir::AsmPrinter& p) const {
  p << "<";
  p.printType(getPointee());
  p << '>';
}

/// parser
mlir::Type PointerType::parse(mlir::AsmParser& p) {
  // eats `<`
  if (p.parseLess()) { return mlir::Type(); }
  mlir::Type pointeeType;

  // parse normal type
  if (p.parseType(pointeeType)) { return mlir::Type(); }

  // eats '>'
  if (p.parseGreater()) { return mlir::Type(); }

  return PointerType::get(p.getContext(), pointeeType);
}

//===----------------------------------------------------------------------===//
// Bool Type
//===----------------------------------------------------------------------===//

/// printer
void BoolType::print(mlir::AsmPrinter& p) const {
  // just have !aten.bool, no other types include.
}

/// parser
mlir::Type BoolType::parse(mlir::AsmParser& p) { return BoolType::get(p.getContext()); }

//===----------------------------------------------------------------------===//
// Struct Type
// FIXME: `body` is dropped in struct arguments.
//===----------------------------------------------------------------------===//

/// printer
void StructType::print(mlir::AsmPrinter& p) const {
  // !aten.struct<"Name", Type, Type>
  p << "<";
  p << getTypeName();

  auto members = getMembers();
  if (!members.empty()) {
    p << ", ";
    llvm::interleaveComma(getMembers(), p);
  }

  p << ">";
}

/// parser
mlir::Type StructType::parse(mlir::AsmParser& p) {
  if (p.parseLess()) { return mlir::Type(); }
  std::string typeName;
  if (p.parseString(&typeName)) { return Type(); }

  llvm::SmallVector<Type> members;

  while (mlir::succeeded(p.parseOptionalComma())) {
    mlir::Type nextMember;
    auto optTy = p.parseOptionalType(nextMember);
    if (optTy.has_value()) {
      if (failed(*optTy)) return Type();
      members.push_back(nextMember);
      continue;
    }
  }

  if (p.parseGreater()) return Type();
  auto sTy = StructType::get(p.getContext(), members, typeName, true);
  return sTy;
}

//===----------------------------------------------------------------------===//
// Int Type Data layout info
//===----------------------------------------------------------------------===//

uint64_t IntType::getABIAlignment(const mlir::DataLayout& dataLayout,
                                  mlir::DataLayoutEntryListRef params) const {
  return (getWidth() == 1) ? 1 : (unsigned)(getWidth() / 8);
}

llvm::TypeSize IntType::getTypeSizeInBits(const mlir::DataLayout& dataLayout,
                                          mlir::DataLayoutEntryListRef params) const {
  return llvm::TypeSize::getFixed(getWidth());
}

uint64_t IntType::getPreferredAlignment(const ::mlir::DataLayout& dataLayout,
                                        ::mlir::DataLayoutEntryListRef params) const {
  return (getWidth() == 1) ? 1 : (uint64_t)(getWidth() / 8);
}

//===----------------------------------------------------------------------===//
// Char Type Data layout info
//===----------------------------------------------------------------------===//

uint64_t CharType::getABIAlignment(const mlir::DataLayout& dataLayout,
                                   mlir::DataLayoutEntryListRef params) const {
  return (uint64_t)(getWidth() / 8);
}

llvm::TypeSize CharType::getTypeSizeInBits(const mlir::DataLayout& dataLayout,
                                           mlir::DataLayoutEntryListRef params) const {
  return llvm::TypeSize::getFixed(getWidth());
}

uint64_t CharType::getPreferredAlignment(const ::mlir::DataLayout& dataLayout,
                                         ::mlir::DataLayoutEntryListRef params) const {
  return (uint64_t)(getWidth() / 8);
}

//===----------------------------------------------------------------------===//
// Bool Type Data layout info: Be careful with bool type's ABI setting.
//===----------------------------------------------------------------------===//

uint64_t BoolType::getABIAlignment(const ::mlir::DataLayout& dataLayout,
                                   ::mlir::DataLayoutEntryListRef params) const {
  return 1;
}

llvm::TypeSize BoolType::getTypeSizeInBits(const ::mlir::DataLayout& dataLayout,
                                           ::mlir::DataLayoutEntryListRef params) const {
  return llvm::TypeSize::getFixed(8);
}

uint64_t BoolType::getPreferredAlignment(const ::mlir::DataLayout& dataLayout,
                                         ::mlir::DataLayoutEntryListRef params) const {
  return 1;
}

//===----------------------------------------------------------------------===//
// Pointer Type Data layout info
//===----------------------------------------------------------------------===//

uint64_t PointerType::getABIAlignment(const ::mlir::DataLayout& dataLayout,
                                      ::mlir::DataLayoutEntryListRef params) const {
  return 8;
}

llvm::TypeSize PointerType::getTypeSizeInBits(const ::mlir::DataLayout& dataLayout,
                                              ::mlir::DataLayoutEntryListRef params) const {
  return llvm::TypeSize::getFixed(64);
  ;
}

uint64_t PointerType::getPreferredAlignment(const ::mlir::DataLayout& dataLayout,
                                            ::mlir::DataLayoutEntryListRef params) const {
  return 8;
}

//===----------------------------------------------------------------------===//
// Array Type Data layout info
//===----------------------------------------------------------------------===//

uint64_t ArrayType::getABIAlignment(const ::mlir::DataLayout& dataLayout,
                                    ::mlir::DataLayoutEntryListRef params) const {
  return dataLayout.getTypeABIAlignment(getEleT());
}

llvm::TypeSize ArrayType::getTypeSizeInBits(const ::mlir::DataLayout& dataLayout,
                                            ::mlir::DataLayoutEntryListRef params) const {
  return llvm::TypeSize::getFixed(getSizeT() * dataLayout.getTypeSizeInBits(getEleT()));
}

uint64_t ArrayType::getPreferredAlignment(const ::mlir::DataLayout& dataLayout,
                                          ::mlir::DataLayoutEntryListRef params) const {
  return dataLayout.getTypePreferredAlignment(getEleT());
}

//===----------------------------------------------------------------------===//
// Struct Type Data layout info
//===----------------------------------------------------------------------===//

llvm::TypeSize StructType::getTypeSizeInBits(const ::mlir::DataLayout& dataLayout,
                                             ::mlir::DataLayoutEntryListRef params) const {
  if (!StructType::size) { computeSizeAndAlignment(dataLayout); }
  return llvm::TypeSize::getFixed(*StructType::size * 8);
}

uint64_t StructType::getABIAlignment(const ::mlir::DataLayout& dataLayout,
                                     ::mlir::DataLayoutEntryListRef params) const {
  if (!StructType::align) { computeSizeAndAlignment(dataLayout); }
  return *StructType::align;
}

uint64_t StructType::getPreferredAlignment(const ::mlir::DataLayout& dataLayout,
                                           ::mlir::DataLayoutEntryListRef params) const {
  llvm_unreachable("NYI");
}

bool StructType::isPadded(const ::mlir::DataLayout& dataLayout) const {
  if (!StructType::padded) computeSizeAndAlignment(dataLayout);
  return *StructType::padded;
}

// self-defined struct alignment

void StructType::computeSizeAndAlignment(const ::mlir::DataLayout& dataLayout) const {
  if (StructType::size || StructType::align || StructType::padded) return;
  // Quite same with LLVM's approach
  unsigned structSize = 0;
  llvm::Align structAlignment{1};

  [[maybe_unused]] bool isPadded = false;

  unsigned numElements = getNumElements();
  auto members = getMembers();

  // loop each struct members
  for (unsigned i = 0, e = numElements; i != e; ++i) {
    auto ty = members[i];
    const llvm::Align tyAlign = llvm::Align(getPacked() ? 1 : dataLayout.getTypeABIAlignment(ty));

    if (!llvm::isAligned(tyAlign, structSize)) {
      isPadded = true;
      structSize = llvm::alignTo(structSize, tyAlign);
    }

    structAlignment = std::max(tyAlign, structAlignment);

    structSize += dataLayout.getTypeSize(ty);
  }

  if (!llvm::isAligned(structAlignment, structSize)) {
    isPadded = true;
    structSize = llvm::alignTo(structSize, structAlignment);
  }

  StructType::size = structSize;
  StructType::align = structAlignment.value();
  StructType::padded = isPadded;
}

//===----------------------------------------------------------------------===//
// Int Type Verifier
//===----------------------------------------------------------------------===//

mlir::LogicalResult IntType::verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError,
                                    unsigned int width, bool isSigned) {
  if (width == 1 || width == 8 || width == 16 || width == 32 || width == 64) {
    return mlir::success();
  }
  return mlir::failure();
}

//===----------------------------------------------------------------------===//
// Char Type Verifier
//===----------------------------------------------------------------------===//

mlir::LogicalResult CharType::verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError,
                                     unsigned int width, bool isUtf) {
  if (width == 8 || (width == 16 && isUtf)) { return mlir::success(); }
  return mlir::failure();
}

//===----------------------------------------------------------------------===//
// Components of Func Types
//===----------------------------------------------------------------------===//

/// Returns the result type of the function as an ArrayRef, enabling better
/// integration with generic MLIR utilities.
ArrayRef<Type> FuncType::getReturnTypes() const {
  return static_cast<detail::FuncTypeStorage*>(getImpl())->returnType;
}

/// Returns whether the function is returns void.
bool FuncType::isVoid() const { return getReturnType().isa<VoidType>(); }

/// Returns a clone of this function type with the given argument
/// and result types.
FuncType FuncType::clone(::mlir::TypeRange inputs, ::mlir::TypeRange results) const {
  return get(llvm::to_vector(inputs), results[0], isVarArg());
}

static void printFuncTypeArgs(::mlir::AsmPrinter& p, ::mlir::ArrayRef<::mlir::Type> params,
                              bool isVarArg) {
  llvm::interleaveComma(params, p, [&p](mlir::Type type) { p.printType(type); });
  // (args, ...) the ... should at the last. And ... should not appears at first place.
  if (isVarArg) {
    if (!params.empty()) { p << ", "; }
    p << "...";
  }
  p << ')';
}

static ::mlir::ParseResult parseFuncTypeArgs(::mlir::AsmParser& p,
                                             ::llvm::SmallVector<::mlir::Type>& params,
                                             bool& isVarArg) {
  isVarArg = false;
  if (succeeded(p.parseOptionalRParen())) { return mlir::success(); }

  if (succeeded(p.parseOptionalEllipsis())) {
    isVarArg = true;
    return p.parseRParen();
  }

  mlir::Type type;
  if (p.parseType(type)) { return mlir::failure(); }
  params.push_back(type);
  while (succeeded(p.parseOptionalComma())) {
    if (succeeded(p.parseOptionalEllipsis())) {
      isVarArg = true;
      return p.parseRParen();
    }
    if (p.parseType(type)) { return mlir::failure(); }
    params.push_back(type);
  }

  return p.parseRParen();
}

//===----------------------------------------------------------------------===//
// Aten Dialect add types to all
//===----------------------------------------------------------------------===//

void AtenDialect::registerTypes() {
  addTypes<
#define GET_TYPEDEF_LIST
#include "AutoTen/IR/AutoTenOpsTypes.cpp.inc"
      >();
}