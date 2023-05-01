#ifndef __KVIOLET__UTILITIES__MATH__H__
#define __KVIOLET__UTILITIES__MATH__H__


/**
 *
 *  作者: hm
 *
 *  说明: 时间处理
 *
 */


#include "../common/common.h"


namespace kviolet
{
    class KVIOLET_CLASS_API Math
    {
    public:
        /**
         * 判断当前参数是否为2^n
         * */
        static bool IsPowerOfTwo(uint32_t num);

        /**
         * 向上取2^n数据,ex: input 9 return 16
         * */
        static uint32_t GetRoundupPowerOfTwo(uint32_t num);

        /**
         * 向下取2^n数据,ex: input 9 return 8
         * */
        static uint32_t GetRoundDownPowerOfTwo(uint32_t num);

        /**
         * 是否为奇数
         * */
        static bool IsOddNumber(int32_t num);

        /**
         * 是否为偶数
         * */
        static bool IsEventNumber(int32_t num);

    };
}


#endif // __KVIOLET__UTILITIES__MATH__H__
