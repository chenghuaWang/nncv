#ifndef NNCV_NNCV_FRONTEND_PASSES
#define NNCV_NNCV_FRONTEND_PASSES

include "mlir/Pass/PassBase.td"

def MLProgramBufferize: Pass<"nncv-frontend-mlprogram-bufferize", "ModuleOp"> {
  let summary = "Bufferize the MLProgram dialect ops";
  let constructor = "mlir::nncv::createMLProgramBufferizePass();";
  let dependentDialects = ["memref::MemRefDialect"];
}

#endif // NNCV_NNCV_FRONTEND_PASSES