/**
 * @file SymbolRef.hpp
 * @author chenghua wang (chenghua.wang.edu@google.com)
 * @brief The symbol ref class for aten language parser.
 * @version 0.1
 * @date 2023-07-19
 *
 * @details The symbol ref class using singleton design pattern. And I use random access stack to
 * manage the symbol table in different scope. It works like a state machine.
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef NNCV_COMPILER_UTILS_SYMBOL_REF_HPP
#define NNCV_COMPILER_UTILS_SYMBOL_REF_HPP

#if defined(_WIN32) && _MSC_VER > 1000
#pragma once
#elif defined(_unix_)
#pragma once
#endif  //! check msc version

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/ScopedHashTable.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/ArrayRef.h"

#include "mlir/IR/Attributes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Verifier.h"

#include <vector>
#include <optional>
#include <unordered_map>

namespace nncv {
namespace compiler {
namespace utils {

// only need namespace to generate function name.
// lld will check if they are in the symbol table or not.
static std::vector<std::string> __rt_namespace__ = {"std", "io", "nncv"};

enum AtenSymbolTableState { kGlobal = 0, kInner = 1 };

enum AtenFunctionType { kGeneral = 0, kImpl = 1 };

struct AtenFunctionSymbolPaylod {
  // basic type check
  mlir::Type retType;
  mlir::TypeRange argumentsType;
  // visibility
  AtenFunctionType funcType;
  bool isPublic;
};

struct AtenStructSymbolPaylod {
  // basic type check
  std::vector<std::tuple<std::string, mlir::Type, bool>>
      argumentsLists;  ///> name, type, visibility

  std::optional<std::pair<mlir::Type, size_t>> getVarTypeAndPositionInStruct(
      const std::string& varName);
};

//===----------------------------------------------------------------------===//
// Aten Symbol Module Name Attribute
//===----------------------------------------------------------------------===//
struct AtenModuleNameAttr {
  AtenModuleNameAttr(const std::string& name) : name(name) {}
  std::string name;
};

class RandomAccessSymbolStack {};

class AtenSymbolTableG {
 public:
  std::optional<AtenFunctionSymbolPaylod&> getFunctionSymbol(const std::string& funcName);
  std::optional<AtenStructSymbolPaylod&> getStructSymbol(const std::string& structName);
  std::optional<mlir::Value&> getVarSymbol(const std::string& varSymbol);

  bool registerFuncSymbol(const std::string& funcName, AtenFunctionSymbolPaylod& payload);
  bool registerStructSymbol(const std::string& structName, AtenStructSymbolPaylod& payload);
  bool registerVarSymbol(const std::string& varName, mlir::Value value);

 private:
  AtenSymbolTableState stateLevel;
  llvm::ScopedHashTable<llvm::StringRef, mlir::Value> varSymbolTable;
  llvm::ScopedHashTable<llvm::StringRef, AtenStructSymbolPaylod> structSymbolTable;
  llvm::ScopedHashTable<llvm::StringRef, AtenFunctionSymbolPaylod> funcSymbolTable;
};

class AtenSymbolRef {
 public:
  AtenSymbolRef();
  ~AtenSymbolRef();

  void newContext();
  void deleteCurContext();

  bool funcVerify(const std::string& funcName, mlir::Type retType, mlir::TypeRange argumentsType);
  bool structVerify(const std::string& structName, const std::string& argumentName);

  // This function will not be used most of the time. I think people just need to verify a function
  AtenFunctionSymbolPaylod getFuncSymbol(const std::string& funcName);  ///> use `funcVerify` first.
  // The normally usage of this function is:
  // if (structVerify(StructName, argumentName))
  //    AtenSymbolRef.getStructSymbol(StructName).getVarTypeAndPositionInStruct(varName)
  AtenStructSymbolPaylod getStructSymobl(
      const std::string& structName);  ///> use `structVerify` first

  bool registerFuncSymbol(const std::string& funcName, AtenFunctionSymbolPaylod& payload);
  bool registerStructSymbol(const std::string& structName, AtenStructSymbolPaylod& payload);

  std::optional<mlir::Value> getVarValueSymbol(const std::string& varName);
  bool registerVarSymbol(const std::string& varName, mlir::Value value);

  void createVarSymbolTableOnTop();
  void deleteVarSymbolTableOnTop();

  bool writeCache(const std::string& path);  ///< using database
  bool readCache(const std::string& path);   ///< using database

  inline AtenSymbolRef* getParent() { return m_parent; }

  // Using m_parent to get _ModuleA_ModuleB,
  // flag = 0: attrs' size = 1, for struct and var and normal func
  // flag = 1: attrs's size = 2, for func in the `impl`, attrs[0] is fun name, atrrs[1] is impl name
  inline std::string reNameSymbol(const std::vector<std::string>& attrs, bool flag = 0) {
    std::string ret;
    AtenSymbolRef* tmp = this;
    while (tmp != nullptr) {
      ret = "_" + tmp->m_name + ret;
      tmp = tmp->m_parent;
    }
    if (flag) {
      return ret + "_" + attrs[1] + "_" + attrs[0];
    } else {
      return ret + "_" + attrs[0];
    }
  }

 private:
  void clearAll();

  std::string m_name;
  AtenSymbolRef* m_parent;
  RandomAccessSymbolStack m_stack;
};

class AtenSymbolTable {
 public:
  AtenSymbolTable();
  ~AtenSymbolTable();

  static AtenSymbolTable* getInstance() { return instance; }

  inline AtenSymbolRef* getSymbolRefOfModule(const AtenModuleNameAttr& attr) {
    auto it = m_SymbolRefs.find(attr.name);
    if (it == m_SymbolRefs.end()) {
      // TODO emit a error
      return nullptr;
    }
    return it->second;
  }

  inline AtenSymbolRef* createSymbolRefOfModule(const AtenModuleNameAttr& attr) {
    auto it = new AtenSymbolRef();
    m_SymbolRefs[attr.name] = it;
    return it;
  }

  inline void deleteSymbolRefOfModule(const AtenModuleNameAttr& attr) {
    auto it = m_SymbolRefs.find(attr.name);
    if (it != m_SymbolRefs.end()) {
      auto ptr = it->second;
      m_SymbolRefs.erase(it);
      delete ptr;
    } else {
      // TODO emic error
      return;
    }
  }

  inline AtenSymbolRef* operator[](const AtenModuleNameAttr& attr) {
    return getSymbolRefOfModule(attr);
  }

 private:
  std::unordered_map<std::string, AtenSymbolRef*> m_SymbolRefs;

  static AtenSymbolTable* instance;
};

}  // namespace utils
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_UTILS_SYMBOL_REF_HPP