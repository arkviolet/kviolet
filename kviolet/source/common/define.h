#ifndef __KVIOLET__COMMON__DEFINE__H__
#define __KVIOLET__COMMON__DEFINE__H__

#include "include.h"

/// thread sleep time
#define KVIOLET_THIS_THREAD_SLEEP_S(n) std::this_thread::sleep_for(std::chrono::hours(n))
#define KVIOLET_THIS_THREAD_SLEEP_MS(n) std::this_thread::sleep_for(std::chrono::milliseconds(n))
#define KVIOLET_THIS_THREAD_SLEEP_US(n) std::this_thread::sleep_for(std::chrono::microseconds(n))

#define KVIOLET_CURRENT_OS_TIME_MS \
  (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock().now().time_since_epoch()).count())
#define KVIOLET_CURRENT_OS_TIME_NS \
  (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock().now().time_since_epoch()).count())
#define KVIOLET_CURRENT_OS_TIME_US \
  (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock().now().time_since_epoch()).count())

#define KVIOLET_CURRENT_UTC_TIME_MS \
  (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
#define KVIOLET_CURRENT_UTC_TIME_NS \
  (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
#define KVIOLET_CURRENT_UTC_TIME_US \
  (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count())

/// π
#define KVIOLET_PI (3.1415926535898f)

/// bit
#define KVIOLET_BYTE (1)
#define KVIOLET_KB (KVIOLET_BYTE * 1024)
#define KVIOLET_MB (KVIOLET_KB * 1024)
#define KVIOLET_GB (KVIOLET_MB * 1024)

/// max min,
#define KVIOLET_COMPARE_MAX(a, b) (a) > (b) ? (a) : (b)
#define KVIOLET_COMPARE_MIN(a, b) (a) > (b) ? (b) : (a)

/// sizeof
#define KVIOLET_OFFSET_VALUE(value) ((char*)(&value + 1) - (char*)(&value))
#define KVIOLET_OFFSET_VARIABLE(val) ((char*)((val*)0 + 1) - (char*)((val*)0))

/**
 * 求结构体成员变量偏移量
 * type:    结构体类型
 * member： 对应成员变量名
 * return:  偏移量
 * */
#define KVIOLET_OFFSET_OF(type, member) ((size_t)(&((type*)0)->member))

/**
 * 根据结构体成员变量求结构体变量首地址
 * ptr：     成员变量指针
 * type:    结构体类型
 * member： 对应成员变量名
 * return:  结构体指针
 * */
#define KVIOLET_CONTAINER_OF(ptr, type, member) ((type*)((char*)ptr - KVIOLET_OFFSET_OF(type, member)));

/**
 * assert throw std::runtime_error
 * */
#define KVIOLET_ASSERT_CPP(value) \
  { throw std::runtime_error(value); };

/**
 * assert false throw std::runtime_error
 * */
#define KVIOLET_ASSERT_CPP_COND(condition, value) \
  {                                               \
    if (!(condition)) {                           \
      throw std::runtime_error(value);            \
    }                                             \
  };

#endif  ///__KVIOLET__COMMON__DEFINE__H__
