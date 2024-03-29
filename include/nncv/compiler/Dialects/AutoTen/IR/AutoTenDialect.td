/**
* @autor chenghua.wang
* @mail chenghua.wang.edu@gmail.com
* 
* This file defined the Aten-lang's dialect based on mlir. Before start to implement.
* The Toy-lang tutorial provided by LLVM official is which I should go through first.
* Also, the LLVM's TableGen document is highly recommend to read.
*
* Some ref:
* 1. https://harmonyhu.com/2021/08/17/mlir/
*/
#ifndef AUTOTEN_IR_DIALECT_TD
#define AUTOTEN_IR_DIALECT_TD

include "mlir/IR/OpBase.td"

//===----------------------------------------------------------------------===//
// Aten Dialect Define
//===----------------------------------------------------------------------===//
def Aten_Dialect : Dialect {
    let name = "Aten";
    let summary = "A high performance, go-lang like language. Optimized for polyhedral algorithms";
    let cppNamespace = "::mlir::aten";

    let description = [{
        Aten(Auto tensor) is the dialects of Aten language. This language will translate with nncv.
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

#endif //! AUTOTEN_IR_DIALECT_TD