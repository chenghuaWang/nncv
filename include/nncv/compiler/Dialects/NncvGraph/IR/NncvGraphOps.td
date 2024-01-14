#ifndef NNCV_NNCV_GRAPH_OPS_TD
#define NNCV_NNCV_GRAPH_OPS_TD

include "nncv/compiler/Dialects/NncvGraph/IR/NncvGraphDialect.td"

include "mlir/IR/OpBase.td"
include "mlir/IR/SymbolInterfaces.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

class NncvGraph_Op<string mnemonic, list<Trait> traits = []> : Op<NncvGraph_Dialect, mnemonic, traits>;

def NodeOp : NncvGraph_Op<"NodeOp"> {
    
}


#endif //! NNCV_NNCV_GRAPH_OPS_TD
