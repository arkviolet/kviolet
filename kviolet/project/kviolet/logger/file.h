#ifndef __KVIOLET__LOGGER__FILE__H__
#define __KVIOLET__LOGGER__FILE__H__

#include "../common/common.h"

namespace kviolet
{
    class KVIOLET_CLASS_API LoggerFile
    {
    public:
        LoggerFile();

        ~LoggerFile();

    public:
        bool IsOpen();

        void Close();

        void Flush();

        bool ReOpen();

        std::size_t Size();

        std::string Path();

        bool Write(const std::string &value);

        bool Open(const std::string &path, bool truncate = false);

    private:
        std::size_t _size;
        std::string _path;
        std::ofstream _file;
    };
}

#endif ///__KVIOLET__LOGGER__FILE__H__


