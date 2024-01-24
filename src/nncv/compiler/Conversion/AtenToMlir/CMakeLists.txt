add_mlir_conversion_library(AtenToArithConversion
    AtenToMlir.cpp
    AtenMlirToLlvm.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/compiler/Conversion/AtenToMlir

    DEPENDS
    NncvConversionPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    MLIRAtenLang
)