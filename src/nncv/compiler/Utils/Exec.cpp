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
    std::vector<const char*> c_args;
    c_args.push_back(m_ExecFilePath.c_str());
    for (const auto& arg : m_Args) { c_args.push_back(arg.c_str()); }
    c_args.push_back(NULL);
    if (m_hideOutput) {
      int fd = open("/dev/null", O_WRONLY);
      dup2(fd, 1);
      dup2(fd, 2);
    }
    auto ret = execv(m_ExecFilePath.c_str(), const_cast<char* const*>(c_args.data()));
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