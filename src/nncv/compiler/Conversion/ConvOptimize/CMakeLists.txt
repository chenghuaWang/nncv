add_mlir_conversion_library(ConvOptimizeConversion
    ConvertOptimizedConv2dToAffine.cpp
    OptimizeConv2dUsingCB.cpp
    OptimizeConv2dUsingWinograd.cpp
    OptimizeConv2dUsingQnnPack.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/compiler/Conversion/ConvOptimize

    DEPENDS
    NncvConversionPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    MLIRAtenLang
    NNCVLinalgExtDialect
)