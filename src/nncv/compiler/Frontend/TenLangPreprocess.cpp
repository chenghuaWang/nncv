#include "nncv/compiler/Frontend/TenLangPreprocess.hpp"
#include "nncv/compiler/Utils/CliFormatOutput.hpp"

namespace nncv {
namespace compiler {
namespace frontend {

AutoTenPreprocessor::AutoTenPreprocessor() {
  ///! Init compiler flags;
  m_CompilerFlags.EnableStd = true;
  m_CompilerFlags.EnableNN = false;
  m_CompilerFlags.EnableIo = false;
}

}  // namespace frontend
}  // namespace compiler
}  // namespace nncv