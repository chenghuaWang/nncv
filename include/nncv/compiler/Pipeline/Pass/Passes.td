#ifndef NNCV_RUNNER_PIPELINE_PASSES
#define NNCV_RUNNER_PIPELINE_PASSES

include "mlir/Pass/PassBase.td"

def MLProgramBufferize: Pass<"nncv-mlprogram-bufferize", "ModuleOp"> {
  let summary = "Bufferize the MLProgram dialect ops";
  let constructor = "mlir::nncv::createMLProgramBufferizePass();";
  let dependentDialects = ["memref::MemRefDialect"];
}

#endif // NNCV_RUNNER_PIPELINE_PASSES