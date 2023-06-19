#ifndef AUTOTEN_OPS_TD
#define AUTOTEN_OPS_TD

include "mlir/IR/OpBase.td"
include "mlir/IR/FunctionInterfaces.td"
include "mlir/IR/SymbolInterfaces.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

def ATen_Dialect : Dialect {
    let name = "Aten";
    let namespace = "::mlir::aten";
    let description = [{
        Aten(Auto tensor) is the dialects of Aten language. This language will translate to nncv.
    }]
    let hasConstantMaterializer = 1;
    let useDefaultTypePrinterParser = 1;
}

class Aten_Op<string mnemonic, list<Trait> traits = []> : Op<Aten_Dialect, mnemonic, traits>;

def Aten_StructType :
    DialectType<Aten_Dialect, CPred<"::llvm::isa<StructType>($_self)">,
                "Aten struct type">;

def Aten_Type : AnyTypeOf<[F64Tensor, Aten_StructType]>; // TODO

//===----------------------------------------------------------------------===//
// Aten Operations
//===----------------------------------------------------------------------===//

def AddOp : Aten_Op<"add",
    [Pure, DeclareOpInterfaceMethods<ShapeInferenceOpInterface>]> {
  let summary = "element-wise addition operation";
  let description = [{
    The "add" operation performs element-wise addition between two tensors.
    The shapes of the tensor operands are expected to match.
  }];

  let arguments = (ins F64Tensor:$lhs, F64Tensor:$rhs);
  let results = (outs F64Tensor);

  // Indicate that the operation has a custom parser and printer method.
  let hasCustomAssemblyFormat = 1;

  // Allow building an AddOp with from the two input operands.
  let builders = [
    OpBuilder<(ins "Value":$lhs, "Value":$rhs)>
  ];
}

#endif //! AUTOTEN_OPS_TD