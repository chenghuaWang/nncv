#ifndef NNCV_LINALGEXT_DIALECT
#define NNCV_LINALGEXT_DIALECT

include "mlir/IR/OpBase.td"
include "mlir/IR/AttrTypeBase.td"
include "mlir/IR/EnumAttr.td"

def NNCV_LinalgExt_Dialect : Dialect {
  let name = "nncv_linalg_ext";
  let cppNamespace = "::mlir::nncv::linalg_ext";
  let summary = [{
    NNCV Linalg Extensions.
  }];
  let description = [{
    Extension:
    winogradOp,
  }];
  let useDefaultAttributePrinterParser = 1;
}

class NNCVLinalgExt_Attr<string name, list<Trait> traits = []> : AttrDef<NNCV_LinalgExt_Dialect, name, traits>;

class NNCVLinalgExt_I32EnumAttr<string name, string summary, list<I32EnumAttrCase> cases>
    : I32EnumAttr<name, summary, cases> {
  let cppNamespace = "::mlir::nncv::linalg_ext";
  let genSpecializedAttr = 0;
}

class NNCVLinalgExt_EnumAttr<EnumAttrInfo enumInfo, string name = "">
  : EnumAttr<NNCV_LinalgExt_Dialect, enumInfo, name>;

def MATMUL : I32EnumAttrCase<"MATMUL", 0>;
def BATCH_MATMUL : I32EnumAttrCase<"BATCH_MATMUL", 1>;

def EncodingUser : NNCVLinalgExt_I32EnumAttr<"EncodingUser",
    "Describes the operation that a tensor is an operand or a result of.", [
      MATMUL,
      BATCH_MATMUL,
    ]>;

def EncodingUserAttr :
  NNCVLinalgExt_EnumAttr<EncodingUser, "user">;

def LHS : I32EnumAttrCase<"LHS", 0>;
def RHS : I32EnumAttrCase<"RHS", 1>;
def RESULT : I32EnumAttrCase<"RESULT", 2>;

def EncodingRole : NNCVLinalgExt_I32EnumAttr<"EncodingRole",
    "Describes the role of the tensor as an operand or a result of an operation.", [
      LHS,
      RHS,
      RESULT,
    ]>;

def EncodingRoleAttr :
  NNCVLinalgExt_EnumAttr<EncodingRole, "role">;

def EncodingAttr :
    NNCVLinalgExt_Attr<"Encoding"> {
  let mnemonic = "encoding";
  let summary = [{information to decide how to data-tile a tensor}];
   let description = [{
    This attribute describes the change in the layout for
    a given tensor to execute subsequent operations on
    the tiled layout. The encoding serves as a way to
    represent the change in the way the data is laid out in
    memory without changing the logical rank/extent of
    the tensor itself. When required, the encoding
    can be used to explicitly manifest the layout change
    through operations like pack/unpack.
  }];

  let assemblyFormat = "`<` struct(params) `>`";

  let parameters = (ins
    AttrParameter<"EncodingUserAttr", "kind of operation using this tensor">:$user,
    AttrParameter<"EncodingRoleAttr", "role of this tensor as an operand">:$role,
    AttrParameter<"ArrayAttr", "element types of the user's operands">:$element_types,
    OptionalParameter<"TypeAttr", "type of the original tensor type before padding">:$original_type,
    OptionalParameter<"IntegerAttr", "optional M narrow dimension size (only for MATMUL and BATCH_MATMUL users)">:$matmul_narrow_M,
    OptionalParameter<"IntegerAttr", "optional N narrow dimension size (only for MATMUL and BATCH_MATMUL users)">:$matmul_narrow_N,
    OptionalParameter<"ArrayAttr", "Indexing maps of the operation using this tensor">:$user_indexing_maps
  );

  let genVerifyDecl = 0;
}

#endif //! NNCV_LINALGEXT_DIALECT