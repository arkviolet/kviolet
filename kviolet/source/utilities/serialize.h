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
  Serialize(const char* data, uint32_t size) {
    size_ = size;
    buffer_ = new char[size];
    memcpy(buffer_, data, size);
  }

  ~Serialize() { delete[] buffer_; }

 public:
  Serialize& operator<<(bool item) { return Append(item); }
  Serialize& operator<<(uint32_t item) { return Append(item); }
  Serialize& operator<<(int item) { return Append(item); }
  Serialize& operator<<(uint64_t item) { return Append(item); }
  Serialize& operator<<(int64_t item) { return Append(item); }
  Serialize& operator<<(double item) { return Append(item); }
  Serialize& operator<<(const std::string& item) { return Append(item.c_str(), item.size()); }
  Serialize& operator<<(const char* item) { return Append(item, strlen(item)); }

  Serialize& operator>>(bool& item) {
    item = *reinterpret_cast<bool*>(buffer_ + offset_);
    offset_ += sizeof(item);
    return *this;
  }

  Serialize& operator>>(uint32_t& item) { return Extract(item); }
  Serialize& operator>>(int& item) { return Extract(item); }
  Serialize& operator>>(uint64_t& item) { return Extract(item); }
  Serialize& operator>>(int64_t& item) { return Extract(item); }
  Serialize& operator>>(double& item) { return Extract(item); }
  Serialize& operator>>(std::string& item) { return Extract(item); }

 public:
  template <typename... _Args>
  void SerializePack(_Args&&... args) {
    (void)(*this << ... << args);
  }

  template <typename... _Args>
  void DeserializePack(_Args&... args) {
    (void)(*this >> ... >> args);
  }

 public:
  uint32_t size() { return size_; }
  uint32_t offset() { return offset_; }
  const char* str() { return buffer_; }

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

  template <typename T>
  Serialize& Extract(T& item) {
    /// TODO std::is_same<std::string&, decltype(item)>::value)
    item = *reinterpret_cast<T*>(buffer_ + offset_);
    offset_ += sizeof(item);
    return *this;
  }

  Serialize& Extract(std::string& item) {
    auto len = *reinterpret_cast<uint32_t*>(buffer_ + offset_);
    offset_ += sizeof(uint32_t);
    item = std::move(std::string(buffer_ + offset_, len));
    offset_ += len;
    return *this;
  }

 private:
  uint32_t size_{0};
  uint32_t offset_{0};
  char* buffer_{nullptr};
};

}  // namespace utilities
}  // namespace kviolet

#endif  // __KVIOLET__UTILITIES__SERIALIZE__H__
