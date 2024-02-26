add_mlir_conversion_library(NncvCodeGenLlvmGpuConversion
    ModernVecGpu.cpp
    ModernTileGpu.cpp
    Passes.cpp
    PrepareModernVecGpu.cpp
    GpuUtils.cpp

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