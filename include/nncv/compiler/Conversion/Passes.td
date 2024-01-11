#ifndef ATEN_CONVERSION_PASSES
#define ATEN_CONVERSION_PASSES

include "mlir/Pass/PassBase.td"

//===----------------------------------------------------------------------===//
// AtenToArith
//===----------------------------------------------------------------------===//
def ConvertAtenToMlir : Pass<"convert-aten-to-mlir"> {
    let summary = "Convert Aten dialect to MLIR owned dialect";
    let description = [{
        Convert all ops to arith, scf, memref and linalg.
    }];
    let constructor = "mlir::nncv::createConvertAtenToMlirPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "aten::AtenDialect",
    ];
}

#endif //! ATEN_CONVERSION_PASSES