#ifndef NNCV_NNCV_ATEN_TRANSFORMS_PASSES
#define NNCV_NNCV_ATEN_TRANSFORMS_PASSES

include "mlir/Pass/PassBase.td"

// EliminateTailReturnLoad.
def EliminateTailReturnLoad : Pass<"nncv-aten-eliminate-tail-ret-load", ""> {
    let summary = "Eliminate the ret load in function tail.";
    let constructor = "mlir::nncv::aten::createEliminateTailReturnLoadPass();";
    let description = [{
        When lowering an aten-lang script to mlir code.
        ```aten
        func testArithInt64Expr(a int64, b int64) -> int64 {
            var c int64;
            c =  a + b;
            return c;
        };
        ```
        will be translated to
        ```mlir
        Aten.func private @testArithInt64Expr(%arg0: !Aten.int<s, 64>, %arg1: !Aten.int<s, 64>) -> !Aten.int<s, 64> {
            %0 = Aten.alloca !Aten.int<s, 64>, aten.ptr <!Aten.int<s, 64>>, ["c"] {alignment = 8 : i64}
            %1 = Aten.binop(add, %arg0, %arg1) : !Aten.int<s, 64>
            Aten.store %1, %0 : !Aten.int<s, 64>, aten.ptr <!Aten.int<s, 64>>
            %2 = Aten.load %0 : aten.ptr <!Aten.int<s, 64>>, !Aten.int<s, 64>
            Aten.return %2 : !Aten.int<s, 64>
        }
        ```
        We can easily noticed that `Aten.store` and `Aten.load` operation is not necessary. We can eliminate it.

        In this Pass. Algorithm will first check the Aten.return op and check the op->prevOp()->prevOp();
    }];
}

#endif //! NNCV_NNCV_ATEN_TRANSFORMS_PASSES