add_mlir_conversion_library(NncvLinalgOptimizeConversion
    LinalgGenericTile.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/compiler/Conversion/LinalgOptimize

    DEPENDS
    NncvConversionPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    NNCVLinalgExtDialect
)