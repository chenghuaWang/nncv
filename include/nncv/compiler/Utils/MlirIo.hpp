#pragma once

#ifndef NNCV_COMPILER_UTILS_MLIR_IO_HPP
#define NNCV_COMPILER_UTILS_MLIR_IO_HPP

#include "mlir/IR/BuiltinOps.h"

namespace nncv {
namespace compiler {
namespace utils {

bool SaveMlirModuleToFile(mlir::OwningOpRef<mlir::ModuleOp>& m, const std::string& filep);

}  // namespace utils
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_UTILS_MLIR_IO_HPP