#ifndef __KVIOLET__COMMON__DEFINE__CPP__H__
#define __KVIOLET__COMMON__DEFINE__CPP__H__

#define KVIOLET_CLASS_API

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

#endif  ///__KVIOLET__COMMON__DEFINE__CPP__H__
