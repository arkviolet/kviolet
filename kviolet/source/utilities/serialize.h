#ifndef __KVIOLET__UTILITIES__SERIALIZE__H__
#define __KVIOLET__UTILITIES__SERIALIZE__H__

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace kviolet {
namespace utilities {

class Serialize {
 public:
  Serialize() = delete;
  Serialize(uint32_t reserve) { buffer_ = new char[reserve]; }
  ~Serialize() { delete[] buffer_; }

 public:
  Serialize& operator<<(bool item) { return Append(item); }
  Serialize& operator<<(int item) { return Append(item); }
  Serialize& operator<<(uint32_t item) { return Append(item); }
  Serialize& operator<<(uint64_t item) { return Append(item); }
  Serialize& operator<<(int64_t item) { return Append(item); }
  Serialize& operator<<(double item) { return Append(item); }
  Serialize& operator<<(const char* item) { return Append(item, strlen(item)); }
  Serialize& operator<<(const std::string& item) { return Append(item.c_str(), item.size()); }

 public:
#if defined(__GNUC__) && (__GNUC__ >= 6)
  template <typename... _Args>
  void SerializePack(_Args&&... args) {
    (void)(*this << ... << args);
  }
#endif

 public:
  uint32_t Size() { return size_; }
  const char* Str() { return buffer_; }

 protected:
  template <typename T>
  Serialize& Append(T item) {
    memcpy(buffer_ + size_, &item, sizeof(item));
    size_ += sizeof(item);
    return *this;
  }

  Serialize& Append(const char* item, uint32_t size) {
    memcpy(buffer_ + size_, &size, sizeof(uint32_t));
    size_ += sizeof(uint32_t);
    memcpy(buffer_ + size_, item, size);
    size_ += size;
    return *this;
  }

 private:
  uint32_t size_{0};
  char* buffer_{nullptr};
};

class Deserialize {
 public:
  Deserialize() = delete;
  ~Deserialize() = default;
  Deserialize(const char* data) { data_ = data; }

 public:
  Deserialize& operator>>(bool& item) { return Extract(item); }
  Deserialize& operator>>(int& item) { return Extract(item); }
  Deserialize& operator>>(uint32_t& item) { return Extract(item); }
  Deserialize& operator>>(uint64_t& item) { return Extract(item); }
  Deserialize& operator>>(int64_t& item) { return Extract(item); }
  Deserialize& operator>>(double& item) { return Extract(item); }
  Deserialize& operator>>(std::string& item) { return Extract(item); }

 public:
#if defined(__GNUC__) && (__GNUC__ >= 6)
  template <typename... _Args>
  void DeserializePack(_Args&... args) {
    (void)(*this >> ... >> args);
  }
#endif

 public:
  uint32_t Offset() { return offset_; }

 protected:
  template <typename T>
  Deserialize& Extract(T& item) {
    /// TODO std::is_same<std::string&, decltype(item)>::value)
    item = *(T*)(data_ + offset_);
    offset_ += sizeof(item);
    return *this;
  }

  Deserialize& Extract(std::string& item) {
    auto len = *(uint32_t*)(data_ + offset_);
    offset_ += sizeof(uint32_t);
    item = std::move(std::string(data_ + offset_, len));
    offset_ += len;
    return *this;
  }

 private:
  uint32_t offset_{0};
  const char* data_{nullptr};
};

}  // namespace utilities
}  // namespace kviolet

#endif  // __KVIOLET__UTILITIES__SERIALIZE__H__
