#ifndef __KVIOLET__DEBUG__H__
#define __KVIOLET__DEBUG__H__

#include "../common/support.h"
namespace kviolet {
namespace debug {
class API_EXPORT Debug {
 public:
  static void StackTrace();
};
}  // namespace debug
}  // namespace kviolet

#endif  // __KVIOLET__DEBUG__H__