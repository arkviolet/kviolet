#ifndef __KVIOLET__UTILITIES__TIME__H__
#define __KVIOLET__UTILITIES__TIME__H__

#include "../common/common.h"

namespace kviolet {
namespace utilities {

using SystemClockType = std::chrono::system_clock;
using SystemClockDuration = std::chrono::system_clock::duration;
using SystemClockTimePoint = std::chrono::system_clock::time_point;

using SteadyClockType = std::chrono::steady_clock;
using SteadyClockDuration = std::chrono::steady_clock::duration;
using SteadyClockTimePoint = std::chrono::steady_clock::time_point;

class API_EXPORT Time {
 public:
  /// 是否是同一年
  static bool IsSameYear(std::time_t sSeconds, std::time_t dSeconds);

  /// 是否是同一月
  static bool IsSameMonth(std::time_t sSeconds, std::time_t dSeconds);

  /// 是否是同一天
  static bool IsSameDay(std::time_t sSeconds, std::time_t dSeconds);

  /// 是否是同一小时
  static bool IsSameHour(std::time_t sSeconds, std::time_t dSeconds);

  /// 是否是同一分钟
  static bool IsSameMinute(std::time_t sSeconds, std::time_t dSeconds);

  /// utc时间对应的tm结构体
  static std::tm UTCTm();

  /// utc时间对应的tm结构体
  static std::tm UTCTm(std::time_t seconds);

  /// utc时间对应的tm结构
  static void UTCTm(std::time_t seconds, std::tm& tm);

  /// 本地时间对应的tm结构体
  static std::tm LocalTm();

  /// 本地时间对应的tm结构体
  static std::tm LocalTm(std::time_t seconds);

  /// 本地时间对应的tm结构体
  static void LocalTm(std::time_t seconds, std::tm& tm);

  /// 转换时间戳
  template <typename CastTypeT>
  static CastTypeT Cast() {
    return Cast<CastTypeT>(TimePoint());
  }

  /// 换时间戳
  template <typename CastTypeT>
  static CastTypeT Cast(const SystemClockTimePoint& timesPoint) {
    return Cast<CastTypeT>(timesPoint.time_since_epoch());
  }

  /// 转换时间戳
  template <typename CastTypeT>
  static CastTypeT Cast(const SystemClockDuration& duration) {
    return std::chrono::duration_cast<std::chrono::duration<CastTypeT>>(duration).count();
  }

  /// 小时时间戳
  static std::time_t Hours();

  static std::time_t Hours(const SystemClockTimePoint& timesPoint);

  static std::time_t Hours(const SystemClockDuration& duration);

  /// 分钟时间戳
  static std::time_t Minutes();

  static std::time_t Minutes(const SystemClockTimePoint& timesPoint);

  static std::time_t Minutes(const SystemClockDuration& duration);

  /// 秒数时间戳
  static std::time_t Seconds();

  static std::time_t Seconds(const SystemClockTimePoint& timesPoint);

  static std::time_t Seconds(const SystemClockDuration& duration);

  /// 毫秒时间戳
  static std::time_t Milliseconds();

  static std::time_t Milliseconds(const SystemClockTimePoint& timesPoint);

  static std::time_t Milliseconds(const SystemClockDuration& duration);

  /// 微秒时间戳
  static std::time_t Microseconds();

  static std::time_t Microseconds(const SystemClockTimePoint& timesPoint);

  static std::time_t Microseconds(const SystemClockDuration& duration);

  /// 纳秒时间戳
  static std::time_t Nanoseconds();

  static std::time_t Nanoseconds(const SystemClockTimePoint& timesPoint);

  static std::time_t Nanoseconds(const SystemClockDuration& duration);

  /// 时区
  static std::time_t TimeZone();

  /// 下一天指定时间的时间戳
  static std::time_t NextDayTime(int32_t hour = 0, int32_t minutes = 0, int32_t seconds = 0);

  /// 当天指定时间的时间戳
  static std::time_t CurrentDayTime(int32_t hour = 0, int32_t minutes = 0, int32_t seconds = 0);

  /// tm转换成秒数时间戳
  static std::time_t FromTm(std::tm& date);

  /// 日期字符串转换成秒数时间戳
  static std::time_t FromTimeString(const char* value, const char* format = "%4d-%02d-%02d %02d:%02d:%02d");

  /// 日期字符串转换成秒数时间戳
  static std::time_t FromTimeString(const std::string& value, const char* format = "%4d-%02d-%02d %02d:%02d:%02d");

  /// 格式化日期字符串
  static std::string FormatTimeString(std::time_t seconds, const char* format = "%4d-%02d-%02d %02d:%02d:%02d");

  /// 格式化日期字符串
  static std::string FormatTimeString(std::time_t seconds, std::time_t timeZone,
                                      const char* format = "%4d-%02d-%02d %02d:%02d:%02d");

  /// 格式化当前UTC日期字符串
  static std::string CurrentUTCTimeString(const char* format = "%4d-%02d-%02d %02d:%02d:%02d");

  /// 格式化当前本地日期字符串
  static std::string CurrentLocalTimeString(const char* format = "%4d-%02d-%02d %02d:%02d:%02d");

  /// 时间点
  static SystemClockTimePoint TimePoint();

  static SystemClockTimePoint TimePoint(std::time_t time);

  static SystemClockTimePoint TimePoint(const struct timeval& time);

  static SystemClockTimePoint TimePoint(const struct timespec& time);

  /// 时间段
  static SystemClockDuration TimeDuration();

  static SystemClockDuration TimeDuration(std::time_t time);

  static SystemClockDuration TimeDuration(const struct timeval& time);

  static SystemClockDuration TimeDuration(const struct timespec& time);
};

}  // namespace utilities
}  // namespace kviolet

#endif  // __KVIOLET__UTILITIES__TIME__H__
