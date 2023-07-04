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
include "mlir/Interfaces/CastInterfaces.td"
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
def Aten_StructType : DialectType<Aten_Dialect, CPred<"::llvm::isa<AtenStructType>($_self)">, "Aten struct type">;

def Aten_MapType: DialectType<Aten_Dialect, CPred<"::llvm::isa<AtenMapType>($_self)">, "Aten Map type">;

def Aten_Bool : AnyTypeOf<[I1, I8], "boolean-storing type (1 or 8 -bit integer)">;
def Aten_Char : AnyTypeOf<[I8], "charater-storing type(8 bit integer)">;
def Aten_Float : AnyTypeOf<[F32, F64]>;
def Aten_Integer : AnyTypeOf<[I8, I16, I32, I64]>;

def Aten_Element : AnyTypeOf<[Aten_Integer, Aten_Float]>{
    let summary = "Aten ElementType";
    let description = [{
        The ElementType means the Type `Aten_Tensor` can handle.
    }];
}

def Aten_Tensor : TensorOf<[Aten_Element]>;

def Aten_Array : DialectType<Aten_Dialect, CPred<"::llvm::isa<AtenArrayType>(&_self)">> {
    let summary = "Aten ArrayType";
    let description = [{
        The Array in aten is working both static and dynamic. The AtenArray will be lowered to memref type.
        And memref.alloc, memref alloca will handle the static and dynamic.

        Notes: The dynamic array can only be called using `new` keyword which is not implemented yet.
    }];
}

def Aten_Offset : TypeAlias<Index>;
def Aten_Size : TypeAlias<Index>;
def Aten_Range : AnyTypeOf<[Index, AnyInteger]>;

def Aten_Ptr : TypeAlias<AnyMemRef>;

def Aten_Type : AnyTypeOf<[
    Aten_StructType,
    Aten_MapType,
    Aten_Bool,
    Aten_Char,
    Aten_Float,
    Aten_Integer,
    Aten_Element,
    Aten_Tensor,
    Aten_Array,
    Aten_Offset,
    Aten_Size,
    Aten_Range,
    Aten_Ptr
]>;

//===----------------------------------------------------------------------===//
// Aten Operations
//===----------------------------------------------------------------------===//
class Aten_Op<string mnemonic, list<Trait> traits = []> : Op<Aten_Dialect, mnemonic, traits>;

//===----------------------------------------------------------------------===//
// Aten Operations: All Cast Operation.
//===----------------------------------------------------------------------===//
class Aten_CastArith : Aten_Op<"cast", [
     DeclareOpInterfaceMethods<CastOpInterface>,
     Pure,
]> {
    let summary = "Aten Arith Cast operation";
    let description = [{
        The CastArith Op will finally lowering to `arith.BitCast` Op.
    }];

    let arguments = (ins Aten_Float, Aten_Integer:$input);
    let results = (outs Aten_Float, Aten_Integer:$output);

    let assemblyFormat = "$input attr-dict `:` type($input) `to` type($output)";
}

class Aten_CastPtr : Aten_Op<"cast", [
    DeclareOpInterfaceMethods<CastOpInterface>,
    Pure,
]> {
    let summary = "Aten Pointer Cast operation";
    let description = [{
        Thr CastPtr Op will lowering to memref. This Op is mainly responsible for such
        things:

        ```
        foo u_struct* := (u_struct*)std.malloc(...);
        ```
    }];

    let arguments = (ins AnyMemRef:$input);
    let results = (outs AnyMemRef:$output);

    let assemblyFormat = "$input attr-dict `:` type($input) `to` type($output)";
}

//===----------------------------------------------------------------------===//
// Aten Operations: Arith Operation.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Aten Operations: Helper Op for manipulate Struct Type.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Aten Operations: Helper Op for manipulate Array Type.
//===----------------------------------------------------------------------===//

#endif //! AUTOTEN_OPS_TD