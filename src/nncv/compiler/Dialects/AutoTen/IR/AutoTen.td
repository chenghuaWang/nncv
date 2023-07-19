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
include "mlir/IR/BuiltinTypeInterfaces.td"
include "mlir/IR/FunctionInterfaces.td"
include "mlir/Interfaces/CastInterfaces.td"
include "mlir/IR/SymbolInterfaces.td"
include "mlir/Interfaces/SideEffectInterfaces.td"
include "mlir/IR/BuiltinAttributeInterfaces.td"
include "mlir/Interfaces/InferTypeOpInterface.td"

// include for Attribute
include "mlir/IR/AttrTypeBase.td"
include "mlir/IR/EnumAttr.td"

//===----------------------------------------------------------------------===//
// Aten Dialect Define
//===----------------------------------------------------------------------===//
def Aten_Dialect : Dialect {
    let name = "Aten";
    let cppNamespace = "::mlir::aten";
    let description = [{
        Aten(Auto tensor) is the dialects of Aten language. This language will translate with nncv.
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
        "tensor::TensorDialect"
    ];
}

//===----------------------------------------------------------------------===//
// Aten Attribute Define
//===----------------------------------------------------------------------===//
class AtenDialect_Attr<string name, string attrMnemonic, list<Trait> traits = []>
    : AttrDef<Aten_Dialect, name, traits> {
  let mnemonic = attrMnemonic;
}

def Aten_CmpPredicateAttr : I64EnumAttr<"CmpPredicate", "", [
    I64EnumAttrCase<"Equl", 0>,
    I64EnumAttrCase<"Nequal", 1>,
    I64EnumAttrCase<"Less", 2>,
    I64EnumAttrCase<"Lesseq", 3>,
    I64EnumAttrCase<"Greater", 4>,
    I64EnumAttrCase<"Greatereq", 5>,
]> {
  let cppNamespace = "::mlir::aten";
}

def Aten_BinaryArithPredicateAttr : I64EnumAttr<"BinaryArithPredict", "", [
    I64EnumAttrCase<"Add", 0>,
    I64EnumAttrCase<"Sub", 1>,
    I64EnumAttrCase<"Mul", 2>,
    I64EnumAttrCase<"Div", 3>,
    I64EnumAttrCase<"Mod", 4>,
]> {
    let cppNamespace = "::mlir::aten";
}

def Aten_BinaryLogicPredicateAttr : I64EnumAttr<"BinaryLogicPredict", "", [
    I64EnumAttrCase<"OrOp", 0>,
    I64EnumAttrCase<"AndOp", 1>,
    I64EnumAttrCase<"XorOp", 2>,
    I64EnumAttrCase<"ShlOp", 3>,
    I64EnumAttrCase<"ShrOp", 4>,
    I64EnumAttrCase<"AndAndOp", 5>,
    I64EnumAttrCase<"OrOrOp", 6>,
]> {
    let cppNamespace = "::mlir::aten";
}

def Aten_UnaryLogicPredicateAttr : I64EnumAttr<"UnaryLogicPredict", "", [
    I64EnumAttrCase<"MakePositive", 0>,
    I64EnumAttrCase<"MakeNegative", 1>,
    I64EnumAttrCase<"Not4Bool", 2>,
    I64EnumAttrCase<"BitwiseNot", 3>,
]> {
    let cppNamespace = "::mlir::aten";
}

//===----------------------------------------------------------------------===//
// Aten Type Define
//===----------------------------------------------------------------------===//
class Aten_SpecialType<string mnemonic, list<Trait> traits = []> : TypeDef<Aten_Dialect, mnemonic, traits>;

def Aten_StructType : Aten_SpecialType<"AtenStruct"> {
    let summary = "Aten Struct";
    
    let parameters = (ins ArrayRefParameter<"Type", "elementTypes">:$elementTypes);
    bit hasCustomAssemblyFormat = 1;

    let mnemonic = "AtenStruct";
}

def Aten_StringType : TensorOf<[I8, I16]>;

def Aten_MapType: DialectType<Aten_Dialect, CPred<"::llvm::isa<AtenMapType>($_self)">, "Aten Map type"> {
    bit hasCustomAssemblyFormat = 1;
}

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

def Aten_Array : Aten_SpecialType<"AtenArray"> {
    let summary = "Aten Array Type";
    let description = [{

    }];
}

def Aten_Offset : TypeAlias<Index>;
def Aten_Size : TypeAlias<Index>;

def Aten_Ptr : Aten_SpecialType<"AtenPointer"> {
    let summary = "Aten pointer type";

    let description = [{
        
    }];
    let parameters = (ins "Type":$pointee);
    let builders = [
        TypeBuilderWithInferredContext<(ins "Type":$pointee), [{
        return $_get(pointee.getContext(), pointee);
        }]>
    ];
    let assemblyFormat = "`<` qualified($pointee) `>`";

    let mnemonic = "AtenPointer";
}

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
    Aten_Ptr
]>;

def Aten_Type4NormalExpression : AnyTypeOf<[
    Aten_StructType,
    Aten_Bool,
    Aten_Char,
    Aten_Float,
    Aten_Integer,
    Aten_Tensor,
    Aten_Offset,
    Aten_Size,
    Aten_Ptr
]>;

//===----------------------------------------------------------------------===//
// Aten Operations
//===----------------------------------------------------------------------===//
class Aten_Op<string mnemonic, list<Trait> traits = []> : Op<Aten_Dialect, mnemonic, traits>;

//===----------------------------------------------------------------------===//
// Aten Operations: All Cast Operation.
//===----------------------------------------------------------------------===//
def Aten_CastArith : Aten_Op<"CastArith"> {
    let summary = "Aten Arith Cast operation";
    let description = [{
        The CastArith Op will finally lowering to `arith.BitCast` Op.
    }];

    let arguments = (ins Aten_Float, Aten_Integer:$input);
    let results = (outs Aten_Float, Aten_Integer:$output);

    // let assemblyFormat = "`aten.castarith` $input attr-dict `:` type($input) `to` type($output)";
}

def Aten_CastPtr : Aten_Op<"CastPtr", [
    DeclareOpInterfaceMethods<CastOpInterface>,
    Pure,
]> {
    let summary = "Aten Pointer Cast operation";
    let description = [{
        Thr CastPtr Op will lowering to memref. This Op is mainly responsible for such
        things:

        ```cpp
        foo u_struct* := (u_struct*)std.malloc(...);
        ```
    }];

    let arguments = (ins AnyMemRef:$input);
    let results = (outs AnyMemRef:$output);

    // let assemblyFormat = "`aten.castptr` $input attr-dict `:` type($input) `to` type($output)";
}

//===----------------------------------------------------------------------===//
// Aten Operations: Binary Op.
// 
// Ops: AddOp, SubOp, MulOp, DivOp
// Ops: CmpOp(!=, ==, >, >=, <, <=) using attribute to figure out which pattern we need.
// Ops: AndOp, OrOp, XorOp
//===----------------------------------------------------------------------===//
def Aten_BinaryArithOp : Aten_Op<"BinaryArith", [
    DeclareOpInterfaceMethods<InferTypeOpInterface>
]> {
    let summary = "Aten Generic Binary Op";
    let description = [{

    }];

    let arguments = (ins Aten_BinaryArithPredicateAttr:$predicate, Aten_Type4NormalExpression:$lhs, Aten_Type4NormalExpression:$rhs);
    let results = (outs Aten_Type4NormalExpression:$result);

    // let assemblyFormat = "`aten.binaryarith` $predicate `,` $lhs `,` $rhs attr-dict `:` type($lhs) `,` type($rhs) `->`  type($result)";
}

def Aten_BinaryLogicOp : Aten_Op<"BinaryLogic", [
    DeclareOpInterfaceMethods<InferTypeOpInterface>
]> {
    let summary = "Aten Generic Binary logic";
    let description = [{

    }];

    let arguments = (ins Aten_BinaryLogicPredicateAttr:$predicate, Aten_Type4NormalExpression:$lhs, Aten_Type4NormalExpression:$rhs);
    let results = (outs Aten_Type4NormalExpression:$result);

    // let assemblyFormat = "`aten.binarylogic` $predicate `,` $lhs `,` $rhs attr-dict `:` type($lhs) `,` type($rhs) `->` type($result)";
}

def Aten_CmpOp : Aten_Op<"Cmp", [
    DeclareOpInterfaceMethods<InferTypeOpInterface>
]> {
    let arguments = (ins Aten_CmpPredicateAttr:$predicate, Aten_Type4NormalExpression:$lhs, Aten_Type4NormalExpression:$rhs);
    let results = (outs Aten_Bool:$result);

    // let assemblyFormat = "`aten.cmp` $predicate `,` $lhs `,` $rhs attr-dict `:` type($lhs) `,` type($rhs)";
}

def Aten_UnaryLogicOp : Aten_Op<"UnaryLogic", [
    DeclareOpInterfaceMethods<InferTypeOpInterface>
]> {
    let arguments = (ins Aten_BinaryLogicPredicateAttr:$predicate, Aten_Type4NormalExpression:$inputs);
    let results = (outs Aten_Type4NormalExpression:$result);
}

//===----------------------------------------------------------------------===//
// Aten Operations: Unary Op.
// 
// Ops: ++, --
// Ops: !, ~
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Aten Operations: Helper Op for manipulate Struct Type.
//===----------------------------------------------------------------------===//
def Aten_AccessStruct : Aten_Op<"AccessStruct">{

}

//===----------------------------------------------------------------------===//
// Aten Operations: Helper Op for manipulate Array Type.
//===----------------------------------------------------------------------===//
def Aten_AccessArray : Aten_Op<"AccessArray">{

}

//===----------------------------------------------------------------------===//
// Aten Operations: Helper Op on typed pointer.
//
// Dereference: value = *ptr
// Apply: ptr = &value
//===----------------------------------------------------------------------===//
def Aten_Dereference : Aten_Op<"Dereference"> {
    let arguments = (ins Aten_Ptr:$inputs);
    let results = (outs Aten_Type4NormalExpression:$outputs);
}

def Aten_Apply : Aten_Op<"Apply"> {
    let arguments = (ins Aten_Type4NormalExpression:$inputs);
    let results = (outs Aten_Ptr:$outputs);
}

//===----------------------------------------------------------------------===//
// Aten Operations: Contorl Flow.
//
// For / While / do-While / if 
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Aten Operations: Other build in method.
//===----------------------------------------------------------------------===//

#endif //! AUTOTEN_OPS_TD