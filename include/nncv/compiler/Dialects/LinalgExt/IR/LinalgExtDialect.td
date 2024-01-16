#ifndef NNCV_LINALGEXT_DIALECT
#define NNCV_LINALGEXT_DIALECT

include "mlir/IR/OpBase.td"
include "mlir/IR/AttrTypeBase.td"
include "mlir/IR/EnumAttr.td"

def NNCV_LinalgExt_Dialect : Dialect {
  let name = "nncv_linalg_ext";
  let cppNamespace = "::mlir::nncv::linalg_ext";
  let summary = [{
    NNCV Linalg Extensions.
  }];
  let description = [{
    Extension:
    winogradOp,
  }];
  let useDefaultAttributePrinterParser = 1;
}

#endif //! NNCV_LINALGEXT_DIALECT