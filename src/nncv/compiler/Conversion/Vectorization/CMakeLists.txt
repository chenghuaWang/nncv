add_mlir_conversion_library(NncvVectorizationConversion
    Vec.cpp
    VectorizePad.cpp
    OptimizeInsertExtractSlices.cpp
    FoldTensorSubsetIntoVectorTransferOps.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/compiler/Conversion/Vectorization

    DEPENDS
    NncvConversionPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    NNCVLinalgExtDialect
)