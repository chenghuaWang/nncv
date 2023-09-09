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

#ifndef _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#endif

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

// A singleton for reference.
// class Singleton {
// public:
// 	static Singleton& getInstance(){
// 		static Singleton instance;
// 		return instance;
// 	}
// private:
// 	Singleton ()= default;
// 	~Singleton ()= default;
// 	Singleton (const Singleton &)= delete;
// 	Singleton & operator=(const Singleton &)= delete;
// };

// only need namespace to generate function name.
// lld will check if they are in the symbol table or not.
static std::vector<std::string> __rt_namespace__ = {"std", "io", "nncv"};

//===----------------------------------------------------------------------===//
// The Organization of Aten Symbol Table:
//
// stack<AtenSymbolTableG> -> AtenSymbolRef -> AtenSymbolTable(singleton)
//
// An aten symbol table correspond to a program which composed by multi packages
// An aten symbol ref correspond to a single package
// An aten symbol tableG correspond to a block in package.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Aten Symbol Payload and state
//===----------------------------------------------------------------------===//
enum class AtenSymbolTableState { kGlobal = 0, kInner = 1 };

enum class AtenFunctionType { kGeneral = 0, kImpl = 1 };

struct AtenFunctionSymbolPayload {
  // basic type check
  mlir::Type retType;
  mlir::TypeRange argumentsType;

  AtenFunctionType funcType;  ///< this function is belong to impl type or in general place.
  // visibility
  bool isPublic;
};

struct AtenStructSymbolPayload {
  // basic type check
  std::vector<std::tuple<std::string, mlir::Type, bool>>
      argumentsLists;  ///> name, type, visibility

  inline bool hasArgument(const std::string& name) {
    for (auto& item : argumentsLists) {
      if (std::get<0>(item) == name) return true;
    }
    return false;
  }

  std::optional<std::tuple<mlir::Type, bool, size_t>> getVarTypeAndPositionInStruct(
      const std::string& varName);

  std::optional<std::tuple<bool, size_t>> getVisibilityAndPositionInStruct(
      const std::string& varName);
};

//===----------------------------------------------------------------------===//
// Aten Symbol Module Name Attribute
//===----------------------------------------------------------------------===//
struct AtenModuleNameAttr {
  AtenModuleNameAttr(const std::string& name) : name(name) {}
  std::string name;
};

template<typename _Ty>
class RandomAccessSymbolStack {
 public:
  inline void push(_Ty d) {
    _data.push_back(d);
    _data.shrink_to_fit();
  }

  inline void pop() {
    if (_data.size() == 0) return;
    _data.erase(_data.end() - 1);
    _data.shrink_to_fit();
  }

  inline _Ty top() { return _data[_data.size() - 1]; }

  inline _Ty randomAccess(size_t a) {
    if (a > _data.size()) {
      // TODO emit error
      return _data[0];
    } else {
      return _data[a];
    }
  }

  inline size_t size() { return _data.size(); }

 private:
  std::vector<_Ty> _data;
};

class AtenSymbolTableG {
 public:
  inline AtenSymbolTableG(AtenSymbolTableState level = AtenSymbolTableState::kGlobal)
      : stateLevel(level) {}

  ///< Actually, this function should not be used. You should use mlir's SymbolTable instead.
  inline std::optional<AtenFunctionSymbolPayload> getFunctionSymbol(const std::string& funcName) {
    switch (stateLevel) {
      case AtenSymbolTableState::kGlobal: {
        auto item = funcSymbolTable.find(funcName);
        if (item == funcSymbolTable.end()) {
          // FIXME error
        } else {
          return item->second;
        }
        break;
      }
      case AtenSymbolTableState::kInner: {
        // FIXME emit error
        break;
      }
    }
    return std::nullopt;
  }

  inline std::optional<AtenStructSymbolPayload> getStructSymbol(const std::string& structName) {
    switch (stateLevel) {
      case AtenSymbolTableState::kGlobal: {
        auto item = structSymbolTable.find(structName);
        if (item == structSymbolTable.end()) {
          // emit error
        } else {
          return item->second;
        }
        break;
      }
      case AtenSymbolTableState::kInner: {
        // FIXME emit error
        break;
      }
    }
    return std::nullopt;
  }

  std::optional<mlir::Value> getVarSymbol(const std::string& varSymbol) {
    auto item = varSymbolTable.find(varSymbol);
    if (item == varSymbolTable.end()) {
      // FIXME emit error
      return std::nullopt;
    } else {
      return item->second;
    }
  }

  inline bool registerFuncSymbol(const std::string& funcName, AtenFunctionSymbolPayload& payload) {
    if (stateLevel == AtenSymbolTableState::kInner) return false;
    if (funcSymbolTable.find(funcName) == funcSymbolTable.end()) return false;
    funcSymbolTable[funcName] = payload;
    return true;
  }

  inline bool registerStructSymbol(const std::string& structName,
                                   AtenStructSymbolPayload& payload) {
    if (stateLevel == AtenSymbolTableState::kInner) return false;
    if (structSymbolTable.find(structName) == structSymbolTable.end()) return false;
    structSymbolTable[structName] = payload;
    return true;
  }

  inline bool registerVarSymbol(const std::string& varName, mlir::Value value) {
    if (varSymbolTable.find(varName) == varSymbolTable.end()) return false;
    varSymbolTable[varName] = value;
    return true;
  }

 private:
  AtenSymbolTableState stateLevel;
  std::unordered_map<std::string, mlir::Value> varSymbolTable;
  std::unordered_map<std::string, AtenStructSymbolPayload> structSymbolTable;
  std::unordered_map<std::string, AtenFunctionSymbolPayload> funcSymbolTable;
};

class AtenSymbolRef {
 public:
  AtenSymbolRef(const std::string& name);
  ~AtenSymbolRef();

  inline bool funcVerify(const std::string& funcName, const mlir::Type& retType,
                         const mlir::TypeRange& argumentsType) {
    // step 1. access the top level symbol table.
    auto symbolTable = m_stack.randomAccess(0);
    // step2. search func in this table.
    auto funcSymbol = symbolTable->getFunctionSymbol(funcName);
    if (!funcSymbol.has_value()) return false;
    // step 3. check ok.
    auto value = funcSymbol.value();
    if (value.retType == retType && value.argumentsType == argumentsType) return true;
    return false;
  }

  inline bool structVerify(const std::string& structName, const std::string& argumentName) {
    // same as what funcVerify do.
    auto symbolTable = m_stack.randomAccess(0);
    auto structSymbol = symbolTable->getStructSymbol(structName);
    if (!structSymbol.has_value()) return false;
    return structSymbol.value().hasArgument(argumentName);
  }

  // This function will not be used most of the time. I think people just need to verify a function
  AtenFunctionSymbolPayload getFuncSymbol(
      const std::string& funcName);  ///> use `funcVerify` first.
  // The normally usage of this function is:
  // if (structVerify(StructName, argumentName))
  //    AtenSymbolRef.getStructSymbol(StructName).getVarTypeAndPositionInStruct(varName)
  AtenStructSymbolPayload getStructSymbol(
      const std::string& structName);  ///> use `structVerify` first

  bool registerFuncSymbol(const std::string& funcName, AtenFunctionSymbolPayload& payload);
  bool registerStructSymbol(const std::string& structName, AtenStructSymbolPayload& payload);

  std::optional<mlir::Value> getVarValueSymbol(const std::string& varName);
  bool registerVarSymbol(const std::string& varName, mlir::Value value);

  void createVarSymbolTableOnTop();
  void deleteVarSymbolTableOnTop();

  bool writeCache(const std::string& path);  ///< using database
  bool readCache(const std::string& path);   ///< using database

 private:
  std::string m_name;
  RandomAccessSymbolStack<AtenSymbolTableG*> m_stack;
};

class AtenSymbolTable {
 public:
  AtenSymbolTable() = default;
  ~AtenSymbolTable();
  AtenSymbolTable(const AtenSymbolTable&) = delete;
  AtenSymbolTable& operator=(const AtenSymbolTable&) = delete;

  static AtenSymbolTable& getInstance() {
    static AtenSymbolTable instance;
    return instance;
  }

  inline AtenSymbolRef* getSymbolRefOfModule(const AtenModuleNameAttr& attr) {
    auto it = m_SymbolRefs.find(attr.name);
    if (it == m_SymbolRefs.end()) {
      // FIXME emit a error
      return nullptr;
    }
    return it->second;
  }

  inline AtenSymbolRef* createSymbolRefOfModule(const AtenModuleNameAttr& attr) {
    auto it = new AtenSymbolRef(attr.name);
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
      // FIXME emit error
      return;
    }
  }

  inline AtenSymbolRef* operator[](const AtenModuleNameAttr& attr) {
    return getSymbolRefOfModule(attr);
  }

  inline mlir::ModuleOp* getMLIRModule(const AtenModuleNameAttr& attr) {
    auto it = m_MLIRModule.find(attr.name);
    if (it == m_MLIRModule.end()) {
      // FIXME emit a error
      return nullptr;
    }
    return it->second;
  }

  inline void registerMLIRModule(const AtenModuleNameAttr& attr, mlir::ModuleOp* mo) {
    m_MLIRModule[attr.name] = mo;
  }

 private:
  std::unordered_map<std::string, AtenSymbolRef*> m_SymbolRefs;
  std::unordered_map<std::string, mlir::ModuleOp*> m_MLIRModule;
};

}  // namespace utils
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_UTILS_SYMBOL_REF_HPP