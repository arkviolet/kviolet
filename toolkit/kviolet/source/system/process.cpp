#include "process.h"

#include <pthread.h>
#include <sched.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <wait.h>

#include <iostream>

namespace kviolet {
namespace system {

uint64_t Process::ThreadID() { return static_cast<uint64_t>(::syscall(SYS_gettid)); }

std::string Process::ThreadName() {
  char buffer[16] = {};
#ifdef HAVE_PTHREAD_SETNAME_NP
  pthread_getname_np(pthread_self(), buffer);
#else
  prctl(PR_GET_NAME, buffer);
#endif
  return std::string(buffer);
}

void Process::ThreadName(const std::string& name) {
  /// name.size max 16
#ifdef HAVE_PTHREAD_SETNAME_NP
  pthread_setname_np(pthread_self(), name.c_str());
#else
  prctl(PR_SET_NAME, name.c_str());
#endif
}

int Process::MaxThreadPriority() { return sched_get_priority_max(SCHED_FIFO); }

bool Process::Priority(int priority) {
  /// #define SCHED_OTHER   系统自动调度
  /// #define SCHED_FIFO    FIFO,较高的优先级thread并始终保持对CPU的占用
  /// #define SCHED_RR      时间片轮转策略
  struct sched_param params;
  params.sched_priority = priority;
  return !pthread_setschedparam(pthread_self(), SCHED_FIFO, &params);
}

pid_t Process::Fork(const char** argv) {
  auto pid = fork();
  if (pid < 0) {
    return -1;
  } else if (0 == pid) {
    auto ret = execvp(argv[0], (char* const*)argv);
    std::cerr << "fork process error:" << ret << std::endl;
    exit(127);
  }

  return pid;
}

int Process::WaitPid(pid_t pid, bool is_wait) {
  int status = 0;

  auto ret = waitpid(pid, &status, is_wait ? WUNTRACED : WNOHANG);

  if (-1 == ret || (!is_wait && 0 == ret)) {
    return ret;
  }

  return WIFEXITED(status) ? 2 : 1;
}

}  // namespace system
}  // namespace kviolet
