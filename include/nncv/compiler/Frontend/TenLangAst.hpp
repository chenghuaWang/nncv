/**
 * @file TenLangAst.hpp
 * @author chenghua.Wang (chenghua.wang.edu@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-06-01
 *
 * @details Ast impl is reference from clang:
 * https://clang.llvm.org/docs/IntroductionToTheClangAST.html
 * @copyright Copyright (c) 2023
 *
 */
#ifndef NNCV_COMPILER_TEN_LANG_AST_HPP_
#define NNCV_COMPILER_TEN_LANG_AST_HPP_

#pragma once

#if defined(_WIN32) && _MSC_VER < 1900
#error MS Compiler version need higher than 1900
#endif

#include "nncv/compiler/Frontend/TenLangLexer.hpp"

#include <string>
#include <memory>
#include <vector>

namespace nncv {
namespace compiler {
namespace frontend {

class ExprAst;
class VariableExprAst;
class BinaryExprAst;
class CallExpAst;
class PrototypeAst;

using ExprAstPtr = std::unique_ptr<ExprAst>;
using VecExprAstPtr = std::vector<ExprAstPtr>;
using VariableExprAstPtr = std::unique_ptr<VariableExprAst>;
using BinaryExprAstPtr = std::unique_ptr<BinaryExprAst>;
using CallExprAstPtr = std::unique_ptr<CallExpAst>;
using PrototypeAstPtr = std::unique_ptr<PrototypeAst>;

class ExprAst {
 public:
  ExprAst(const Location& _loc);
  virtual ~ExprAst() = default;

 private:
  Location m_Loc;
};

/// Normal Variables. Such as 'int a = 1'(a is var).
class VariableExprAst : public ExprAst {
  std::string m_Name;

 public:
  VariableExprAst(const Location& _loc, const std::string& _name) : ExprAst(_loc), m_Name(_name) {}
};

/// Binary Expression.
class BinaryExprAst : public ExprAst {
  std::string m_Op;
  ExprAstPtr m_LHS, m_RHS;

 public:
  BinaryExprAst(const Location& _loc, const std::string& _op, ExprAstPtr _lhs, ExprAstPtr _rhs)
      : ExprAst(_loc), m_Op(_op), m_LHS(std::move(_lhs)), m_RHS(std::move(_rhs)) {}
};

/// Funcion calls.
class CallExprAst : public ExprAst {
  std::string m_Callee;
  std::vector<std::unique_ptr<ExprAst>> m_Args;

 public:
  CallExprAst(const Location& _loc, const std::string& _callee, VecExprAstPtr _args)
      : ExprAst(_loc), m_Callee(_callee), m_Args(std::move(_args)) {}
};

/// PrototypeAst - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAst {
  std::string m_Name;
  std::vector<std::string> m_Args;

 public:
  PrototypeAst(const std::string& _name, std::vector<std::string> _args)
      : m_Name(_name), m_Args(std::move(_args)) {}

  const std::string& GetName() const { return m_Name; }
};

/// The behavior of a function does.
class FunctionAst {
  PrototypeAstPtr m_Proto;
  ExprAstPtr m_Body;

 public:
  FunctionAst(PrototypeAstPtr _proto, ExprAstPtr _body)
      : m_Proto(std::move(_proto)), m_Body(std::move(_body)) {}
};

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_TEN_LANG_AST_HPP_