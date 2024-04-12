add_mlir_conversion_library(NncvCodeGenAdvanceConversion
    FinalVec.cpp
    PeeledDispatchedToParallel.cpp
    TileAndDispatch.cpp
    VecDispatched.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/compiler/Conversion/CodeGen/Advance

    DEPENDS
    NncvConversionPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    NNCVLinalgExtDialect
)