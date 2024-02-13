#include "nncv/compiler/Conversion/AtenToMlir/AtenMlirToLlvm.hpp"

// All dialect
#include "mlir/Conversion/TensorToLinalg/TensorToLinalg.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlow.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"

// Conversion
#include "mlir/Conversion/AffineToStandard/AffineToStandard.h"
#include "mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/Conversion/ControlFlowToLLVM/ControlFlowToLLVM.h"
#include "mlir/Conversion/FuncToLLVM/ConvertFuncToLLVM.h"
#include "mlir/Conversion/FuncToLLVM/ConvertFuncToLLVMPass.h"
#include "mlir/Conversion/LLVMCommon/ConversionTarget.h"
#include "mlir/Conversion/LLVMCommon/TypeConverter.h"
#include "mlir/Conversion/MemRefToLLVM/MemRefToLLVM.h"
#include "mlir/Conversion/SCFToControlFlow/SCFToControlFlow.h"
#include "mlir/IR/BuiltinDialect.h"
#include "mlir/Transforms/DialectConversion.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_CONVERTATENMLIRTOLLVM
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class ConvertAtenMlirToLlvmPass
    : public impl::ConvertAtenMlirToLlvmBase<ConvertAtenMlirToLlvmPass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                    mlir::memref::MemRefDialect, mlir::arith::ArithDialect,
                    mlir::cf::ControlFlowDialect, mlir::scf::SCFDialect, mlir::LLVM::LLVMDialect>();
  }

  void runOnOperation() override {
    mlir::LLVMConversionTarget target(getContext());
    target.addLegalOp<mlir::ModuleOp>();
    mlir::LLVMTypeConverter typeConverter(&getContext());
    mlir::RewritePatternSet patterns(&getContext());

    // Affine for loops
    mlir::populateAffineToStdConversionPatterns(patterns);

    // Arith
    mlir::arith::populateArithToLLVMConversionPatterns(typeConverter, patterns);

    // Scf to CF
    mlir::populateSCFToControlFlowConversionPatterns(patterns);

    // CF to Llvm
    mlir::cf::populateControlFlowToLLVMConversionPatterns(typeConverter, patterns);

    // Memref to LLVM
    mlir::populateFinalizeMemRefToLLVMConversionPatterns(typeConverter, patterns);

    // Func to Llvm
    mlir::populateFuncToLLVMConversionPatterns(typeConverter, patterns);

    // apply
    auto module = getOperation();
    if (failed(mlir::applyPartialConversion(module, target, std::move(patterns))))
      signalPassFailure();
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createConvertAtenMlirToLlvmPass() {
  return std::make_unique<ConvertAtenMlirToLlvmPass>();
}

}  // namespace mlir::nncv