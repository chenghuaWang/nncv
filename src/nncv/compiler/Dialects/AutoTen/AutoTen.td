#ifndef AUTOTEN_OPS_TD
#define AUTOTEN_OPS_TD

include "mlir/IR/OpBase.td"
include "mlir/IR/FunctionInterfaces.td"
include "mlir/IR/SymbolInterfaces.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

def Aten_Dialect : Dialect {
    let name = "Aten";
    let cppNamespace = "::mlir::aten";
    let description = [{
        Aten(Auto tensor) is the dialects of Aten language. This language will translate to nncv.
    }];
    let hasConstantMaterializer = 1;
    let useDefaultTypePrinterParser = 1;
}

class Aten_Op<string mnemonic, list<Trait> traits = []> : Op<Aten_Dialect, mnemonic, traits>;

def Aten_StructType : DialectType<Aten_Dialect, CPred<"::llvm::isa<StructType>($_self)">, "Aten struct type">;
def Aten_Bool : AnyTypeOf<[I1, I8], "boolean-storing type (1 or 8 -bit integer)">;
def Aten_Char : AnyTypeOf<[I8], "charater-storing type(8 bit integer)">;
def Aten_Element : AnyTypeOf<[AnyInteger, AnyFloat]>;
def Aten_Tensor : TensorOf<[Aten_Element]>;
def Aten_Primitive : AnyTypeOf<[Index, AnyInteger, AnyFloat]>;
def Aten_FillPattern : AnyTypeOf<[AnyInteger, AnyFloat, Index]>;
def Aten_Offset : TypeAlias<Index>;
def Aten_Size : TypeAlias<Index>;
def Aten_Range : AnyTypeOf<[Index, AnyInteger]>;

def Aten_Type : AnyTypeOf<[Aten_Bool, Aten_Char, Aten_Element, Aten_Tensor, Aten_Primitive, 
                          Aten_Offset, Aten_Size, Aten_Range, Aten_StructType]>;

//===----------------------------------------------------------------------===//
// Aten Operations
//===----------------------------------------------------------------------===//


#endif //! AUTOTEN_OPS_TD