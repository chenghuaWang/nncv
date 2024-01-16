add_mlir_library(NNCVLinalgExtDialect
  LinalgExtDialect.cpp
  LinalgExtInterfaces.cpp
  LinalgExtOps.cpp

  ADDITIONAL_HEADER_DIRS
  ${PROJECT_SRC_DIR}/include/nncv/compiler/Dialects/LinalgExt/LinalgExt

  DEPENDS
  NNCVLinalgExtIncGen

  LINK_LIBS PUBLIC
  MLIRAffineDialect
  MLIRAffineUtils
  MLIRArithUtils
  MLIRDestinationStyleOpInterface
  MLIRDialectUtils
  MLIRIR
  MLIRInferTypeOpInterface
  MLIRLinalgDialect
  MLIRLinalgUtils
  MLIRMathDialect
  MLIRMemRefDialect
  MLIRPass
  MLIRSideEffectInterfaces
  MLIRSupport
  MLIRSCFDialect
  MLIRFuncDialect
  MLIRTensorDialect
  MLIRTensorUtils
  MLIRTilingInterface
  MLIRViewLikeInterface
)