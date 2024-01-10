#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"
#include "nncv/compiler/Dialects/AutoTen/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/AutoTen/Transforms/Passes.hpp"

namespace mlir::nncv::aten {

namespace {

class EliminateStoreLoadPattern final : public mlir::OpRewritePattern<mlir::aten::ReturnOp> {
 public:
  using OpRewritePattern::OpRewritePattern;

  mlir::LogicalResult matchAndRewrite(mlir::aten::ReturnOp retOp,
                                      mlir::PatternRewriter& rewriter) const override {
    if (retOp->getNumOperands() == 0) {
      // is void return
      return mlir::failure();
    }

    auto prevOp = retOp->getPrevNode();  // expect load op.
    if (prevOp == nullptr) { return mlir::failure(); }

    auto prevPrevOp = prevOp->getPrevNode();  // expect store op.
    if (prevPrevOp == nullptr) { return mlir::failure(); }

    auto excutionOp = prevPrevOp->getPrevNode();  // expect binOp or other Op that return values.
    if (excutionOp == nullptr) { return mlir::failure(); }

    auto loadOp = dyn_cast<mlir::aten::LoadOp>(prevOp);
    auto storeOp = dyn_cast<mlir::aten::StoreOp>(prevPrevOp);

    // normally, we will have:
    // %1 = Aten.binop(add, %arg0, %arg1) : !Aten.int<s, 64>
    // Aten.store %1, %0 : !Aten.int<s, 64>, aten.ptr <!Aten.int<s, 64>>
    // %2 = Aten.load %0 : aten.ptr <!Aten.int<s, 64>>, !Aten.int<s, 64>
    // Aten.return %2 : !Aten.int<s, 64>
    if (!loadOp || !storeOp) { return mlir::failure(); }

    auto loadFrom = loadOp->getOperands()[0];
    auto StoreTo = storeOp.getOperands()[1];
    auto valueToStore = storeOp.getOperands()[0];
    auto execOpRetValue = excutionOp->getResults()[0];

    auto loadRet = loadOp.getResult();
    auto retValue = retOp->getOperands()[0];

    if ((loadRet == retValue) && (execOpRetValue == valueToStore) && (StoreTo == loadFrom)) {
      auto op = rewriter.create<mlir::aten::ReturnOp>(retOp->getLoc(), execOpRetValue);
      rewriter.replaceOp(retOp, op);
      rewriter.eraseOp(loadOp);
      rewriter.eraseOp(storeOp);
      return mlir::success();
    }
    return mlir::failure();
  }
};

class EliminateTailReturnLoad : public EliminateTailReturnLoadBase<EliminateTailReturnLoad> {
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::aten::AtenDialect>();
    return;
  }

  void runOnOperation() override {
    mlir::MLIRContext* context = &getContext();
    mlir::RewritePatternSet patterns(context);

    // insert rewrite patternt
    patterns.insert<EliminateStoreLoadPattern>(context);

    // do rewrite
    if (mlir::failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      // no need to signalPassFailure();
      return;
    }

    return;
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createEliminateTailReturnLoadPass() {
  return std::make_unique<EliminateTailReturnLoad>();
}

}  // namespace mlir::nncv::aten