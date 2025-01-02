#ifndef __KVIOLET__UTILITIES__TIMESTAMP__H__
#define __KVIOLET__UTILITIES__TIMESTAMP__H__

#include <time.h>

#include <chrono>

namespace kviolet {
namespace utilities {
class Timestamp {
 public:
  /// utc s
  static std::time_t Seconds();

  /// utc ms
  static std::time_t Milliseconds();

  /// utc us
  static std::time_t Microseconds();

  /// utc ns
  static std::time_t Nanoseconds();

  /// utc double us
  static double MicrosecondsDouble();

  /// cpu monotonic s
  static uint64_t MonotonicSeconds();

  /// cpu monotonic ms
  static uint64_t MonotonicMilliseconds();

  /// cpu monotonic us
  static uint64_t MonotonicMicroseconds();

  /// cpu monotonic ns
  static uint64_t MonotonicNanoseconds();

  /// cpu monotonic double us
  static double MonotonicMicrosecondsDouble();
};

}  // namespace utilities
}  // namespace kviolet

#endif  // __KVIOLET__UTILITIES__TIME__H__
