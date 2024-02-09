#pragma once

#ifndef NNCV_COMPILER_UTILS_EXEC_HPP
#define NNCV_COMPILER_UTILS_EXEC_HPP

#include <string>
#include <vector>

namespace nncv {
namespace compiler {
namespace utils {

class ExecObject {
 public:
  ExecObject(const std::string& execFilePath) : m_ExecFilePath(execFilePath) {}
  inline void pushArgs(const std::string arg) { m_Args.push_back(arg); }

  int32_t runParallel();
  int32_t runSyncWait();
  inline int32_t getRet() { return m_Ret; }
  inline bool isSuccess() { return m_Ret == 0; }
  inline void setHideOutput(bool flag) { m_hideOutput = flag; }

 private:
  std::string m_ExecFilePath;
  std::vector<std::string> m_Args;
  int32_t m_Ret;
  bool m_hideOutput = false;
};

}  // namespace utils
}  // namespace compiler
}  // namespace nncv

#endif  //! NNCV_COMPILER_UTILS_EXEC_HPP