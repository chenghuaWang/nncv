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

// Eliminate Redundant Cmp for scf.condiontional
def EliminateRedundantLoadStoreForScfConditional: Pass<"nncv-aten-eliminate-redundant-load-store-for-scf-conditional", ""> {
    let summary = "Eliminate redunant store and load after the perform of aten to mlir lowering.";
    let constructor = "mlir::nncv::aten::createEliminateRedundantLoadStoreForScfConditionalPass();";
    let description = [{
        After lowering `aten.if` and `aten.loop` to mlir's `scf.if` and `scf.while`. For lowering convinence, I involved
        some ops. Such as:
        aten lang:
        ```mlir
        for (i := 0; i < 128; i++) {
            var c float32;
            c = dst[i];
        };
        ```
        lowering to aten ir
        ```mlir
        Aten.loop for(cond : {
            %3 = Aten.load %2 : aten.ptr <!Aten.int<s, 32>>, !Aten.int<s, 32>
            %4 = Aten.cmp(lt, %3, %0) : !Aten.int<s, 32>, !Aten.bool
            %5 = Aten.alloca !Aten.bool, aten.ptr <!Aten.bool>, ["__tmp_condition@0"] {alignment = 1 : i64}
            Aten.store %4, %5 : !Aten.bool, aten.ptr <!Aten.bool>
            Aten.yield
        }, step : {
            %3 = Aten.load %2 : aten.ptr <!Aten.int<s, 32>>, !Aten.int<s, 32>
            %4 = Aten.unary(inc, %3) : !Aten.int<s, 32>, !Aten.int<s, 32>
            Aten.store %4, %2 : !Aten.int<s, 32>, aten.ptr <!Aten.int<s, 32>>
            Aten.yield
        }) {
            %3 = Aten.alloca f32, aten.ptr <f32>, ["c"] {alignment = 4 : i64}
            %4 = Aten.load %2 : aten.ptr <!Aten.int<s, 32>>, !Aten.int<s, 32>
            %5 = Aten.cast(int_to_mlir_index, %4 : !Aten.int<s, 32>), index
            %6 = memref.load %alloc[%5] : memref<128xf32>
            Aten.store %6, %3 : f32, aten.ptr <f32>
            Aten.yield
        }
        ```
        lowering to MLIR:
        ```mlir
        scf.while : () -> () {
            %0 = memref.load %alloca[] : memref<i32>
            %1 = arith.cmpi ult, %0, %c128_i32 : i32
            %2 = arith.extui %1 : i1 to i8
            %alloca_0 = memref.alloca() {alignment = 1 : i64} : memref<i8>
            memref.store %2, %alloca_0[] : memref<i8>
            scf.condition(%1)
        } do {
            %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<f32>
            %0 = memref.load %alloca[] : memref<i32>
            %1 = arith.index_cast %0 : i32 to index
            %2 = memref.load %alloc[%1] : memref<128xf32>
            memref.store %2, %alloca_0[] : memref<f32>
            %3 = memref.load %alloca[] : memref<i32>
            %c1_i32 = arith.constant 1 : i32
            %4 = arith.addi %3, %c1_i32 : i32
            memref.store %4, %alloca[] : memref<i32>
            scf.yield
        }
        ```

        We can noticed that:

        ```mlir
        %2 = arith.extui %1 : i1 to i8
        %alloca_0 = memref.alloca() {alignment = 1 : i64} : memref<i8>
        memref.store %2, %alloca_0[] : memref<i8>
        ```
        can be eliminated.
    }];
}

def RaiseMemerefLSInAffineToAffineLS : Pass<"nncv-aten-raise-memref-ls-to-affine-ls-if-in-affine", "func::FuncOp"> {
    let summary = "Raise Memref Load/Store to Affine Load/Store if Memref in Affine scope.";
    let constructor = "mlir::nncv::aten::createRaiseMemerefLSInAffineToAffineLSPass();";
}

#endif //! NNCV_NNCV_ATEN_TRANSFORMS_PASSES