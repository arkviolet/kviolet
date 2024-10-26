#include "math.h"

namespace kviolet {
namespace utilities {

bool Math::IsPowerOfTwo(uint32_t num) {
  return num && (!(num & (num - 1)));
}

uint32_t Math::GetRoundupPowerOfTwo(uint32_t num) {
  return (num == 0) ? 1 : (0x01 << (sizeof(num) * CHAR_BIT - __builtin_clz(num) + 1));
#if 0
        uint32_t i = 0;

        while ((1 << i++) < num)
        {
        }
        return 1 << --i;
#endif
}

uint32_t Math::GetRoundDownPowerOfTwo(uint32_t num) {
  return GetRoundupPowerOfTwo(num) >> 1;
}

bool Math::IsOddNumber(int32_t num) {
  return !!(num & 1);
}

bool Math::IsEventNumber(int32_t num) {
  return !(num & 1);
}

}  // namespace utilities
}  // namespace kviolet
