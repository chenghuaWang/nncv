#ifndef NNCV_NNCV_LINALG_EXT_PASSES
#define NNCV_NNCV_LINALG_EXT_PASSES

include "mlir/Pass/PassBase.td"

def TileAndDecomposeWinogradTransform : Pass<"nncv-linalg-ext-tile-and-decompose-winograd", "func::FuncOp"> {
    let summary = "Tiles and decomposes winograd transform ops into linalg ops";
    let constructor = "mlir::nncv::linalg_ext::createTileAndDecomposeWinogradTransformPass()";
    let options = [
        Option<"onlyTile", "onlyTile", "bool", /*default=*/"false", 
        "Choose whether to only tile or go through till decomposition">,
    ];
}

#endif //! NNCV_NNCV_LINALG_EXT_PASSES