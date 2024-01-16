#include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtDialect.hpp"
#include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtOps.hpp"

#include "mlir/IR/Attributes.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/Transforms/InliningUtils.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/TypeSwitch.h"
#include "llvm/Support/SourceMgr.h"

using namespace mlir;
using namespace mlir::nncv::linalg_ext;

#include "LinalgExt/IR/LinalgExtEnums.cpp.inc"  // IWYU pragma: keep

#define GET_ATTRDEF_CLASSES
#include "LinalgExt/IR/LinalgExtAttrs.cpp.inc"  // IWYU pragma: keep

struct IREELinalgExtInlinerInterface : public DialectInlinerInterface {
  using DialectInlinerInterface::DialectInlinerInterface;

  bool isLegalToInline(Operation* call, Operation* callable, bool wouldBeCloned) const final {
    return true;
  }
  bool isLegalToInline(Region* dest, Region* src, bool wouldBeCloned,
                       IRMapping& valueMapping) const final {
    return true;
  }

  bool isLegalToInline(Operation* op, Region* dest, bool wouldBeCloned,
                       IRMapping& valueMapping) const final {
    return true;
  }
};

void NNCVLinalgExtDialect::initialize() {
  addInterfaces<IREELinalgExtInlinerInterface>();
  addAttributes<
#define GET_ATTRDEF_LIST
#include "LinalgExt/IR/LinalgExtAttrs.cpp.inc"
      >();
#define GET_OP_LIST
  addOperations<
#include "LinalgExt/IR/LinalgExtOps.cpp.inc"
      >();
}
#include "LinalgExt/IR/LinalgExtDialect.cpp.inc"
