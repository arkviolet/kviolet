#include "time.h"

namespace kviolet {
namespace utilities {

bool Time::IsSameYear(std::time_t sSeconds, std::time_t dSeconds) {
  std::tm src = LocalTm(sSeconds);
  std::tm dst = LocalTm(dSeconds);

  return (src.tm_year == dst.tm_year);
}

bool Time::IsSameMonth(std::time_t sSeconds, std::time_t dSeconds) {
  std::tm src = LocalTm(sSeconds);
  std::tm dst = LocalTm(dSeconds);

  return (src.tm_year == dst.tm_year && src.tm_mon == dst.tm_mon);
}

bool Time::IsSameDay(std::time_t sSeconds, std::time_t dSeconds) {
  std::tm src = LocalTm(sSeconds);
  std::tm dst = LocalTm(dSeconds);

  return (src.tm_year == dst.tm_year && src.tm_mon == dst.tm_mon && src.tm_mday == dst.tm_mday);
}

bool Time::IsSameHour(std::time_t sSeconds, std::time_t dSeconds) {
  std::tm src = LocalTm(sSeconds);
  std::tm dst = LocalTm(dSeconds);

  return (src.tm_year == dst.tm_year && src.tm_mon == dst.tm_mon && src.tm_mday == dst.tm_mday && src.tm_hour == dst.tm_hour);
}

bool Time::IsSameMinute(std::time_t sSeconds, std::time_t dSeconds) {
  std::tm src = LocalTm(sSeconds);
  std::tm dst = LocalTm(dSeconds);

  return (src.tm_year == dst.tm_year && src.tm_mon == dst.tm_mon && src.tm_mday == dst.tm_mday && src.tm_hour == dst.tm_hour && src.tm_min == dst.tm_min);
}

std::tm Time::UTCTm() {
  return UTCTm(Seconds());
}

std::tm Time::UTCTm(std::time_t seconds) {
  std::tm tm = {};

  UTCTm(seconds, tm);

  return tm;
}

void Time::UTCTm(std::time_t seconds, std::tm& tm) {
  gmtime_r(&seconds, &tm);
}

std::tm Time::LocalTm() {
  return LocalTm(Seconds());
}

std::tm Time::LocalTm(std::time_t seconds) {
  std::tm tm = {};

  LocalTm(seconds, tm);

  return tm;
}

void Time::LocalTm(std::time_t seconds, struct tm& tm) {
  localtime_r(&seconds, &tm);
}

std::time_t Time::Hours() {
  return Hours(TimePoint());
}

std::time_t Time::Hours(const SystemClockTimePoint& timesPoint) {
  return Hours(timesPoint.time_since_epoch());
}

std::time_t Time::Hours(const SystemClockDuration& duration) {
  return std::chrono::duration_cast<std::chrono::hours>(duration).count();
}

std::time_t Time::Minutes() {
  return Minutes(TimePoint());
}

std::time_t Time::Minutes(const SystemClockTimePoint& timesPoint) {
  return Minutes(timesPoint.time_since_epoch());
}

std::time_t Time::Minutes(const SystemClockDuration& duration) {
  return std::chrono::duration_cast<std::chrono::minutes>(duration).count();
}

std::time_t Time::Seconds() {
  return Seconds(TimePoint());
}

std::time_t Time::Seconds(const SystemClockTimePoint& timesPoint) {
  return Seconds(timesPoint.time_since_epoch());
}

std::time_t Time::Seconds(const SystemClockDuration& duration) {
  return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

std::time_t Time::Milliseconds() {
  return Milliseconds(TimePoint());
}

std::time_t Time::Milliseconds(const SystemClockTimePoint& timesPoint) {
  return Milliseconds(timesPoint.time_since_epoch());
}

std::time_t Time::Milliseconds(const SystemClockDuration& duration) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

std::time_t Time::Microseconds() {
  return Microseconds(TimePoint());
}

std::time_t Time::Microseconds(const SystemClockTimePoint& timesPoint) {
  return Microseconds(timesPoint.time_since_epoch());
}

std::time_t Time::Microseconds(const SystemClockDuration& duration) {
  return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

std::time_t Time::Nanoseconds() {
  return Nanoseconds(TimePoint());
}

std::time_t Time::Nanoseconds(const SystemClockTimePoint& timesPoint) {
  return Nanoseconds(timesPoint.time_since_epoch());
}

std::time_t Time::Nanoseconds(const SystemClockDuration& duration) {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

std::time_t Time::TimeZone() {
  static std::pair<std::time_t, bool> value(0, true);

  if (value.second) {
    std::tm utc = UTCTm();
    std::tm local = LocalTm();

    value.first = (FromTm(local) - FromTm(utc)) / (60 * 60);

    value.second = false;
  }

  return value.first;
}

std::time_t Time::NextDayTime(int32_t hour, int32_t minutes, int32_t seconds) {
  if (hour < 0 || hour > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) {
    throw std::logic_error("Invalid Time");
  }

  return CurrentDayTime(hour, minutes, seconds) + (24 * 60 * 60);
}

std::time_t Time::CurrentDayTime(int32_t hour, int32_t minutes, int32_t seconds) {
  if (hour < 0 || hour > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) {
    throw std::logic_error("Invalid Time");
  }

  std::tm date = LocalTm();

  date.tm_hour = hour;
  date.tm_min = minutes;
  date.tm_sec = seconds;

  return FromTm(date);
}

std::time_t Time::FromTm(std::tm& date) {
  return std::mktime(&date);
}

std::time_t Time::FromTimeString(const char* value, const char* format) {
  assert(value && format);

  std::tm now{};

  sscanf(value, format, &now.tm_year, &now.tm_mon, &now.tm_mday, &now.tm_hour, &now.tm_min, &now.tm_sec);

  now.tm_year -= 1900;
  now.tm_mon -= 1;

  return FromTm(now);
}

std::time_t Time::FromTimeString(const std::string& value, const char* format) {
  return FromTimeString(value.c_str(), format);
}

std::string Time::FormatTimeString(std::time_t seconds, const char* format) {
  assert(format);

  return FormatTimeString(seconds, TimeZone(), format);
}

std::string Time::FormatTimeString(std::time_t seconds, std::time_t timeZone, const char* format) {
  assert(format);

  char str[128] = {0};

  std::tm now = UTCTm(seconds + timeZone * (60 * 60));

  snprintf(str, sizeof(str), format, now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);

  return str;
}

std::string Time::CurrentUTCTimeString(const char* format) {
  return FormatTimeString(Seconds(), 0, format);
}

std::string Time::CurrentLocalTimeString(const char* format) {
  return FormatTimeString(Seconds(), format);
}

SystemClockTimePoint Time::TimePoint() {
  return SystemClockType::now();
}

SystemClockTimePoint Time::TimePoint(std::time_t time) {
  return std::chrono::time_point_cast<SystemClockDuration>(std::chrono::time_point<SystemClockType, std::chrono::seconds>(std::chrono::seconds(time)));
}

SystemClockTimePoint Time::TimePoint(const struct timeval& time) {
  return std::chrono::time_point<SystemClockType, SystemClockDuration>(
      std::chrono::duration_cast<SystemClockDuration>(std::chrono::seconds(time.tv_sec) + std::chrono::microseconds(time.tv_usec)));
}

SystemClockTimePoint Time::TimePoint(const struct timespec& time) {
  return std::chrono::time_point<SystemClockType, SystemClockDuration>(
      std::chrono::duration_cast<SystemClockDuration>(std::chrono::seconds(time.tv_sec) + std::chrono::nanoseconds(time.tv_nsec)));
}

SystemClockDuration Time::TimeDuration() {
  return TimePoint().time_since_epoch();
}

SystemClockDuration Time::TimeDuration(std::time_t time) {
  return TimePoint(time).time_since_epoch();
}

SystemClockDuration Time::TimeDuration(const struct timeval& time) {
  return TimePoint(time).time_since_epoch();
}

SystemClockDuration Time::TimeDuration(const struct timespec& time) {
  return TimePoint(time).time_since_epoch();
}

}  // namespace utilities
}  // namespace kviolet
