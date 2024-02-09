#include "nncv/compiler/Utils/Exec.hpp"
#include <fcntl.h>
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
  pid = fork();
  if (pid == -1) {
    printf("[ Erro ] Can't fork process for %s.\n", m_ExecFilePath.c_str());
    return -1;
  } else if (pid == 0) /*child process*/ {
    char** args = (char**)malloc((m_Args.size() + 2) * sizeof(char*));
    args[0] = m_ExecFilePath.data();
    for (size_t i = 0; i < m_Args.size(); ++i) { args[i + 1] = m_Args[i].data(); }
    args[m_Args.size() + 1] = NULL;

    if (m_hideOutput) {
      int fd = open("/dev/null", O_WRONLY);
      dup2(fd, 1);
      dup2(fd, 2);
    }
    auto ret = execv(m_ExecFilePath.c_str(), args);
    free(args);
    exit(ret);
  } else /*father process*/ {
    printf("[ Info ] Waiting for %s.\n", m_ExecFilePath.c_str());
    int status;
    waitpid(pid, &status, 0);
    printf("[ Info ] %s done.\n", m_ExecFilePath.c_str());
    m_Ret = status;
  }
  return 0;
}

}  // namespace utils
}  // namespace compiler
}  // namespace nncv