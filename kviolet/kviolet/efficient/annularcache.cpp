#include "annularcache.h"
#include "../utilities/math.h"

namespace kviolet {
namespace efficent {

using namespace kviolet::utilities;

AnnularCache::AnnularCache(uint32_t size) {
  /**
   * _size = 2^n 求余操作转换为位操作
   * _r % _size = _r & (_size - 1)
   * _w % _size = _w & (_size- 1)
   * */
  _size = Math::GetRoundupPowerOfTwo(size);

  _cache = new uint8_t[_size];
}

AnnularCache::~AnnularCache() {
  delete[] _cache;

  _cache = nullptr;

  _size = _w = _r = 0;
}

uint32_t AnnularCache::Push(uint8_t* data, uint32_t len) {
  /**
   * _size - (_w - _r)
   *
   *      _w,_r,无符号32位整形数据,达到最大值后产生溢出重新从零开始增长
   *      二进制变换：00000... -> 11111... -> 00000 -> 11111...
   *
   *      _w >= _r: 可写入空间长度: _size - (_w - r)
   *                              [0..._r(读index)..............._w(写index).....]_size
   *
   *      _w <  _r: 可写入空间长度：          --->---> _w _r同时向右移动使的_r产生移除重置为0,
   *                                        则_size - (_w - r)依然成立
   *                              [0..._w(写index)..............._r(读index).....]_size
   * */
  len = KVIOLET_COMPARE_MIN(len, _size - (_w - _r));  /// 获取写入数据长度

  /**
   * 求前半部分与后半部分
   *
   * [........._r......................_w...........]_size
   *  xxxxxxxxx:输入后半部                    xxxxxxxxxxx:输入数据前半部分
   * */
  auto l = KVIOLET_COMPARE_MIN(len, _size - (_w & (_size - 1)));

  memcpy(_cache + (_w & (_size - 1)), data, l);

  memcpy(_cache, data + l, len - l);

  _w += len;

  return len;
}

uint32_t AnnularCache::Pop(uint8_t* data, uint32_t len) {
  len = KVIOLET_COMPARE_MIN(len, _w - _r);

  auto l = KVIOLET_COMPARE_MIN(len, _size - (_r & (_size - 1)));

  memcpy(data, _cache + (_r & (_size - 1)), l);

  memcpy(data + l, _cache, len - l);

  _r += len;

  return len;
}

}  // namespace efficent
}  // namespace kviolet
