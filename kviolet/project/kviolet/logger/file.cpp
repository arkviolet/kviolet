#include "file.h"

namespace kviolet
{
    LoggerFile::LoggerFile() : _size(0)
    {

    }

    LoggerFile::~LoggerFile()
    {
        Close();
    }

    bool LoggerFile::IsOpen()
    {
        return _file.is_open();
    }

    void LoggerFile::Close()
    {
        _size = 0;

        if (_file.is_open())
        {
            _file.flush();
            _file.close();
        }
    }

    void LoggerFile::Flush()
    {
        _file.flush();
    }

    bool LoggerFile::ReOpen()
    {
        Close();

        return Open(_path, true);
    }


    std::size_t LoggerFile::Size()
    {
        return _size;
    }

    std::string LoggerFile::Path()
    {
        return _path;
    }

    bool LoggerFile::Write(const std::string &value)
    {
        if (_file.is_open())
        {
            _file << value;

            _size += value.size();
        }
    }

    bool LoggerFile::Open(const std::string &path, bool truncate)
    {
        if (_file.is_open())
        {
            return true;
        }

        _file.open(path, truncate ? std::ios::binary : std::ios::binary | std::ios::app);

        if (_file.is_open())
        {
            _path = path;

            _size += static_cast<std::size_t>(_file.tellp());

            return true;
        }
        return false;
    }
}
