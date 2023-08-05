/**
* @autor chenghua.wang
* @mail chenghua.wang.edu@gmail.com
*/
#ifndef AUTOTEN_IR_ATTRI_TD
#define AUTOTEN_IR_ATTRI_TD

include "nncv/compiler/Dialects/AutoTen/IR/AutoTenDialect.td"

include "mlir/IR/BuiltinAttributeInterfaces.td"
include "mlir/IR/EnumAttr.td"

//===----------------------------------------------------------------------===//
// Noes:
//
// `char` type will eats ui8 and ui16
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Aten Attribute Define
//===----------------------------------------------------------------------===//

class Aten_Attr<string name, string attrMnemonic, list<Trait> traits = []>
    : AttrDef<Aten_Dialect, name, traits> {
  let mnemonic = attrMnemonic;
}

//===----------------------------------------------------------------------===//
// Aten Nil Attri
//===----------------------------------------------------------------------===//

def Aten_NullAttr : Aten_Attr<"Nil", "nil", [
    TypedAttrInterface
]> {
  let summary = "Attri for nil ptr";
  let description = [{
    Only for `!aten.ptr`
  }];
  let parameters = (ins AttributeSelfTypeParameter<"">:$type);
  let builders = [
    AttrBuilderWithInferredContext<(ins "Type":$type), [{
      return $_get(type.getContext(), type);
    }]>
  ];
  let assemblyFormat = [{}];
}

//===----------------------------------------------------------------------===//
// Aten Bool Attri
//===----------------------------------------------------------------------===//

def Aten_BoolAttr : Aten_Attr<"Bool", "bool", [
  TypedAttrInterface
]> {
  let summary = "true or false";
  let description = [{
    The BoolAttr represents a 'true' or 'false' value.
  }];
  let parameters = (ins AttributeSelfTypeParameter<
                        "", "mlir::aten::BoolType">:$type,
                    "bool":$value);

  let assemblyFormat = [{
    `<` $value `>`
  }];
}

//===----------------------------------------------------------------------===//
// Aten Const Array Attri
//===----------------------------------------------------------------------===//

def Aten_ConstArrayAttr : Aten_Attr<"ConstArray", "constArray", [
  TypedAttrInterface
]> {
  let summary = "constant make array";
  let description = [{
    Array of literals of the specified attr types.
  }];
  let parameters = (ins AttributeSelfTypeParameter<"">:$type,
                        "Attribute":$elts);
  let builders = [
    AttrBuilderWithInferredContext<(ins "mlir::aten::ArrayType":$type,
                                        "Attribute":$elts), [{
      return $_get(type.getContext(), type, elts);
    }]>
  ];
  let hasCustomAssemblyFormat = 1;
  let genVerifyDecl = 1;
}

//===----------------------------------------------------------------------===//
// Aten Const Struct Attr
//===----------------------------------------------------------------------===//

def AtenConstStructAttr : Aten_Attr<"ConstStruct", "constStruct", [
  TypedAttrInterface
]> {
  let summary = "constant make struct";
  let description = [{
    Eats data from ArrayAttr. 
  }];
  let parameters = (ins AttributeSelfTypeParameter<"">:$type,
                        "ArrayAttr":$members);
  let builders = [
    AttrBuilderWithInferredContext<(ins "mlir::aten::StructType":$type,
                                        "ArrayAttr":$members), [{
      return $_get(type.getContext(), type, members);
    }]>
  ];
  let assemblyFormat = [{
    `<` custom<StructMembers>($members) `>`
  }];
  let genVerifyDecl = 1;
}

//===----------------------------------------------------------------------===//
// Aten Integer Attri
//===----------------------------------------------------------------------===//

def Aten_IntAttr : Aten_Attr<"Int", "int", [
  TypedAttrInterface
]> {
  let summary = "integer value of i8, i16, i32, i64";
  let description = [{
    i8, i16, i32, i64
  }];
  let parameters = (ins AttributeSelfTypeParameter<"">:$type, "APInt":$value);
  let builders = [
    AttrBuilderWithInferredContext<(ins "Type":$type,
                                        "const APInt &":$value), [{
      return $_get(type.getContext(), type, value);
    }]>,
    AttrBuilderWithInferredContext<(ins "Type":$type, "int64_t":$value), [{
      IntType intType = type.cast<IntType>();
      mlir::APInt apValue(intType.getWidth(), value, intType.isSigned());
      return $_get(intType.getContext(), intType, apValue);
    }]>,
  ];
  let extraClassDeclaration = [{
    int64_t getSInt() const { return getValue().getSExtValue(); }
    uint64_t getUInt() const { return getValue().getZExtValue(); }
    bool isNilValue() const { return getValue() == 0; }
  }];
  let genVerifyDecl = 1;
  let hasCustomAssemblyFormat = 1;
}

//===----------------------------------------------------------------------===//
// Aten Float Attri
// FIXME: APFloat constructor usage is wrong?
//===----------------------------------------------------------------------===//

def Aten_FloatAttr : Aten_Attr<"Float", "float", [
  TypedAttrInterface
]> {
  let summary = "integer value of i8, i16, i32, i64";
  let description = [{
    i8, i16, i32, i64
  }];
  let parameters = (ins AttributeSelfTypeParameter<"">:$type, "APFloat":$value);
  let builders = [
    AttrBuilderWithInferredContext<(ins "Type":$type,
                                        "const APFloat &":$value), [{
      return $_get(type.getContext(), type, value);
    }]>,
    AttrBuilderWithInferredContext<(ins "Type":$type, "double":$value), [{
      if (type.isF64() || !::llvm::isa<FloatType>(type))
        return $_get(type.getContext(), type, APFloat(value));

      // This handles, e.g., F16 because there is no APFloat constructor for it.
      bool unused;
      APFloat val(value);
      val.convert(::llvm::cast<FloatType>(type).getFloatSemantics(),
                  APFloat::rmNearestTiesToEven, &unused);
      return $_get(type.getContext(), type, val);
    }]>
  ];
  let genVerifyDecl = 1;
  let hasCustomAssemblyFormat = 1;
}

#endif //! AUTOTEN_IR_ATTRI_TD