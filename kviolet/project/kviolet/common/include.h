#ifndef __KVIOLET__COMMON__INCLUDE__H__
#define __KVIOLET__COMMON__INCLUDE__H__

/// c
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <cstdint>
#include <cassert>
#include <fcntl.h>

/// c++
#include <set>
#include <map>
#include <list>
#include <array>
#include <queue>
#include <stack>
#include <mutex>
#include <regex>
#include <chrono>
#include <atomic>
#include <vector>
#include <string>
#include <memory>
#include <future>
#include <thread>
#include <random>
#include <iomanip>
#include <utility>
#include <numeric>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <functional>
#include <type_traits>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include <condition_variable>

#if __cplusplus >= 201703 // c++17

#include <filesystem>

#endif

///linux

#include <pwd.h>
#include <dlfcn.h>
#include <netdb.h>
#include <dirent.h>
#include <cxxabi.h>
#include <unistd.h>
#include <syslog.h>
#include <execinfo.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/resource.h>

#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/if_ether.h>

#include <sys/timerfd.h>
#include <sys/eventfd.h>
#include <sys/signalfd.h>


#endif ///__KVIOLET__COMMON__INCLUDE__H__