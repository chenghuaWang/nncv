/**
* @autor chenghua.wang
* @mail chenghua.wang.edu@gmail.com
*/
#ifndef AUTOTEN_IR_TYPES_TD
#define AUTOTEN_IR_TYPES_TD

include "nncv/compiler/Dialects/AutoTen/IR/AutoTenDialect.td"

include "mlir/IR/AttrTypeBase.td"
include "mlir/Interfaces/DataLayoutInterfaces.td"

//===----------------------------------------------------------------------===//
// Notes: 
//
// This file just defined the most common types that will be used in aten-lang. 
// The `string` type can be composed by `!aten.array<len> : !aten.char<8>` for 
// ASCII or `!aten.array<len> : !aten.char<16>` for UTF-8.
// 
// The `map` type is not implement yet. But it still will not appeared in this file
// `map` is a ptr returned from runtime lib.
//===----------------------------------------------------------------------===//


//===----------------------------------------------------------------------===//
// Aten Types
//===----------------------------------------------------------------------===//

class Aten_Type<string name, string typeMnemonic, list<Trait> traits = []> :
    TypeDef<Aten_Dialect, name, traits> {
    let mnemonic = typeMnemonic;
}

//===----------------------------------------------------------------------===//
// Aten Int Types
//===----------------------------------------------------------------------===//

def Aten_IntegerType : Aten_Type<"Int", "int", [
    DeclareTypeInterfaceMethods<DataLayoutTypeInterface>
]> {
    let summary = "Integer with limited bitwidth";
    let description = [{
        i8, i16, i32, i64 is supported. Both of those types has singed/unsinged.
    }];
    let parameters = (ins "unsigned":$width, "bool":$isSigned);
    let hasCustomAssemblyFormat = 1;
    let extraClassDeclaration = [{
        bool isSigned() const { return getIsSigned(); }
        bool isUnsigned() const { return !getIsSigned(); }
        std::string getAlias() const {
        return (isSigned() ? 's' : 'u') + std::to_string('i') + std::to_string(getWidth());
        };
    }];
    let genVerifyDecl = 1;
}

//===----------------------------------------------------------------------===//
// Aten Float Types
//===----------------------------------------------------------------------===//

// def Aten_FloatType : Aten_Type<"Float", "float", [
//     DeclareTypeInterfaceMethods<DataLayoutTypeInterface>
// ]> {
//     let summary = "float with limited bitwidth";
//     let description = [{
//         f32, f64 is supported.
//     }];
//     let parameters = (ins "unsigned":$width);
//     let hasCustomAssemblyFormat = 1;
//     let genVerifyDecl = 1;
// }

//===----------------------------------------------------------------------===//
// Aten Bool Types
//===----------------------------------------------------------------------===//

def Aten_BoolType : Aten_Type<"Bool", "bool", [
    DeclareTypeInterfaceMethods<DataLayoutTypeInterface>
]> {
    let summary = "Aten bool type";
    let description = [{
        `!aten.bool` represent's a bool type. Will be lowering to mlir.i1 or mlir.i8.
        depending where bool value is located in(alias).
    }];

    let hasCustomAssemblyFormat = 1;
}

//===----------------------------------------------------------------------===//
// Aten Char Types
//===----------------------------------------------------------------------===//

def Aten_CharType : Aten_Type<"Char", "char", [
    DeclareTypeInterfaceMethods<DataLayoutTypeInterface>
]> {
    let summary = "Char with limited bitwidth";
    let description = [{
        ui8, ui16, is supported.
    }];
    let parameters = (ins "unsigned":$width, "bool":$isUtf);
    let hasCustomAssemblyFormat = 1;
    let extraClassDeclaration = [{
        bool isUtf() const { return getIsUtf(); }
        bool isUnUtf() const { return !getIsUtf(); }
        std::string getAlias() const {
        return "ci" + std::to_string(getWidth());
        };
    }];
    let genVerifyDecl = 1;
}

//===----------------------------------------------------------------------===//
// Aten Pointer Types
//===----------------------------------------------------------------------===//

def Aten_PointerType : Aten_Type<"Pointer", "ptr", [
    DeclareTypeInterfaceMethods<DataLayoutTypeInterface>
]> {
    let summary = "Aten pointer type";
    let description = [{
        `!aten.ptr` is a typed pointer. If the type is Tensor, then it will be translate
        to memref when lowering.
    }];

    let parameters = (ins "mlir::Type":$pointee);

    let hasCustomAssemblyFormat = 1;
}

//===----------------------------------------------------------------------===//
// Aten Func Type
//===----------------------------------------------------------------------===//

def Aten_FuncType : Aten_Type<"Func", "func"> {
    let summary = "Aten function type";
    let description = [{

    }];

    let parameters = (ins ArrayRefParameter<"Type">:$inputs, "Type":$returnType, "bool":$varArg);
    let assemblyFormat = [{
        `<` $returnType ` ` `(` custom<FuncTypeArgs>($inputs, $varArg) `>`
    }];

    let builders = [
        TypeBuilderWithInferredContext<(ins
        "ArrayRef<Type>":$inputs, 
        "Type":$returnType,
        CArg<"bool", "false">:$isVarArg), 
        [{
            return $_get(returnType.getContext(), inputs, returnType, isVarArg);
        }]>
    ];

    let extraClassDeclaration = [{
        /// Returns whether the function is variadic.
        bool isVarArg() const { return getVarArg(); }

        /// Returns the `i`th input operand type. Asserts if out of bounds.
        Type getInput(unsigned i) const { return getInputs()[i]; }

        /// Returns the number of arguments to the function.
        unsigned getNumInputs() const { return getInputs().size(); }

        /// Returns the result type of the function as an ArrayRef, enabling better
        /// integration with generic MLIR utilities.
        ArrayRef<Type> getReturnTypes() const;

        /// Returns whether the function is returns void.
        bool isVoid() const;

        /// Returns a clone of this function type with the given argument
        /// and result types.
        FuncType clone(TypeRange inputs, TypeRange results) const;
    }];
}

//===----------------------------------------------------------------------===//
// Aten Struct Types
//===----------------------------------------------------------------------===//

def Aten_StructType : Aten_Type<"Struct", "struct", [
    DeclareTypeInterfaceMethods<DataLayoutTypeInterface>
]> {
    let summary = "Aten struct type";
    let description = [{
        Aten AST/CST will map a Table Decl to Struct Type in `!aten.struct<...>`
        which will be directly lowering to `llvm.struct<>`.
    }];

    let parameters = (ins
        ArrayRefParameter<"mlir::Type", "members">:$members,
        "mlir::StringAttr":$typeName,
        "bool":$body,
        "bool":$packed
    );

    let builders = [
        TypeBuilder<(ins
        "ArrayRef<mlir::Type>":$members, "StringRef":$typeName,
        "bool":$body
        ), [{
            auto id = mlir::StringAttr::get(context, typeName);
            auto sTy = StructType::get(context, members, id, body, /*packed=*/false);
            return sTy;
        }]>
  ];

    let hasCustomAssemblyFormat = 1;

    let extraClassDeclaration = [{
    private:
        // All these support lazily computation and storage
        // for the struct size and alignment.
        mutable std::optional<unsigned> size{}, align{};
        mutable std::optional<bool> padded{};
        void computeSizeAndAlignment(const ::mlir::DataLayout &dataLayout) const;
    public:
        size_t getNumElements() const { return getMembers().size(); }
        bool isOpaque() const { return !getBody(); }
        bool isPadded(const ::mlir::DataLayout &dataLayout) const;
    }];
}

//===----------------------------------------------------------------------===//
// Aten Array Types
//===----------------------------------------------------------------------===//

def Aten_ArrayType : Aten_Type<"Array", "array", [
    DeclareTypeInterfaceMethods<DataLayoutTypeInterface>
]> {
    let summary = "Aten array type";
    let description = [{
        `!aten.array` only for constant array. If you want to have a dynamic array, use
        `new []int32` pls.
    }];

    let parameters = (ins "mlir::Type":$eleT, "uint64_t":$sizeT);

    let assemblyFormat = [{
        `<` $eleT `x` $sizeT `>`
    }];
}

//===----------------------------------------------------------------------===//
// Aten Void type
//===----------------------------------------------------------------------===//

def Aten_VoidType : Aten_Type<"Void", "void"> {
    let summary = "Aten void type";
    let description = [{
        `!aten.void` is a default return for `aten.func`
    }];
    let extraClassDeclaration = [{
        /// Returns a clone of this type with the given context.
        std::string getAlias() const { return "void"; };
    }];
}

//===----------------------------------------------------------------------===//
// All Tensor first class type
//===----------------------------------------------------------------------===//

def Aten_TensorType : TensorOf<[
    Aten_IntegerType, 
    F32,
    F64
]>;

//===----------------------------------------------------------------------===//
// All types that we may need in ops
//===----------------------------------------------------------------------===//

def Aten_AnyAtenType : AnyTypeOf<[
    Aten_PointerType, 
    Aten_BoolType, 
    Aten_StructType,
    Aten_ArrayType, 
    Aten_VoidType
]>;


#endif //! AUTOTEN_IR_TYPES_TD