#ifndef NNCV_GRAPH_IR_DIALECT_TD
#define NNCV_GRAPH_IR_DIALECT_TD

include "mlir/IR/OpBase.td"

//===----------------------------------------------------------------------===//
// NNCV Graph Dialect Define
//===----------------------------------------------------------------------===//
def NncvGraph_Dialect : Dialect {
    let name = "nncvgraph";
    let summary = "nncv graph level optimization dialect";
    let cppNamespace = "::mlir::nncv::graph";

    let description = [{
        NNCV Graph is a high-level representation of a deepl learning model.
    }];
    
    let useDefaultTypePrinterParser = 0;
    let useDefaultAttributePrinterParser = 1;

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

def NncvGraph_Dim : TypeAlias<Index>;
def NncvGraph_ShapeDynamicDims : Variadic<NncvGraph_Dim>;
def NncvGraph_Tensor : TypeAlias<AnyRankedTensor>;


#endif //! NNCV_GRAPH_IR_DIALECT_TD