#include "nncv/compiler/Utils/SymbolRef.hpp"

namespace nncv {
namespace compiler {
namespace utils {

//===----------------------------------------------------------------------===//
// AtenStructSymbolPaylod Implement
//===----------------------------------------------------------------------===//
std::optional<std::tuple<mlir::Type, bool, size_t>>
AtenStructSymbolPayload::getVarTypeAndPositionInStruct(const std::string& varName) {
  size_t cnt = 0;
  for (auto& item : argumentsLists) {
    if (std::get<0>(item) == varName) {
      return std::tuple<mlir::Type, bool, size_t>(std::get<1>(item), std::get<2>(item), cnt);
    }
    cnt++;
  }
  return std::nullopt;
}

std::optional<std::tuple<bool, size_t>> AtenStructSymbolPayload::getVisibilityAndPositionInStruct(
    const std::string& varName) {
  size_t cnt = 0;
  for (auto& item : argumentsLists) {
    if (std::get<0>(item) == varName) { return std::tuple<bool, size_t>(std::get<2>(item), cnt); }
    cnt++;
  }
  return std::nullopt;
}

//===----------------------------------------------------------------------===//
// AtenSymbolRef Implement
//===----------------------------------------------------------------------===//
AtenSymbolRef::AtenSymbolRef(const std::string& name) : m_name(name) {
  m_stack.push(new AtenSymbolTableG(AtenSymbolTableState::kGlobal));
}

AtenSymbolRef::~AtenSymbolRef() {
  while (m_stack.size()) {
    auto ptr = m_stack.top();
    m_stack.pop();
    delete ptr;
  }
}

AtenFunctionSymbolPayload AtenSymbolRef::getFuncSymbol(const std::string& funcName) {
  auto symbolTable = m_stack.randomAccess(0);
  return symbolTable->getFunctionSymbol(funcName).value();
}

AtenStructSymbolPayload AtenSymbolRef::getStructSymbol(const std::string& structName) {
  auto symbolTable = m_stack.randomAccess(0);
  return symbolTable->getStructSymbol(structName).value();
}

bool AtenSymbolRef::registerFuncSymbol(const std::string& funcName,
                                       AtenFunctionSymbolPayload& payload) {
  return m_stack.randomAccess(0)->registerFuncSymbol(funcName, payload);
}

bool AtenSymbolRef::registerStructSymbol(const std::string& structName,
                                         AtenStructSymbolPayload& payload) {
  return m_stack.randomAccess(0)->registerStructSymbol(structName, payload);
}

std::optional<mlir::Value> AtenSymbolRef::getVarValueSymbol(const std::string& varName) {
  size_t depth = m_stack.size();
  while (depth) {
    auto item = m_stack.randomAccess(depth - 1)->getVarSymbol(varName);
    if (item.has_value()) return item;
    depth--;
  }
  return std::nullopt;
}

std::optional<std::string> AtenSymbolRef::getVarValueName(mlir::Value value) {
  size_t depth = m_stack.size();
  while (depth) {
    auto item = m_stack.randomAccess(depth - 1)->getVarValueName(value);
    if (item.has_value()) { return item; }
    depth--;
  }
  return std::nullopt;
}

VarSymbolKind AtenSymbolRef::getVarValueSymbolKind(const std::string& varName) {
  size_t depth = m_stack.size();
  while (depth) {
    auto item = m_stack.randomAccess(depth - 1)->getVarSymbolKind(varName);
    if (item.has_value()) { return item.value(); }
    depth--;
  }
  return VarSymbolKind::kNone;
}

bool AtenSymbolRef::isInTheTopSymbolTable(std::string& vn) {
  auto item = m_stack.randomAccess(m_stack.size() - 1)->getVarSymbol(vn);
  if (item.has_value()) { return true; }
  return false;
}

bool AtenSymbolRef::updateVarSymbol(const std::string& varName, mlir::Value value) {
  size_t depth = m_stack.size();
  while (depth) {
    auto item = m_stack.randomAccess(depth - 1)->getVarSymbol(varName);
    if (item.has_value()) {
      m_stack.randomAccess(depth - 1)->updateVatSymbol(varName, value);
      return true;
    }
    depth--;
  }
  return false;
}

bool AtenSymbolRef::registerVarSymbol(const std::string& varName, mlir::Value value,
                                      VarSymbolKind kind) {
  return m_stack.top()->registerVarSymbol(varName, value, kind);
}

void AtenSymbolRef::createVarSymbolTableOnTop() {
  auto c = new AtenSymbolTableG(AtenSymbolTableState::kInner);
  m_stack.push(c);
}

void AtenSymbolRef::deleteVarSymbolTableOnTop() {
  auto ptr = m_stack.top();
  m_stack.pop();
  delete ptr;
}

bool AtenSymbolRef::writeCache(const std::string& path) { return true; }

bool AtenSymbolRef::readCache(const std::string& path) { return true; }

//===----------------------------------------------------------------------===//
// AtenSymbolTable Implement
//===----------------------------------------------------------------------===//
AtenSymbolTable::~AtenSymbolTable() {
  for (auto& item : m_SymbolRefs) { delete item.second; }
}

}  // namespace utils
}  // namespace compiler
}  // namespace nncv