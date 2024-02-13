#ifndef NNCV_NNCV_GRAPH_OPS_TD
#define NNCV_NNCV_GRAPH_OPS_TD

include "nncv/compiler/Dialects/NncvGraph/IR/NncvGraphDialect.td"
include "nncv/compiler/Dialects/NncvGraph/IR/NncvGraphInterface.td"

include "mlir/IR/OpBase.td"
include "mlir/IR/SymbolInterfaces.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

class NncvGraph_Op<string mnemonic, list<Trait> traits = []> : Op<NncvGraph_Dialect, mnemonic, traits> {
    let hasCustomAssemblyFormat = 1;
}

class NncvGraph_PureOp<string mnemonic, list<Trait> traits = []> : NncvGraph_Op<mnemonic, !listconcat(traits, [Pure])>;


def NncvGraph_WorkerOp : NncvGraph_PureOp<"worker" , [
    NncvGraph_ShapeAwareOpInterface,
    AttrSizedOperandSegments
]> {
    let summary = [{A work contains multiple operations}];
    let description = [{
        Organized All Operations to a work.
    }];

    let arguments = (ins NncvGraph_ShapeDynamicDims:$result_dims, Variadic<NncvGraph_Dim>:$workload);
    let results = (outs Variadic<AnyType>:$result);
    let regions = (region AnyRegion:$body);

    let hasCanonicalizer = 1;
    let hasCustomAssemblyFormat = 1;
    let hasVerifier = 1;

    let extraClassDeclaration = [{
        ValueRange getOperandDynamicDims(unsigned idx) { return ValueRange{}; }
        ValueRange getResultDynamicDims(unsigned idx);
    }];
}

def NncvGraph_WorkerGroupOp : NncvGraph_Op<"worker_group", [
    NncvGraph_ShapeAwareOpInterface,
    IsolatedFromAbove,
]> {
    let summary = [{A work group with multiple works}];
    let description = [{
        A group of works that can be execute in one time.
    }];

    let results = (outs Variadic<AnyType>:$result);
    let regions = (region AnyRegion:$body);

    let hasCanonicalizer = 1;
    let hasCustomAssemblyFormat = 1;
    let hasVerifier = 1;
}

#endif //! NNCV_NNCV_GRAPH_OPS_TD
