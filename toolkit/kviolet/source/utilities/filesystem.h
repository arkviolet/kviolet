#ifndef __KVIOLET__UTILITIES__FILE_SYSTEM__H__
#define __KVIOLET__UTILITIES__FILE_SYSTEM__H__

#include "../common/common.h"

namespace kviolet {
namespace utilities {
class API_EXPORT Filesystem {
 public:
  /// 文件是否存在
  static bool Exists(const std::string& path);

  /// 删除目录
  static bool Remove(const std::string& path);

  /// 更改文件名称
  static bool Rename(const std::string& src, const std::string& dst);

  /// 是否为目录
  static bool IsDirectory(const std::string& path);

  /// 文件大小
  static std::size_t Size(const std::string& path);

  /// 文件内容
  static std::string Content(const std::string& path);

  /// 读取文件内容
  static std::size_t ReadFile(const std::string& path, std::vector<std::string>& container, bool keepEmpty = false);

  /// 读取文件内容
  static std::vector<std::string> ReadFile(const std::string& path, bool keepEmpty = false);

  /// 写入文件
  template <typename ValueT>
  static bool WriteFile(const std::string& path, ValueT&& value) {
    std::ofstream ofs(path, std::ios::binary);

    if (ofs.is_open()) {
      ofs << std::forward<ValueT>(value);

      ofs.close();

      return true;
    } else {
      throw std::runtime_error("Failed open file : " + path);
    }
  }

  /// 写入文件
  template <typename It>
  static bool WriteFile(const std::string& path, const It& begin, const It& end) {
    std::ofstream ofs(path, std::ios::binary);

    if (ofs.is_open()) {
      for (auto iter = begin; iter != end; ++iter) {
        ofs << *iter << std::endl;
      }

      ofs.close();

      return true;
    } else {
      throw std::runtime_error("Failed open file : " + path);
    }
  }

  /// 创建文件
  static bool CreateFile(const std::string& path);

  /// 创建文件夹
  static bool CreateDirectory(const std::string& path);

  /// 创建层级目录
  static bool CreateDirectories(const std::string& path);

  /// 当前目录
  static std::string CurrentDirectory();

  /// 文件名
  static std::string Name(const std::string& path);

  /// 文件前缀
  static std::string Steam(const std::string& path);

  /// 绝对路径
  static std::string Canonical(const std::string& path);

  /// 文件扩展名
  static std::string Extension(const std::string& path);

  /// 父级路径
  static std::string ParentDirectory(const std::string& path);

  /// 遍历文件
  static void TraverseFile(const std::string& path, std::vector<std::string>& container, bool subdirectory = false);

  /// 遍历文件
  static void TraverseFile(const std::string& path, std::vector<std::string>& container, const std::regex& rule,
                           bool subdirectory = false);

  /// 遍历文件
  static std::vector<std::string> TraverseFile(const std::string& path, bool subdirectory = false);

  /// 遍历文件
  static std::vector<std::string> TraverseFile(const std::string& path, const std::regex& rule, bool subdirectory = false);

  /// 遍历文件
  static void TraverseDirectory(const std::string& path, std::vector<std::string>& container, bool subdirectory = false);

  /// 遍历文件
  static void TraverseDirectory(const std::string& path, std::vector<std::string>& container, const std::regex& rule,
                                bool subdirectory = false);

  /// 遍历目录
  static std::vector<std::string> TraverseDirectory(const std::string& path, bool subdirectory = false);

  /// 遍历目录
  static std::vector<std::string> TraverseDirectory(const std::string& path, const std::regex& rule,
                                                    bool subdirectory = false);
};

}  // namespace utilities
}  // namespace kviolet

#endif  // __KVIOLET__UTILITIES__FILE_SYSTEM__H__
