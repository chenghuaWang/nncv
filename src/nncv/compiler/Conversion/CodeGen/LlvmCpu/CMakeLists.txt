add_mlir_conversion_library(NncvCodeGenLlvmCpuConversion
    ModernVec.cpp
    ModernTile.cpp
    Passes.cpp
    PrepareModernVec.cpp
    PeelAfterTile.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/compiler/Conversion/CodeGen/LlvmCpu

    DEPENDS
    NncvConversionPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    NNCVLinalgExtDialect
)