add_mlir_conversion_library(NncvLinalgOptimizeConversion
    LinalgGenericTile.cpp
    CastAwayTensorLeadingOneDim.cpp
    LinalgPoolTile.cpp
    RegisterLinalgOps.cpp
    OneShotTiling.cpp
    DecomposeTransGen.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Conversion/LinalgOptimize

    DEPENDS
    NncvConversionPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRArithDialect
    NNCVLinalgExtDialect
    MLIRLinalgDialect
    MLIRLinalgTransforms
    MLIRLinalgUtils
)