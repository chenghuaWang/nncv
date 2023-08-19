/**
 * @file BuiltinMethodHandler.hpp
 * @author chenghua.wang (chenghua.wang.edu@gmail.com)
 * @brief The handler of built in op set. VERSION 0.0.1
 * @version 0.1
 * @date 2023-08-13
 *
 * @copyright Copyright (c) 2023
 *
 */

// will be include multiple times.
#pragma once

#include <optional>
#include <string>
#include <functional>
#include <unordered_map>
#include <utility>

#include "mlir/IR/Builders.h"

namespace nncv {
namespace compiler {
namespace frontend {

enum class __tensor_method_type : int32_t {
  kExtract = 0,
  kInsert = 1,
};

struct __tensor_method_set {
  template<typename... Args>
  static std::optional<mlir::Value> tensor_extract_handler(mlir::OpBuilder* builder);
};

static std::unordered_map<std::string, __tensor_method_type> __TensorBuiltInMethodSet = {
    {"__tensor_extract", __tensor_method_type::kExtract},
};

template<typename... Args>
static std::optional<std::pair<bool, std::optional<mlir::Value>>> tensorMethodHandler(
    const std::string& StrType, mlir::OpBuilder* builder, Args&&... args) {
  auto item = __TensorBuiltInMethodSet.find(StrType);
  if (item == __TensorBuiltInMethodSet.end()) {
    return std::make_optional(std::make_pair(false, {}));  // {} will construct nullopt_t
  }

  switch (item->second) {
    case __tensor_method_type::kExtract: {
      auto ans = __tensor_method_set::tensor_extract_handler(builder, std::forward<Args>(args)...);
      return std::make_optional(std::make_pair(true, ans));
    }
    case __tensor_method_type::kInsert: break;
  }
}

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv