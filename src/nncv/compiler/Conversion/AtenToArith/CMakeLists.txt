add_mlir_conversion_library(AtenToArithConversion
    AtenToArith.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/compiler/Conversion/AtenToArith

    DEPENDS
    NncvConversionPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    MLIRAtenLang
)