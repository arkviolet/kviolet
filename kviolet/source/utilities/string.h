#ifndef __KVIOLET__UTILITIES__STRING_H__
#define __KVIOLET__UTILITIES__STRING_H__

#include "../common/common.h"

namespace kviolet {
namespace utilities {

class API_EXPORT String {
 public:
  static void PrintHex(const std::string& data, char w = ' ');

  static void PrintChar(const std::string& data);

  /// 去除首尾字符
  static void Trim(std::string& value, const char* group = "\r\n\t ");

  static std::string Trim(const std::string& value, const char* group = "\r\n\t ");

  /// 转换小写
  static void Lower(std::string& value, std::size_t index = 0);

  static std::string Lower(const std::string& value, std::size_t index = 0);

  /// 转换大写
  static void Upper(std::string& value, std::size_t index = 0);

  static std::string Upper(const std::string& value, std::size_t index = 0);

  /// 删除字符串指定字符
  static void Erase(std::string& value, char key, std::size_t index = 0);

  static std::string Erase(const std::string& value, char key, std::size_t index = 0);

  static void Erase(std::string& value, const std::string& key, std::size_t index = 0);

  static std::string Erase(const std::string& value, const std::string& key, std::size_t index = 0);

  static void Erase(std::string& value, const std::function<bool(char)>& function, std::size_t index = 0);

  static std::string Erase(const std::string& value, const std::function<bool(char)>& function, std::size_t index = 0);

  /// 字符串替换字符
  static void Replace(std::string& value, const std::string& src, const std::string& dst, std::size_t index = 0);

  static std::string Replace(const std::string& value, const std::string& src, const std::string& dst,
                             std::size_t index = 0);

  static void ReplaceAll(std::string& value, const std::string& src, const std::string& dst, std::size_t index = 0);

  static std::string ReplaceAll(const std::string& value, const std::string& src, const std::string& dst,
                                std::size_t index = 0);

  /// 是否包含被查找的字符
  static bool With(const char* value, char infix, std::size_t index = 0);

  static bool With(const char* value, const char* infix, std::size_t index = 0);

  static bool With(const std::string& value, char infix, std::size_t index = 0);

  static bool With(const std::string& value, const char* infix, std::size_t index = 0);

  static bool With(const std::string& value, const std::string& infix, std::size_t index = 0);

  /// 是否以字符串结尾
  static bool EndWith(const std::string& value, const std::string& suffix);

  /// 是否字符串开头
  static bool StartWith(const std::string& value, const std::string& prefix);

  /// 按字符串拆分
  static std::size_t Split(const std::string& value, const std::string& key, std::vector<std::string>& container,
                           bool keepEmpty = false);

  static std::vector<std::string> Split(const std::string& value, const std::string& key, bool keepEmpty = false);

  /// 按行拆分
  static std::size_t SplitLines(const std::string& value, std::vector<std::string>& container, bool keepEnter = false);

  static std::vector<std::string> SplitLines(const std::string& value, bool keepEnter = false);

  /// 过滤注释
  static std::string FilterNote(const std::string& value);

  /// 转换16进制字符串
  static std::string AsHexString(const char* value, bool reverse = false);

  static std::string AsHexString(const uint8_t* value, bool reverse = false);

  static std::string AsHexString(const std::string& value, bool reverse = false);

  static std::string AsHexString(const char* value, std::size_t size, bool reverse = false);

  static std::string AsHexString(const uint8_t* value, std::size_t size, bool reverse = false);

  static std::string AsHexString(const std::string& value, std::size_t size, bool reverse = false);
};

class API_EXPORT HexString {
 public:
  /// 转换字符
  static uint8_t AsByte(const char* value);

  static uint8_t AsByte(const std::string& value);

  /// 转换字符串
  static std::string AsString(const char* value, bool reverse = false);

  static std::string AsString(const std::string& value, bool reverse = false);

  static std::string AsString(const char* value, std::size_t size, bool reverse = false);

  static std::string AsString(const std::string& value, std::size_t size, bool reverse = false);
};

}  // namespace utilities
}  // namespace kviolet

#endif  // __KVIOLET__UTILITIES__STRING_H__
