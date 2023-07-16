add_mlir_conversion_library(
    AtenToArithConversion

    AtenToArith.cpp

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    # TODO May need to link aten dialect. And best if AtenDialect cmake target is renamed.
)