#ifndef NNCV_GRAPH_IR_DIALECT_TD
#define NNCV_GRAPH_IR_DIALECT_TD

include "mlir/IR/OpBase.td"

//===----------------------------------------------------------------------===//
// NNCV Graph Dialect Define
//===----------------------------------------------------------------------===//
def NncvGraph_Dialect : Dialect {
    let name = "nncvgraph";
    let summary = "nncv graph level optimization dialect";
    let cppNamespace = "::mlir::nncv";

    let description = [{
        NNCV Graph is a high-level representation of a deepl learning model.
    }];
    
    let useDefaultAttributePrinterParser = 0;
    let useDefaultTypePrinterParser = 0;

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

    let extraClassDeclaration = [{
        void registerAttributes();
        void registerTypes();

        ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;
        void printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const override;

        ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                        ::mlir::Type type) const override;

        void printAttribute(::mlir::Attribute attr,
                            ::mlir::DialectAsmPrinter &os) const override;
    }];
}


#endif //! NNCV_GRAPH_IR_DIALECT_TD