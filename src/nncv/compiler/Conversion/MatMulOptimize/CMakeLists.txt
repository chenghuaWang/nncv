add_mlir_conversion_library(MatMulOptimizeConversion
    BatchMatMulOptVec.cpp
    MatMulOptDefault.cpp
    MatMulOptParallelVec.cpp
    MatMulOptVec.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/compiler/Conversion/MatMulOptimize

    DEPENDS
    NncvConversionPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    MLIRAtenLang
    NNCVLinalgExtDialect
)