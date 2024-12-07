#include "filesystem.h"

namespace kviolet {
namespace utilities {

bool Filesystem::Exists(const std::string& path) { return access(path.c_str(), F_OK) == 0; }

bool Filesystem::Remove(const std::string& path) {
  if (IsDirectory(path)) {
    DIR* dir = opendir(path.c_str());

    if (dir == nullptr) {
      throw std::runtime_error("No such file or directory : [" + path + "]");
    }

    struct dirent* dirEvent = readdir(dir);

    while (dirEvent) {
      if (dirEvent->d_name[0] != '.') {
        std::string value{};

        if (path[path.size() - 1] == '/') {
          value = path + dirEvent->d_name;
        } else {
          value = path + '/' + dirEvent->d_name;
        }

        if (IsDirectory(value)) {
          if (!Remove(value)) {
            closedir(dir);

            return false;
          }
        } else {
          if (std::remove(value.c_str()) == -1) {
            closedir(dir);

            return false;
          }
        }
      }

      dirEvent = readdir(dir);
    }

    if (std::remove(path.c_str()) == -1) {
      closedir(dir);

      return false;
    }

    closedir(dir);

    return true;
  } else {
    return std::remove(path.c_str()) == 0;
  }
}

bool Filesystem::Rename(const std::string& src, const std::string& dst) {
  if (std::rename(src.c_str(), dst.c_str()) == 0) {
    return true;
  } else {
    throw std::runtime_error("Failed Rename [" + src + "] to [" + dst + "]");
  }
}

bool Filesystem::IsDirectory(const std::string& path) {
  if (Exists(path)) {
    struct stat status {};

    if (::stat(path.c_str(), &status) == -1) {
      throw std::runtime_error("Failed stat : [" + path + "]");
    }

    return S_ISDIR(status.st_mode);
  } else {
    return false;
  }
}

std::size_t Filesystem::Size(const std::string& path) {
  std::ifstream ifs(path, std::ifstream::ate | std::ifstream::binary);

  if (ifs.is_open()) {
    std::size_t size = static_cast<std::size_t>(ifs.tellg());

    ifs.close();

    return size;
  } else {
    throw std::runtime_error("Failed open file : [" + path + "]");
  }
}

std::string Filesystem::Content(const std::string& path) {
  std::ifstream ifs(path, std::ios::binary);

  if (ifs.is_open()) {
    std::string str((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    ifs.close();

    return str;
  } else {
    throw std::runtime_error("Failed open file : [" + path + "]");
  }
}

std::size_t Filesystem::ReadFile(const std::string& path, std::vector<std::string>& container, bool keepEmpty) {
  std::ifstream ifs(path, std::ios::binary);

  if (ifs.is_open()) {
    std::string str{};

    while (!ifs.eof()) {
      std::getline(ifs, str);

      if (!ifs.good()) {
        break;
      }

      if (keepEmpty || !str.empty()) {
        container.push_back(str);
      }
    }

    ifs.close();
  } else {
    throw std::runtime_error("Failed open file : [" + path + "]");
  }

  return container.size();
}

std::vector<std::string> Filesystem::ReadFile(const std::string& path, bool keepEmpty) {
  std::vector<std::string> container;

  ReadFile(path, container, keepEmpty);

  return container;
}

bool Filesystem::CreateFile(const std::string& path) {
  std::ofstream ofs(path, std::ios::binary);

  if (ofs.is_open()) {
    ofs.close();

    return true;
  }

  return false;
}

bool Filesystem::CreateDirectory(const std::string& path) {
  if (mkdir(path.c_str(), 0777) == -1) {
    if (!Exists(path)) {
      throw std::runtime_error("Failed create directory : [" + path + "]");
    }
  }
  return true;
}

bool Filesystem::CreateDirectories(const std::string& path) {
  std::size_t size = path.size();

  for (std::size_t i = 0; i < size; ++i) {
    if (i == (size - 1)) {
      if (!CreateDirectory(path)) {
        return false;
      }
    } else if (path[i] == '/') {
      if (i == 0) {
        continue;
      }

      if (!CreateDirectory(path.substr(0, i))) {
        return false;
      }
    }
  }

  return true;
}

std::string Filesystem::CurrentDirectory() {
  char directory[1024 + 1] = {0};

  return getcwd(directory, 1024) ? directory : "";
}

std::string Filesystem::Name(const std::string& path) {
  std::size_t pos = path.rfind('/');

  return pos == std::string::npos ? path : path.substr(pos + 1);
}

std::string Filesystem::Steam(const std::string& path) {
  std::size_t srcPos = path.rfind('/');
  std::size_t dstPos = path.rfind('.');

  if (srcPos == std::string::npos) {
    return dstPos == std::string::npos ? path : path.substr(0, dstPos);
  } else {
    return (dstPos == std::string::npos || dstPos < srcPos) ? path.substr(srcPos + 1)
                                                            : path.substr(srcPos + 1, dstPos - srcPos - 1);
  }
}

std::string Filesystem::Canonical(const std::string& path) {
  char directory[1024 + 1] = {0};

  return realpath(path.c_str(), directory) ? directory : "";
}

std::string Filesystem::Extension(const std::string& path) {
  std::size_t srcPos = path.rfind('/');
  std::size_t dstPos = path.rfind('.');

  if (srcPos == std::string::npos) {
    return dstPos == std::string::npos ? "" : path.substr(dstPos);
  } else {
    return (dstPos == std::string::npos || dstPos < srcPos) ? "" : path.substr(dstPos);
  }
}

std::string Filesystem::ParentDirectory(const std::string& path) {
  std::size_t pos = path.rfind('/');

  if (pos == std::string::npos) {
    return CurrentDirectory();
  } else {
    return path.substr(0, pos);
  }
}

void Filesystem::TraverseFile(const std::string& path, std::vector<std::string>& container, bool subdirectory) {
  DIR* dir = opendir(path.c_str());

  if (dir == nullptr) {
    throw std::runtime_error("No such file or directory : [" + path + "]");
  }

  struct dirent* dirEvent = readdir(dir);

  while (dirEvent) {
    if (dirEvent->d_name[0] != '.') {
      std::string value{};

      if (path[path.size() - 1] == '/') {
        value = path + dirEvent->d_name;
      } else {
        value = path + '/' + dirEvent->d_name;
      }

      if (IsDirectory(value)) {
        if (subdirectory) {
          TraverseFile(value, container, subdirectory);
        }
      } else {
        container.push_back(value);
      }
    }

    dirEvent = readdir(dir);
  }

  closedir(dir);
}

void Filesystem::TraverseFile(const std::string& path, std::vector<std::string>& container, const std::regex& rule,
                              bool subdirectory) {
  DIR* dir = opendir(path.c_str());

  if (dir == nullptr) {
    throw std::runtime_error("No such file or directory : [" + path + "]");
  }

  struct dirent* dirEvent = readdir(dir);

  while (dirEvent) {
    if (dirEvent->d_name[0] != '.') {
      std::string value{};

      if (path[path.size() - 1] == '/') {
        value = path + dirEvent->d_name;
      } else {
        value = path + '/' + dirEvent->d_name;
      }

      if (IsDirectory(value)) {
        if (subdirectory) {
          TraverseFile(value, container, rule, subdirectory);
        }
      } else {
        if (std::regex_match(value, rule)) {
          container.push_back(value);
        }
      }
    }
    dirEvent = readdir(dir);
  }
  closedir(dir);
}

std::vector<std::string> Filesystem::TraverseFile(const std::string& path, bool subdirectory) {
  std::vector<std::string> container;

  TraverseFile(path, container, subdirectory);

  return container;
}

std::vector<std::string> Filesystem::TraverseFile(const std::string& path, const std::regex& rule, bool subdirectory) {
  std::vector<std::string> container;

  TraverseFile(path, container, rule, subdirectory);

  return container;
}

void Filesystem::TraverseDirectory(const std::string& path, std::vector<std::string>& container, bool subdirectory) {
  DIR* dir = opendir(path.c_str());

  if (dir == nullptr) {
    throw std::runtime_error("No such file or directory : [" + path + "]");
  }

  struct dirent* dirEvent = readdir(dir);

  while (dirEvent) {
    if (dirEvent->d_name[0] != '.') {
      std::string value{};

      if (path[path.size() - 1] == '/') {
        value = path + dirEvent->d_name;
      } else {
        value = path + '/' + dirEvent->d_name;
      }

      if (IsDirectory(value)) {
        container.push_back(value);

        if (subdirectory) {
          TraverseDirectory(value, container, subdirectory);
        }
      }
    }

    dirEvent = readdir(dir);
  }
  closedir(dir);
}

void Filesystem::TraverseDirectory(const std::string& path, std::vector<std::string>& container, const std::regex& rule,
                                   bool subdirectory) {
  DIR* dir = opendir(path.c_str());

  if (dir == nullptr) {
    throw std::runtime_error("No such file or directory : [" + path + "]");
  }

  struct dirent* dirEvent = readdir(dir);

  while (dirEvent) {
    if (dirEvent->d_name[0] != '.') {
      std::string value{};

      if (path[path.size() - 1] == '/') {
        value = path + dirEvent->d_name;
      } else {
        value = path + '/' + dirEvent->d_name;
      }

      if (IsDirectory(value)) {
        if (std::regex_match(value, rule)) {
          container.push_back(value);
        }

        if (subdirectory) {
          TraverseDirectory(value, container, rule, subdirectory);
        }
      }
    }

    dirEvent = readdir(dir);
  }

  closedir(dir);
}

std::vector<std::string> Filesystem::TraverseDirectory(const std::string& path, bool subdirectory) {
  std::vector<std::string> container;

  TraverseDirectory(path, container, subdirectory);

  return container;
}

std::vector<std::string> Filesystem::TraverseDirectory(const std::string& path, const std::regex& rule, bool subdirectory) {
  std::vector<std::string> container;

  TraverseDirectory(path, container, rule, subdirectory);

  return container;
}
}  // namespace utilities
}  // namespace kviolet
