add_mlir_conversion_library(NncvTransformsConversion
    NestedTransformErase.cpp
    RemoveSelfMemRefCopy.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/compiler/Conversion/Transforms

    DEPENDS
    NncvConversionPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    NNCVLinalgExtDialect
)