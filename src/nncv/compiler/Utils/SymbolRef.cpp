#include "nncv/compiler/Utils/SymbolRef.hpp"

namespace nncv {
namespace compiler {
namespace utils {
AtenSymbolRef::AtenSymbolRef() : isDelayVerifyDone(false) {
  instance = this;
  registerRuntime();
}

AtenSymbolRef::~AtenSymbolRef() {
  if (!isDelayVerifyDone) {
    // do somthing.
  }
  clearAll();
}

void AtenSymbolRef::clearAll() {}

void AtenSymbolRef::registerRuntime() {}

}  // namespace utils
}  // namespace compiler
}  // namespace nncv