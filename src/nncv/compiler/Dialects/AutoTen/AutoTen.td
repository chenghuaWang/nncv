/**
* @autor chenghua.wang
* @mail chenghua.wang.edu@gmail.com
* 
* This file defined the Aten-lang's dialect based on mlir. Before start to implement.
* The Toy-lang tutorial provided by LLVM official is which I should go through first.
* Also, the LLVM's TableGen document is highly recommend to read.
*
* Some ref:
* 1. https://harmonyhu.com/2021/08/17/mlir/
*/
#ifndef AUTOTEN_OPS_TD
#define AUTOTEN_OPS_TD

// include for basic component.
include "mlir/IR/OpBase.td"
include "mlir/IR/FunctionInterfaces.td"
include "mlir/IR/SymbolInterfaces.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

// include for Attribute
include "mlir/IR/AttrTypeBase.td"

//===----------------------------------------------------------------------===//
// Aten Dialect Define
//===----------------------------------------------------------------------===//
def Aten_Dialect : Dialect {
    let name = "Aten";
    let cppNamespace = "::mlir::aten";
    let description = [{
        Aten(Auto tensor) is the dialects of Aten language. This language will translate to nncv.
    }];
    let hasConstantMaterializer = 1;
    let useDefaultTypePrinterParser = 1;

    let dependentDialects = [
        "affine::AffineDialect",
        "arith::ArithDialect",
        "func::FuncDialect",
        "linalg::LinalgDialect",
        "math::MathDialect",
        "memref::MemRefDialect",
        "scf::SCFDialect",
        "shape::ShapeDialect",
        "tensor::TensorDialect",
    ];
}

//===----------------------------------------------------------------------===//
// Aten Attribute Define
//===----------------------------------------------------------------------===//
class AtenDialect_Attr<string name, string attrMnemonic, list<Trait> traits = []>
    : AttrDef<Aten_Dialect, name, traits> {
  let mnemonic = attrMnemonic;
}

//===----------------------------------------------------------------------===//
// Aten Type Define
//===----------------------------------------------------------------------===//
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
class Aten_Op<string mnemonic, list<Trait> traits = []> : Op<Aten_Dialect, mnemonic, traits>;

#endif //! AUTOTEN_OPS_TD