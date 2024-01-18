add_mlir_library(NNCVLinalgExtPasses
  Passes.cpp
  TileAndDecoWinogradPass.cpp

  DEPENDS
  NNCVLinalgExtPassesIncGen

  LINK_LIBS PUBLIC
  NNCVLinalgExtDialect
  MLIRAffineDialect
  MLIRIR
  MLIRLinalgDialect
  MLIRLinalgTransforms
  MLIRMathDialect
  MLIRMemRefDialect
  MLIRMemRefTransforms
  MLIRPass
  MLIRSCFDialect
  MLIRFuncDialect
  MLIRSupport
  MLIRTensorDialect
  MLIRTransforms
)