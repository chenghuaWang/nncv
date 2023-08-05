/**
* @autor chenghua.wang
* @mail chenghua.wang.edu@gmail.com
*/
#ifndef AUTOTEN_IR_OPS_TD
#define AUTOTEN_IR_OPS_TD

include "nncv/compiler/Dialects/AutoTen/IR/AutoTenDialect.td"
include "nncv/compiler/Dialects/AutoTen/IR/AutoTenTypes.td"
include "nncv/compiler/Dialects/AutoTen/IR/AutoTenAttrs.td"

include "mlir/Interfaces/CallInterfaces.td"
include "mlir/Interfaces/ControlFlowInterfaces.td"
include "mlir/Interfaces/LoopLikeInterface.td"
include "mlir/Interfaces/InferTypeOpInterface.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

include "mlir/IR/BuiltinAttributeInterfaces.td"
include "mlir/IR/EnumAttr.td"
include "mlir/IR/FunctionInterfaces.td"
include "mlir/IR/SymbolInterfaces.td"
include "mlir/Interfaces/DataLayoutInterfaces.td"

//===----------------------------------------------------------------------===//
// Aten Ops
//===----------------------------------------------------------------------===//

class Aten_Op<string mnemonic, list<Trait> traits = []> :
    Op<Aten_Dialect, mnemonic, traits>;

//===----------------------------------------------------------------------===//
// Aten Package and Impl region classification.
//
// All Package and Impl region will use buildin module Op
// The Package of module is: 
// ```
// module @pk_nn {
//      module @pk_cv {
//          module @impl_foo {
//
//          }
//      }
// }
// ```
// which indicated a main package `nn` has sub package `cv` and `cv` has a interface
// that works on `foo` struct.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Aten Cast Op
//===----------------------------------------------------------------------===//

def Aten_IntegralToBoolean : I32EnumAttrCase<"int_to_bool", 1>;
def Aten_ArrayToPointerDecay : I32EnumAttrCase<"array_to_ptrdecay", 2>;
def Aten_IntegralCast : I32EnumAttrCase<"integral", 3>;
def Aten_BitCast : I32EnumAttrCase<"bitcast", 4>;
def Aten_FloatingCast : I32EnumAttrCase<"floating", 5>;
def Aten_FloatToIntegral : I32EnumAttrCase<"float_to_int", 6>;
def Aten_FloatToBoolean : I32EnumAttrCase<"float_to_bool", 7>;
def Aten_BooleanToIntegral : I32EnumAttrCase<"bool_to_int", 8>;
def Aten_IntegralToFloat : I32EnumAttrCase<"int_to_float", 9>;

def CastPrdicate : I32EnumAttr<
    "CastPredicate",
    "cast predicate", [
    Aten_IntegralToBoolean, 
    Aten_ArrayToPointerDecay, 
    Aten_IntegralCast,
    Aten_BitCast,
    Aten_FloatingCast,
    Aten_FloatToIntegral,
    Aten_FloatToBoolean,
    Aten_BooleanToIntegral,
    Aten_IntegralToFloat
]> {
  let cppNamespace = "::mlir::aten";
}

def Aten_CastOp : Aten_Op<"cast", [
    Pure
]> {
    let summary = "Conversion between values";
    let description = [{
        // TODO
    }];

    let arguments = (ins CastPrdicate:$predicate, AnyType:$input);
    let results = (outs AnyType:$result);

    let assemblyFormat = [{
        `(` $predicate `,` $input `:` type($input) `)`
        `,` type($result) attr-dict
    }];

    // The input and output types should match the cast prediacte.
    let hasVerifier = 1;
}

//===----------------------------------------------------------------------===//
// Aten Ptr sub op
//===----------------------------------------------------------------------===//

def Aten_PtrDiffOp : Aten_Op<"ptr_diff", [
    Pure, 
    SameTypeOperands
]> {
    let summary = "Pointer subtraction arithmetic";
    let description = [{
    }];

    let arguments = (ins AnyType:$lhs, AnyType:$rhs);
    let results = (outs Aten_IntegerType:$result);

    let assemblyFormat = [{
        `(` $lhs `,` $rhs  `)` `:` type($lhs) `->` type($result) attr-dict
    }];

    // Already covered by the traits
    let hasVerifier = 0;
}

//===----------------------------------------------------------------------===//
// Aten Ptr Stride Op
//===----------------------------------------------------------------------===//

def SameFirstOperandAndResultType : NativeOpTrait<"SameFirstOperandAndResultType">;

def PtrStrideOp : Aten_Op<"ptr_stride", [
    Pure, 
    SameFirstOperandAndResultType
]> {
    let summary = "Pointer access with stride";
    let description = [{
    }];

    let arguments = (ins AnyType:$base, Aten_IntegerType:$stride);
    let results = (outs AnyType:$result);

    let assemblyFormat = [{
        `(` $base `:` type($base) `,` $stride `:` qualified(type($stride)) `)`
        `,` type($result) attr-dict
    }];

    // SameFirstOperandAndResultType already checks all we need.
    let hasVerifier = 0;
}

//===----------------------------------------------------------------------===//
// Aten Constant Op
//===----------------------------------------------------------------------===//

def ConstantOp : Aten_Op<"const", [
    ConstantLike, 
    Pure
]> {
    let summary = "Defines a Aten constant";
    let description = [{
    }];

    // The constant operation takes an attribute as the only input.
    let arguments = (ins TypedAttrInterface:$value);

    // The constant operation returns a single value of AnyType.
    let results = (outs AnyType:$res);

    let assemblyFormat = [{
        `(` custom<ConstantValue>($value) `)` attr-dict `:` type($res)
    }];

    let hasVerifier = 1;

    let extraClassDeclaration = [{
        bool isNilPtr() {
        return getValue().isa<mlir::aten::NilAttr>();
        }
    }];

    let hasFolder = 1;
}

//===----------------------------------------------------------------------===//
// Aten Alloca Op
//===----------------------------------------------------------------------===//

// TODO

//===----------------------------------------------------------------------===//
// Aten Delete Op
//===----------------------------------------------------------------------===//

// TODO

//===----------------------------------------------------------------------===//
// LoadOp
//===----------------------------------------------------------------------===//

def LoadOp : Aten_Op<"load", [
    TypesMatchWith<"type of 'result' matches pointee type of 'addr'",
                    "addr", "result",
                    "$_self.cast<PointerType>().getPointee()">
]> {
    let summary = "Load value from memory adddress";
    let description = [{
    }];

    let arguments = (ins Arg<Aten_PointerType, "the address to load from",
                            [MemRead]>:$addr, UnitAttr:$isDeref);
    let results = (outs AnyType:$result);

    let assemblyFormat = [{
        (`deref` $isDeref^)? $addr `:` `aten.ptr` type($addr) `,`
                                    type($result) attr-dict
    }];

    // To check if hil or not.
    let hasVerifier = 1;
}

//===----------------------------------------------------------------------===//
// StoreOp
//===----------------------------------------------------------------------===//

def StoreOp : Aten_Op<"store", [
    TypesMatchWith<"type of 'value' matches pointee type of 'addr'",
                    "addr", "value",
                    "$_self.cast<PointerType>().getPointee()">
]> {
    let summary = "Store value to memory address";
    let description = [{
        `cir.store` stores a value (first operand) to the memory address specified
        in the second operand.

        Example:

        ```mlir
        // Store a function argument to local storage, address in %0.
        cir.store %arg0, %0 : i32, !cir.ptr<i32>
        ```
    }];

    let arguments = (ins AnyType:$value,
                        Arg<Aten_PointerType, "the address to store the value",
                            [MemWrite]>:$addr);

    let assemblyFormat =
        "$value `,` $addr attr-dict `:` type($value) `,` `aten.ptr` type($addr)";

    // To check if hil or not.
    let hasVerifier = 1;
}

//===----------------------------------------------------------------------===//
// Aten Unary Op
//===----------------------------------------------------------------------===//

def Aten_UnaryOp_Inc   : I32EnumAttrCase<"Inc",   1, "inc">; // such as i++;
def Aten_UnaryOp_Dec   : I32EnumAttrCase<"Dec",   2, "dec">; // i--;
def Aten_UnaryOp_Plus  : I32EnumAttrCase<"Plus",  3, "plus">; // -i(signed)
def Aten_UnaryOp_Minus : I32EnumAttrCase<"Minus", 4, "minus">; // +i(signed)
def Aten_UnaryOp_Not   : I32EnumAttrCase<"Not",   5, "not">; // !i

def UnaryOpPredicate : I32EnumAttr<
    "UnaryOpPredicate",
    "unary operation predicate", [
]> {
    let cppNamespace = "::mlir::aten";
}

def Aten_UnaryOp : Aten_Op<"unary", [
    Pure, 
    SameOperandsAndResultType
]> {
    let summary = "Unary operations";
    let description = [{
    }];

    let results = (outs AnyType:$result);
    let arguments = (ins Arg<UnaryOpPredicate, "unary op predicate">:$predicate, Arg<AnyType>:$input);

    let assemblyFormat = [{
        `(` $predicate `,` $input `)` `:` type($input) `,` type($result) attr-dict
    }];

    let hasVerifier = 1;
}

//===----------------------------------------------------------------------===//
// Aten Bin Op
//===----------------------------------------------------------------------===//

def Aten_BinOp_Mul : I32EnumAttrCase<"Mul", 1, "mul">;
def Aten_BinOp_Div : I32EnumAttrCase<"Div", 2, "div">;
def Aten_BinOp_Mod : I32EnumAttrCase<"Mod", 3, "Mod">;
def Aten_BinOp_Add : I32EnumAttrCase<"Add", 4, "add">;
def Aten_BinOp_Sub : I32EnumAttrCase<"Sub", 5, "sub">;
def Aten_BinOp_And : I32EnumAttrCase<"And", 8, "and">;
def Aten_BinOp_Xor : I32EnumAttrCase<"Xor", 9, "xor">;
def Aten_BinOp_Or  : I32EnumAttrCase<"Or", 10, "or">;
def Aten_BinOp_LogicAnd : I32EnumAttrCase<"LogicAnd", 11, "logic_and">;
def Aten_BinOp_LogicOr : I32EnumAttrCase<"LogicOr", 12, "logic_or">;

def BinOpPredicate : I32EnumAttr<
    "BinOpPredicate",
    "binary operation (arith and logic) kind", [
    Aten_BinOp_Mul, 
    Aten_BinOp_Div, 
    Aten_BinOp_Mod,
    Aten_BinOp_Add, 
    Aten_BinOp_Sub,
    Aten_BinOp_And, 
    Aten_BinOp_Xor,
    Aten_BinOp_Or,
    Aten_BinOp_LogicAnd,
    Aten_BinOp_LogicOr
]> {
  let cppNamespace = "::mlir::aten";
}

def Aten_BinOp : Aten_Op<"binop", [
    Pure,
    SameTypeOperands, 
    SameOperandsAndResultType
]> {
    let summary = "Binary operations (arith and logic)";
    let description = [{
    }];

    let arguments = (ins Arg<BinOpPredicate, "binop kind">:$predicate, AnyType:$lhs, AnyType:$rhs);

    let results = (outs AnyType:$result);
    
    let assemblyFormat = [{
        `(` $predicate `,` $lhs `,` $rhs  `)` `:` type($lhs) attr-dict
    }];

    // Already covered by the traits
    let hasVerifier = 0;
}

//===----------------------------------------------------------------------===//
// Aten Shift Op
//===----------------------------------------------------------------------===//

def Aten_ShiftOp : Aten_Op<"shift", [
    Pure
]> {
    let summary = "Shift";
    let description = [{
    }];

    let arguments = (ins Aten_IntegerType:$value, Aten_IntegerType:$amount, UnitAttr:$isShiftleft);

    let results = (outs Aten_IntegerType:$result);

    let assemblyFormat = [{
        `(`
        (`left` $isShiftleft^) : (`right`)?
        `,` $value `:` type($value)
        `,` $amount `:` type($amount)
        `)` `->` type($result) attr-dict
    }];

    // Already covered by the traits
    let hasVerifier = 0;
}

//===----------------------------------------------------------------------===//
// Aten Cmp Op
//===----------------------------------------------------------------------===//

def Aten_CmpOp_LT : I32EnumAttrCase<"lt", 1>;
def Aten_CmpOp_LE : I32EnumAttrCase<"le", 2>;
def Aten_CmpOp_GT : I32EnumAttrCase<"gt", 3>;
def Aten_CmpOp_GE : I32EnumAttrCase<"ge", 4>;
def Aten_CmpOp_EQ : I32EnumAttrCase<"eq", 5>;
def Aten_CmpOp_NE : I32EnumAttrCase<"ne", 6>;

def CmpOpPredicate : I32EnumAttr<
    "CmpOpPredicate",
    "compare operation predicate", [
    Aten_CmpOp_LT, 
    Aten_CmpOp_LE, 
    Aten_CmpOp_GT,
    Aten_CmpOp_GE, 
    Aten_CmpOp_EQ, 
    Aten_CmpOp_NE
]> {
  let cppNamespace = "::mlir::aten";
}

def Aten_CmpOp : Aten_Op<"cmp", [
    Pure, 
    SameTypeOperands
]> {

  let summary = "Compare values two values and produce a boolean result";
  let description = [{
  }];


  let results = (outs Aten_BoolType:$result);
  let arguments = (ins Arg<CmpOpPredicate, "cmp predicate">:$predicate, AnyType:$lhs, AnyType:$rhs);

  let assemblyFormat = [{
    `(` $predicate `,` $lhs `,` $rhs  `)` `:` type($lhs) `,` type($result) attr-dict
  }];

  // Already covered by the traits
  let hasVerifier = 0;
}

//===----------------------------------------------------------------------===//
// Aten Struct Element Addr
//===----------------------------------------------------------------------===//

def Aten_StructElementAddr : Aten_Op<"struct_element_addr"> {
  let summary = "Get the address of a member of a struct";
  let description = [{
  }];

  let arguments = (ins
    Arg<Aten_PointerType, "the address to load from", [MemRead]>:$struct_addr,
    StrAttr:$member_name,
    IndexAttr:$member_index);

  let results = (outs Res<Aten_PointerType, "">:$result);

  let builders = [
    OpBuilder<(ins "Type":$type, "Value":$value, "llvm::StringRef":$name,
              "unsigned":$index),
    [{
      mlir::APInt fieldIdx(64, index);
      build($_builder, $_state, type, value, name, fieldIdx);
    }]>
  ];

  let extraClassDeclaration = [{
    uint64_t getIndex() { return getMemberIndex().getZExtValue(); }
  }];
}

//===----------------------------------------------------------------------===//
// Function & Call
//===----------------------------------------------------------------------===//

#endif //! AUTOTEN_IR_OPS_TD