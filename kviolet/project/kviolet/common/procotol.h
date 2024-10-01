#ifndef __KVIOLET__COMMON__PROCOTOL__H__
#define __KVIOLET__COMMON__PROCOTOL__H__

#include "include.h"

/// 网络转换头
typedef struct NET_HEAD {
  uint32_t length;
  uint32_t protocol;
} NET_HEAD;

#endif  ///__KVIOLET__COMMON__PROTOCOL__H__
