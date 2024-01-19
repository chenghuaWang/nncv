#ifndef NNCV_NNCV_GRAPH_INTERFACE_TD
#define NNCV_NNCV_GRAPH_INTERFACE_TD

include "mlir/IR/OpBase.td"

def NncvGraph_ShapeAwareOpInterface : OpInterface<"ShapeAwareOpInterface"> {
  let cppNamespace = "::mlir::nncv::graph";

  let methods = [
    InterfaceMethod<
      [{Returns dynamic dimensions for the given shaped operand index.}],
      "mlir::ValueRange", "getOperandDynamicDims", (ins "unsigned":$idx)
    >,
    InterfaceMethod<
      [{Returns dynamic dimensions for the given shaped result index.}],
      "mlir::ValueRange", "getResultDynamicDims", (ins "unsigned":$idx)
    >,
    InterfaceMethod<
      [{Returns dynamic dimensions for the given shaped result value.}],
      "mlir::ValueRange", "getResultDynamicDimsFromValue", (ins "Value":$value),
      /*defaultImplementation=*/[{
        for (unsigned i = 0; i < $_self->getNumResults(); ++i) {
          if ($_self->getResult(i) == value) {
            return $_self.getResultDynamicDims(i);
          }
        }
        return {};
      }]
    >,
    InterfaceMethod<
      /*desc=*/[{Returns a full shape for the given shaped operand index.}],
      /*retTy=*/"SmallVector<Value>",
      /*methodName=*/"buildOperandShape",
      /*args=*/(ins "unsigned":$idx, "OpBuilder &":$builder),
      /*defaultImplementation=*/[{
        return ::mlir::nncv::graph::buildOperandShape($_self, idx, builder);
      }]
    >,
    InterfaceMethod<
      /*desc=*/[{Returns a full shape for the given shaped result index.}],
      /*retTy=*/"SmallVector<Value>",
      /*methodName=*/"buildResultShape",
      /*args=*/(ins "unsigned":$idx, "OpBuilder &":$builder),
      /*defaultImplementation=*/[{
        return ::mlir::nncv::graph::buildResultShape($_self, idx, builder);
      }]
    >,
    StaticInterfaceMethod<
      /*desc=*/[{Builds a full shape for the given shaped result value.}],
      /*retTy=*/"SmallVector<Value>",
      /*methodName=*/"buildResultValueShape",
      /*args=*/(ins "Value":$result, "OpBuilder &":$builder),
      /*methodBody=*/[{
        auto shapeAwareOp = dyn_cast<::mlir::nncv::graph::ShapeAwareOpInterface>(result.getDefiningOp());
        return shapeAwareOp.buildResultShape(
            result.cast<mlir::OpResult>().getResultNumber(), builder);
      }]
    >,
  ];
}

#endif //! NNCV_NNCV_GRAPH_INTERFACE_TD