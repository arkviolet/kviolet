#ifndef __KVIOLET__COMMON__DEFINE__H__
#define __KVIOLET__COMMON__DEFINE__H__

#include "include.h"


/// thread sleep time
#define KVIOLET_THIS_THREAD_SLEEP_S std::this_thread::sleep_for(std::chrono::hours(n))
#define KVIOLET_THIS_THREAD_SLEEP_MS std::this_thread::sleep_for(std::chrono::milliseconds(n))
#define KVIOLET_THIS_THREAD_SLEEP_US std::this_thread::sleep_for(std::chrono::microseconds(n))


///current timestamp
/**
 *  system_clock, 起点：1970-01-01 00:00:00 UTC,刻度 1个 tick
 *  steady_clock, 起点：系统启动时间,steady_clock的作用是为了得到不随系统时间修改而变化的时间间隔
 * */
#define KVIOLET_CURRENT_OS_TIME_MS  (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock().now().time_since_epoch()).count())
#define KVIOLET_CURRENT_OS_TIME_NS  (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock().now().time_since_epoch()).count())
#define KVIOLET_CURRENT_OS_TIME_US  (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock().now().time_since_epoch()).count())

#define KVIOLET_CURRENT_UTC_TIME_MS (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
#define KVIOLET_CURRENT_UTC_TIME_NS (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
#define KVIOLET_CURRENT_UTC_TIME_US (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count())


/// π
#define KVIOLET_PI (3.1415926535898f)


/// bit
#define KVIOLET_BYTE                                (1)
#define KVIOLET_KB                  (KVIOLET_BYTE * 1024)
#define KVIOLET_MB                  (KVIOLET_KB * 1024)
#define KVIOLET_GB                  (KVIOLET_MB * 1024)


///EOF
#define KVIOLET_EOF                 "\n"


///max min,
/**
 * 三元运算符 效率高于if-else：
 *      if - else: 仅仅只有一条默认流水,跳转失败后需重新建立cpu流水
 *      三元运算符： 存在条件判断两条默认流水,根据实际情况选择流水,不需要重建流水
 * */
#define KVIOLET_COMPARE_MAX(a, b) (a) > (b) ? (a) : (b)
#define KVIOLET_COMPARE_MIN(a, b) (a) > (b) ? (b) : (a)


#endif ///__KVIOLET__COMMON__DEFINE__H__