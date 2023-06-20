#include "nncv/compiler/Dialects/AutoTen/Dialect.hpp"

#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/FunctionImplementation.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/Transforms/InliningUtils.h"

using namespace mlir;
using namespace mlir::aten;

#include "AutoTen/Dialect.cpp.inc"

mlir::Type AtenDialect::parseType(mlir::DialectAsmParser& parser) const {}

void AtenDialect::printType(mlir::Type type, mlir::DialectAsmPrinter& printer) const {}

#define GET_OP_CLASSES
#include "AutoTen/AutoTen.cpp.inc"

void AtenDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "AutoTen/AutoTen.cpp.inc"
      >();
}

mlir::Operation* AtenDialect::materializeConstant(mlir::OpBuilder& builder, mlir::Attribute value,
                                                  mlir::Type type, mlir::Location loc) {
  return nullptr;
}

namespace mlir {
namespace aten {}
}  // namespace mlir