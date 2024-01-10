#ifndef ATEN_CONVERSION_PASSES
#define ATEN_CONVERSION_PASSES

include "mlir/Pass/PassBase.td"

//===----------------------------------------------------------------------===//
// AtenToArith
//===----------------------------------------------------------------------===//
def ConvertAtenToArith : Pass<"convert-aten-to-arith"> {
    let summary = "Convert Aten dialect to Arith dialect";
    let description = [{
        This pass converts supported Aten ops to Arith dialect. The Ops supported is
        only `aten.castarith` Op. The Aten cast arith Op allow all types in aten as
        inputs. But it only allowed arith to arith and tensor to tensor cast. Ptr cast
        is supported by `aten.castptr`.

        **Note:** The struct cast and array cast can only use `aten.castptr` method.
    }];
    let constructor = "mlir::nncv::createConvertAtenToArithPass()";
    let dependentDialects = [
        "arith::ArithDialect",
        "aten::AtenDialect",
    ];
}

#endif //! ATEN_CONVERSION_PASSES