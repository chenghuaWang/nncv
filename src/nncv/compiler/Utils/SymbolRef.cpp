#include "nncv/compiler/Utils/SymbolRef.hpp"

namespace nncv {
namespace compiler {
namespace utils {
AtenSymbolRef::AtenSymbolRef() : m_parent(nullptr) {}

AtenSymbolRef::~AtenSymbolRef() { clearAll(); }

void AtenSymbolRef::clearAll() {}

//===----------------------------------------------------------------------===//
// AtenSymbolTable Implement
//===----------------------------------------------------------------------===//
AtenSymbolTable::AtenSymbolTable() { instance = this; }

AtenSymbolTable::~AtenSymbolTable() {
  for (auto& item : m_SymbolRefs) { delete item.second; }
}

}  // namespace utils
}  // namespace compiler
}  // namespace nncv