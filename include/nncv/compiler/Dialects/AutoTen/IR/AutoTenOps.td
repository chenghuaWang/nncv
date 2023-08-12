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
// Aten Ptr Get Refernce Op
//===----------------------------------------------------------------------===//

def GetRefOp : Aten_Op<"get_ref", [
    DeclareOpInterfaceMethods<InferTypeOpInterface>,
    Pure
]> {
    let summary = "Get the reference of a object";
    let description = [{
    }];

    let arguments = (ins AnyType:$value);

    let results = (outs Aten_PointerType:$res);

    let assemblyFormat = [{
        $value attr-dict `:` type($value) `->` type($res)
    }];

    // InferTypeOpInterface will make sure everything is right.
    let hasVerifier = 0;
}

//===----------------------------------------------------------------------===//
// Aten Load Op (can be used as deref)
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
// Aten Store Op
//===----------------------------------------------------------------------===//

def StoreOp : Aten_Op<"store", [
    TypesMatchWith<"type of 'value' matches pointee type of 'addr'",
                    "addr", "value",
                    "$_self.cast<PointerType>().getPointee()">
]> {
    let summary = "Store value to memory address";
    let description = [{
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
    Aten_UnaryOp_Inc,
    Aten_UnaryOp_Dec,
    Aten_UnaryOp_Plus,
    Aten_UnaryOp_Minus,
    Aten_UnaryOp_Not
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
    Pure,
    SameOperandsAndResultType
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
//
// Highly referenced from mlir.func 's impl.
//===----------------------------------------------------------------------===//

def Aten_FuncOp : Aten_Op <"func", [
    AutomaticAllocationScope, 
    CallableOpInterface, 
    FunctionOpInterface,
    IsolatedFromAbove, 
    Symbol
]> {
    let summary = "Declare or define a function";
    let description = [{

    }];

    let arguments = (ins 
        SymbolNameAttr:$sym_name,
        TypeAttrOf<Aten_FuncType>:$function_type,
        Aten_ExtFuncAttr:$extra_attrs,
        OptionalAttr<StrAttr>:$sym_visibility,
        OptionalAttr<DictArrayAttr>:$arg_attrs,
        OptionalAttr<DictArrayAttr>:$res_attrs
    );

    let regions = (region AnyRegion:$body);
    let skipDefaultBuilders = 1;

    let builders = [OpBuilder<(ins
        "StringRef":$name, 
        "FuncType":$type,
        CArg<"ArrayRef<NamedAttribute>", "{}">:$attrs,
        CArg<"ArrayRef<DictionaryAttr>", "{}">:$argAttrs
    )>];

    let extraClassDeclaration = [{
        /// Returns the region on the current operation that is callable. This may
        /// return null in the case of an external callable object, e.g. an external
        /// function.
        ::mlir::Region *getCallableRegion();

        /// Returns the results types that the callable region produces when
        /// executed.
        ArrayRef<Type> getCallableResults() {
        if (::llvm::isa<aten::VoidType>(getFunctionType().getReturnType()))
            return {};
        return getFunctionType().getReturnTypes();
        }

        /// Returns the argument attributes for all callable region arguments or
        /// null if there are none.
        ::mlir::ArrayAttr getCallableArgAttrs() {
        return getArgAttrs().value_or(nullptr);
        }

        /// Returns the result attributes for all callable region results or null if
        /// there are none.
        ::mlir::ArrayAttr getCallableResAttrs() {
        return getResAttrs().value_or(nullptr);
        }

        /// Returns the argument types of this function.
        ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

        /// Returns the result types of this function.
        ArrayRef<Type> getResultTypes() { return getFunctionType().getReturnTypes(); }

        /// Hook for OpTrait::FunctionOpInterfaceTrait, called after verifying that
        /// the 'type' attribute is present and checks if it holds a function type.
        /// Ensures getType, getNumFuncArguments, and getNumFuncResults can be
        /// called safely.
        LogicalResult verifyType();

        //===------------------------------------------------------------------===//
        // SymbolOpInterface Methods
        //===------------------------------------------------------------------===//

        bool isDeclaration();
    }];

    let hasCustomAssemblyFormat = 1;
    let hasVerifier = 1;
}

def CallOp : Aten_Op<"call", [
    CallOpInterface, 
    DeclareOpInterfaceMethods<SymbolUserOpInterface>
]> {
    let summary = "call operation";
    let description = [{
    }];

    let arguments = (ins OptionalAttr<FlatSymbolRefAttr>:$callee, Variadic<AnyType>:$operands);
    let results = (outs Variadic<AnyType>);

    let builders = [
        OpBuilder<(ins "FuncOp":$callee, CArg<"ValueRange", "{}">:$operands), [{
        $_state.addOperands(operands);
        $_state.addAttribute("callee", SymbolRefAttr::get(callee));
        if (!callee.getFunctionType().isVoid())
            $_state.addTypes(callee.getFunctionType().getReturnType());
        }]>,
        OpBuilder<(ins "Value":$ind_target, "FuncType":$fn_type, CArg<"ValueRange", "{}">:$operands), [{
        $_state.addOperands(ValueRange{ind_target});
        $_state.addOperands(operands);
        if (!fn_type.isVoid())
            $_state.addTypes(fn_type.getReturnType());
        }]
    >];

    let extraClassDeclaration = [{
        mlir::Value getIndirectCallee() {
            assert(!getCallee() && "only works for indirect call");
            return *arg_operand_begin();
        }

        operand_iterator arg_operand_begin() {
            auto arg_begin = operand_begin();
            if (!getCallee())
                arg_begin++;
            return arg_begin;
        }
        operand_iterator arg_operand_end() { return operand_end(); }

        /// Get the argument operands to the called function.
        operand_range getArgOperands() {
            return {arg_operand_begin(), arg_operand_end()};
        }

        /// Return the operand at index 'i', accounts for indirect call.
        Value getArgOperand(unsigned i) {
            if (!getCallee()) i++;
            return getOperand(i);
        }

        /// Return the number of operands, accounts for indirect call.
        unsigned getNumArgOperands() {
            if (!getCallee())
                return this->getOperation()->getNumOperands()-1;
            return this->getOperation()->getNumOperands();
        }

        /// Return the callee of this operation.
        CallInterfaceCallable getCallableForCallee() {
            return (*this)->getAttrOfType<SymbolRefAttr>("callee");
        }

        /// Set the callee for this operation.
        void setCalleeFromCallable(mlir::CallInterfaceCallable callee) {
            if (auto calling =
                (*this)->getAttrOfType<mlir::SymbolRefAttr>(getCalleeAttrName()))
                (*this)->setAttr(getCalleeAttrName(), callee.get<mlir::SymbolRefAttr>());
            setOperand(0, callee.get<mlir::Value>());
        }
    }];

    let hasCustomAssemblyFormat = 1;
    let skipDefaultBuilders = 1;
    let hasVerifier = 0;
}

def ReturnOp : Aten_Op<"return", [ 
    HasParent<"FuncOp">,
    Terminator
]> {
    let summary = "Return from function";
    let description = [{
    }];

    let arguments = (ins Variadic<AnyType>:$input);

    let assemblyFormat = "($input^ `:` type($input))? attr-dict ";

    let builders = [
        OpBuilder<(ins), [{ build($_builder, $_state, std::nullopt); }]>
    ];

    let extraClassDeclaration = [{
        bool hasOperand() { return getNumOperands() != 0; }
    }];

    let hasVerifier = 1;
}

//===----------------------------------------------------------------------===//
// Struct Symbol
//===----------------------------------------------------------------------===//

def Aten_MakeStructSymbol : Aten_Op<"make_struct_symbol", [
    Symbol, 
    DeclareOpInterfaceMethods<RegionBranchOpInterface>, 
    NoRegionArguments
]> {
    let summary = "Declare a struct type. A temp struct symbol for multi-file compile";
    let description = [{
        This Op works in such circumstance: file `a.lang` want to use a struct that defined in `b.lang`.
        And you don't want to let `a.lang` know the defination of struct in high-level language but using mlir.
        As we all know that !llvm.struct is just a type. It's not bing treated as a defination such as func.func.
        In that case, I use a symbol like defination to let `a.mlir` know there has a struct def in `b.mlir`.

        In `b.mlir`:
        ```mlir
            aten.make_struct_symbol @foo = #aten.const_struct<{0 : i8,
                                                               5 : i64, 
                                                               #aten.null : !aten.ptr<i8>
                                                            }> : !aten.struct<"", i8, i64, !aten.ptr<i8>>
        ``` 

        When loweirng `a.lang` to `a.mlir` and `a.lang` want to know the def of struct `foo`. It can load pre-compiled
        `b.mlir` and using `lookup` function to find the symbol `foo`. Due to `foo` is a `const_struct`, it know all info
        of types in struct `foo`.

        *Note*:
        1. this Op should not appear into the code u want to run. It's just a helper Op. When loweing to LLVM, it should be
            eliminated.
        2. I highly comment you to generate two files for `b.lang`. One for symbol check up, while another has all regions.
    }];

    let arguments = (ins SymbolNameAttr:$sym_name,
                       TypeAttr:$sym_type,
                       OptionalAttr<AnyAttr>:$initial_value,
                       OptionalAttr<I64Attr>:$alignment
                    );

    let regions = (region AnyRegion:$ctorRegion);
    let assemblyFormat = [{
        $sym_name
        custom<StructSymbolOpTypeAndInitialValue>($sym_type, $initial_value, $ctorRegion)
        attr-dict
    }];

    let skipDefaultBuilders = 1;
    let builders = [
        OpBuilder<(ins
        "StringRef":$sym_name,
        "Type":$sym_type)>
    ];

    let hasVerifier = 1;
}

//===----------------------------------------------------------------------===//
// Global Value
//===----------------------------------------------------------------------===//

/// TODO

#endif //! AUTOTEN_IR_OPS_TD