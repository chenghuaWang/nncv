#include <queue>
#include <stack>
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/Operation.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"
#include "nncv/compiler/Dialects/AutoTen/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/AutoTen/Transforms/Passes.hpp"

namespace mlir::nncv::aten {

namespace {

bool isInAffineForScope(mlir::Operation* op) {
  mlir::Operation* top = op->getParentOp();
  while (top) {
    if (mlir::isa<mlir::affine::AffineForOp>(top)) { return true; }
    top = top->getParentOp();
  }
  return false;
}

struct ForOpValueMap {
  void insertOp(mlir::affine::AffineForOp op) { forOp.push_back(op); }

  llvm::SmallVector<mlir::affine::AffineForOp> forOp;
};

struct MapValueAndPosition {
  bool hasValue(mlir::Value v) {
    for (auto [_v, _] : data) {
      if (_v == v) return true;
    }
    return false;
  }

  void set(mlir::Value v, int pos) {
    if (!hasValue(v)) data.push_back({v, pos});
  }

  int getPos(mlir::Value v) {
    for (auto [_v, _pos] : data) {
      if (_v == v) return _pos;
    }
    return -1;
  }

  size_t size() { return data.size(); }

  std::vector<std::pair<mlir::Value, int>> data;
};

mlir::AffineExpr buildTree(mlir::PatternRewriter& rewriter, mlir::Operation* op,
                           MapValueAndPosition& allNewOperand, int& curPos) {
  auto isArithExpr = [](mlir::Operation* op) -> bool {
    return mlir::isa<arith::AddIOp>(op) || mlir::isa<arith::MulIOp>(op)
           || mlir::isa<arith::SubIOp>(op) || mlir::isa<arith::DivUIOp>(op);
  };

  auto isConstantIndexExpr = [](mlir::Operation* op) -> bool {
    return mlir::isa<arith::ConstantOp>(op)
           && mlir::cast<arith::ConstantOp>(op).getResult().getType().isa<mlir::IndexType>();
  };

  auto mapArithToSymbol = [](mlir::Operation* op) -> char {
    if (mlir::isa<arith::AddIOp>(op)) return '+';
    if (mlir::isa<arith::MulIOp>(op)) return '*';
    if (mlir::isa<arith::SubIOp>(op)) return '-';
    if (mlir::isa<arith::DivUIOp>(op)) return '/';
  };

  if (isConstantIndexExpr(op)) {
    return rewriter.getAffineConstantExpr(
        mlir::cast<arith::ConstantOp>(op).getValueAttr().cast<mlir::IntegerAttr>().getInt());
  }

  auto lhs = op->getOperand(0);
  auto rhs = op->getOperand(1);

  mlir::AffineExpr lhsExpr;
  mlir::AffineExpr rhsExpr;

  //  process lhs
  if (lhs.getDefiningOp() && isArithExpr(lhs.getDefiningOp())) {
    lhsExpr = buildTree(rewriter, lhs.getDefiningOp(), allNewOperand, curPos);
  } else if (lhs.getDefiningOp() && isConstantIndexExpr(lhs.getDefiningOp())) {
    lhsExpr = rewriter.getAffineConstantExpr(mlir::cast<arith::ConstantOp>(lhs.getDefiningOp())
                                                 .getValueAttr()
                                                 .cast<mlir::IntegerAttr>()
                                                 .getInt());
  } else {
    // check is in current Operand or not.
    if (!allNewOperand.hasValue(lhs)) { allNewOperand.set(lhs, curPos++); }
    lhsExpr = rewriter.getAffineDimExpr(allNewOperand.getPos(lhs));
  }

  // process rhs
  if (rhs.getDefiningOp() && isArithExpr(rhs.getDefiningOp())) {
    rhsExpr = buildTree(rewriter, rhs.getDefiningOp(), allNewOperand, curPos);
  } else if (rhs.getDefiningOp() && isConstantIndexExpr(rhs.getDefiningOp())) {
    rhsExpr = rewriter.getAffineConstantExpr(mlir::cast<arith::ConstantOp>(rhs.getDefiningOp())
                                                 .getValueAttr()
                                                 .cast<mlir::IntegerAttr>()
                                                 .getInt());
  } else {
    // check is in current Operand or not.
    if (!allNewOperand.hasValue(rhs)) { allNewOperand.set(rhs, curPos++); }
    rhsExpr = rewriter.getAffineDimExpr(allNewOperand.getPos(rhs));
  }

  switch (mapArithToSymbol(op)) {
    case '+': return lhsExpr + rhsExpr;
    case '-': return lhsExpr - rhsExpr;
    case '*': return lhsExpr * rhsExpr;
    case '/': {
      printf("[ Erro ] Divide between Affine Index is not supportted yes\n");
      exit(-1);
      break;
    }
  }
}

std::pair<mlir::AffineMap, mlir::ValueRange> traceIndicesAndTurnItToMapExpr(
    mlir::PatternRewriter& rewriter, mlir::OperandRange range) {
  llvm::SmallVector<mlir::AffineExpr> exprs;
  llvm::SmallVector<mlir::Value> retRange;
  MapValueAndPosition allNewOperand;
  int curPos = 0;

  auto isArithExpr = [](mlir::Operation* op) -> bool {
    return mlir::isa<arith::AddIOp>(op) || mlir::isa<arith::MulIOp>(op)
           || mlir::isa<arith::SubIOp>(op) || mlir::isa<arith::DivUIOp>(op);
  };

  auto isConstantIndexExpr = [](mlir::Operation* op) -> bool {
    return mlir::isa<arith::ConstantOp>(op)
           && mlir::cast<arith::ConstantOp>(op).getResult().getType().isa<mlir::IndexType>();
  };

  for (auto operand : range) {
    // get which op defined this operand
    auto op = operand.getDefiningOp();

    // check if this op is calculated or not.
    if (op && (isArithExpr(op) || isConstantIndexExpr(op))) {
      exprs.push_back(buildTree(rewriter, op, allNewOperand, curPos));
    } else {
      // is created by affine.for or arith.constant
      if (!allNewOperand.hasValue(operand)) { allNewOperand.set(operand, curPos++); }
      exprs.push_back(rewriter.getAffineDimExpr(allNewOperand.getPos(operand)));
      continue;
    }
  }

  // return if all empty;
  if (exprs.empty()) {
    return std::make_pair(mlir::AffineMap::get(rewriter.getContext()), mlir::ValueRange{});
  }

  // turn allNewOperand to mlir::ValueRange
  retRange.resize(allNewOperand.data.size());
  for (auto& item : allNewOperand.data) { retRange[item.second] = item.first; }
  auto amp = mlir::AffineMap::get(/*dim count*/ retRange.size(), /*symbol count*/ 0,
                                  /*affine expression*/ exprs, /*contex*/ rewriter.getContext());

  return std::make_pair(amp, retRange);
}

class MemrefLoadToAffineLoardPattern final : public mlir::OpRewritePattern<mlir::memref::LoadOp> {
 public:
  using OpRewritePattern::OpRewritePattern;
  mlir::LogicalResult matchAndRewrite(mlir::memref::LoadOp op,
                                      mlir::PatternRewriter& rewriter) const override {
    if (isInAffineForScope(op)) {
      // trace all affine for op at top affine
      llvm::SmallVector<mlir::affine::AffineForOp> AffineForOps;
      {
        // find the top affine.for
        mlir::Operation* top = op->getParentOp();
        mlir::affine::AffineForOp topAffineForOp;
        while (top) {
          if (mlir::isa<mlir::affine::AffineForOp>(top)) {
            topAffineForOp = mlir::cast<mlir::affine::AffineForOp>(top);
          }
          top = top->getParentOp();
        }

        // using the top affine for to get all affine for ops in this scope
        // NOTICE: The walk function will include the topAffineForOp. Which means it will walk
        // through the top level op.
        topAffineForOp.walk([&](mlir::affine::AffineForOp op) { AffineForOps.push_back(op); });
      }

      // process all affine symbols and values.
      if (op.getIndices().empty()) {
        rewriter.replaceOpWithNewOp<mlir::affine::AffineLoadOp>(op,
                                                                /*memref*/ op.getMemRef());
      } else {
        // trace op.getIndices and build
        auto [_map, _vr] = traceIndicesAndTurnItToMapExpr(rewriter, op.getIndices());

        // check forops, and reget all indicies
        llvm::SmallVector<mlir::Value> indicies;
        for (size_t i = 0; i < _vr.size(); ++i) {
          for (size_t j = 0; j < AffineForOps.size(); ++j) {
            if (_vr[i] == AffineForOps[j].getInductionVar()) {
              indicies.push_back(AffineForOps[j].getInductionVar());
            }
          }
        }

        assert(_vr.size() == indicies.size());

        if (_map.isEmpty()) {
          rewriter.replaceOpWithNewOp<mlir::affine::AffineLoadOp>(op,
                                                                  /*memref*/ op.getMemRef(),
                                                                  /*operand*/ op.getIndices());
        } else {
          rewriter.replaceOpWithNewOp<mlir::affine::AffineLoadOp>(op,
                                                                  /*memref*/ op.getMemRef(),
                                                                  /*map*/ _map,
                                                                  /*operand*/ indicies);
        }
      }
      return mlir::LogicalResult::success();
    } else {
      return mlir::LogicalResult::failure();
    }
    return mlir::LogicalResult::failure();
  }
};

class MemrefStoreToAffineStorePattern final : public mlir::OpRewritePattern<mlir::memref::StoreOp> {
 public:
  using OpRewritePattern::OpRewritePattern;
  mlir::LogicalResult matchAndRewrite(mlir::memref::StoreOp op,
                                      mlir::PatternRewriter& rewriter) const override {
    if (isInAffineForScope(op)) {
      // trace all affine for op at top affine
      llvm::SmallVector<mlir::affine::AffineForOp> AffineForOps;
      {
        // find the top affine.for
        mlir::Operation* top = op->getParentOp();
        mlir::affine::AffineForOp topAffineForOp;
        while (top) {
          if (mlir::isa<mlir::affine::AffineForOp>(top)) {
            topAffineForOp = mlir::cast<mlir::affine::AffineForOp>(top);
          }
          top = top->getParentOp();
        }

        // using the top affine for to get all affine for ops in this scope
        // NOTICE: The walk function will include the topAffineForOp. Which means it will walk
        // through the top level op.
        topAffineForOp.walk([&](mlir::affine::AffineForOp op) { AffineForOps.push_back(op); });
      }

      // process all affine symbols and values.
      if (op.getIndices().empty()) {
        rewriter.replaceOpWithNewOp<mlir::affine::AffineStoreOp>(
            op,
            /*value to store*/ op.getValueToStore(), /*Memref*/ op.getMemRef(),
            /*indicies*/ op.getIndices());
      } else {
        // trace op.getIndices and build
        auto [_map, _vr] = traceIndicesAndTurnItToMapExpr(rewriter, op.getIndices());

        // check forops, and reget all indicies
        llvm::SmallVector<mlir::Value> indicies;
        for (size_t i = 0; i < _vr.size(); ++i) {
          for (size_t j = 0; j < AffineForOps.size(); ++j) {
            if (_vr[i] == AffineForOps[j].getInductionVar()) {
              indicies.push_back(AffineForOps[j].getInductionVar());
            }
          }
        }

        assert(_vr.size() == indicies.size());

        if (_map.isEmpty()) {
          rewriter.replaceOpWithNewOp<mlir::affine::AffineStoreOp>(
              op,
              /*value to store*/ op.getValueToStore(), /*Memref*/ op.getMemRef(),
              /*indicies*/ op.getIndices());
        } else {
          rewriter.replaceOpWithNewOp<mlir::affine::AffineStoreOp>(
              op,
              /*value to store*/ op.getValueToStore(), /*Memref*/ op.getMemRef(),
              /*map*/ _map,
              /*indicies*/ indicies);
        }
      }

      return mlir::LogicalResult::success();
    } else {
      return mlir::LogicalResult::failure();
    }
    return mlir::LogicalResult::failure();
  }
};

class RaiseMemerefLSInAffineToAffineLSPass final
    : public RaiseMemerefLSInAffineToAffineLSBase<RaiseMemerefLSInAffineToAffineLSPass> {
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::affine::AffineDialect, mlir::memref::MemRefDialect,
                    mlir::aten::AtenDialect>();
    return;
  }

  void runOnOperation() override {
    mlir::MLIRContext* context = &getContext();
    mlir::RewritePatternSet patterns(context);

    // insert rewrite patternt
    patterns.insert<MemrefLoadToAffineLoardPattern, MemrefStoreToAffineStorePattern>(context);

    // do rewrite
    if (mlir::failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      return;
    }
    return;
  };
};

}  // namespace

std::unique_ptr<mlir::Pass> createRaiseMemerefLSInAffineToAffineLSPass() {
  return std::make_unique<RaiseMemerefLSInAffineToAffineLSPass>();
}

}  // namespace mlir::nncv::aten