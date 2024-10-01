#ifndef __KVIOLET__COMMON__INCLUDE__H__
#define __KVIOLET__COMMON__INCLUDE__H__

/// c
#include <fcntl.h>
#include <cassert>
#include <cerrno>
#include <climits>
#include <cmath>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

/// c++
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#if __cplusplus >= 201703  // c++17

#include <filesystem>

#endif

/// linux

#include <cxxabi.h>
#include <dirent.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <netdb.h>
#include <pwd.h>
#include <syslog.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <sys/epoll.h>

#include <sys/eventfd.h>
#include <sys/signalfd.h>
#include <sys/timerfd.h>

#endif  ///__KVIOLET__COMMON__INCLUDE__H__
