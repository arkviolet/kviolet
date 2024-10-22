#ifndef __KVIOLET__SYSTEM__PROCESS__H__
#define __KVIOLET__SYSTEM__PROCESS__H__

#include <string>

namespace kviolet {
namespace system {

class Process {
 public:
  static uint64_t ThreadID();

  static std::string ThreadName();

  static void ThreadName(const std::string& name);

  static bool Priority(int priority);  /// priority 1 --> 99

  static int MaxThreadPriority();

  static pid_t Fork(const char** argv);

  /**
   * -1 not exists
   * 0 running
   * 1 exception exit
   * 2 normally exit
   * */
  static int WaitPid(pid_t pid, bool is_wait = false);
};

}  // namespace system
}  // namespace kviolet

#endif  // __KVIOLET__SYSTEM__PROCESS__H__
