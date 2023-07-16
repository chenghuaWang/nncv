#include "nncv/compiler/Dialects/AutoTen/IR/Dialect.hpp"

#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/FunctionImplementation.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/Transforms/InliningUtils.h"

#include "llvm/ADT/TypeSwitch.h"

using namespace mlir;
using namespace mlir::aten;

#include "AutoTen/IR/Dialect.cpp.inc"

#define GET_TYPEDEF_CLASSES
#include "AutoTen/IR/AutoTenTypes.cpp.inc"

#define GET_OP_CLASSES
#include "AutoTen/IR/AutoTen.cpp.inc"

#define GET_ATTRDEF_CLASSES
#include "AutoTen/IR/AutoTenOpsAttributes.cpp.inc"

#include "AutoTen/IR/AutoTenOpsEnums.cpp.inc"

void AtenDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "AutoTen/IR/AutoTen.cpp.inc"
      >();
  addTypes<
#define GET_TYPEDEF_LIST
#include "AutoTen/IR/AutoTenTypes.cpp.inc"
      >();
  addAttributes<
#define GET_ATTRDEF_LIST
#include "AutoTen/IR/AutoTenOpsAttributes.cpp.inc"
      >();
}

mlir::Operation* AtenDialect::materializeConstant(mlir::OpBuilder& builder, mlir::Attribute value,
                                                  mlir::Type type, mlir::Location loc) {
  return nullptr;
}

namespace mlir {
namespace aten {
//===----------------------------------------------------------------------===//
// Aten Struct Type: with self defined asm format.
//===----------------------------------------------------------------------===//
void AtenStructType::print(mlir::AsmPrinter& p) const {
  p << "<";
  llvm::interleaveComma(getElementTypes(), p);
  p << '>';
}

Type AtenStructType::parse(AsmParser& parser) {
  if (parser.parseLess()) return Type();
  SmallVector<mlir::Type, 1> elementTypes;
  do {
    mlir::Type elementType;
    if (parser.parseType(elementType)) return nullptr;

    elementTypes.push_back(elementType);
  } while (succeeded(parser.parseOptionalComma()));
  if (parser.parseGreater()) return Type();
  return get(parser.getContext(), elementTypes);
}

//===----------------------------------------------------------------------===//
// Aten Cast Ptr Op method
//
// different typed ptr can be cast. But not recommend. Such as
// `!aten.ptr<int>` to `!aten.ptr<float>`
//===----------------------------------------------------------------------===//
bool CastPtr::areCastCompatible(TypeRange inputs, TypeRange outputs) {
  // only support one
  if (inputs.size() != 1 || outputs.size() != 1) return false;

  AtenStructType input = inputs.front().dyn_cast<AtenStructType>();
  AtenStructType output = outputs.front().dyn_cast<AtenStructType>();

  if (!input || !output) return false;
  return true;
}

}  // namespace aten
}  // namespace mlir