#include "nncv/compiler/Utils/Exec.hpp"
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

namespace nncv {
namespace compiler {
namespace utils {

int32_t ExecObject::runParallel() {
  // TODO
}

int32_t ExecObject::runSyncWait() {
  pid_t pid;
  int status;
  pid = fork();
  if (pid == -1) {
    printf("[ Erro ] Can't fork process for %s\n", m_ExecFilePath.c_str());
    return -1;
  } else if (pid == 0) {
    char** args = (char**)malloc((m_Args.size() + 1) * sizeof(char*));
    for (size_t i = 0; i < m_Args.size(); ++i) { args[i] = m_Args[i].data(); }
    args[m_Args.size()] = NULL;
    execl(m_ExecFilePath.c_str(), m_ExecFilePath.c_str(), args);
    free(args);
    return m_Ret;
  } else {
    printf("[ Info ] Waiting for %s\n", m_ExecFilePath.c_str());
    wait(&status);
  }
  return 0;
}

}  // namespace utils
}  // namespace compiler
}  // namespace nncv