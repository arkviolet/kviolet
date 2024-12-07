#ifndef __KVIOLET__UTILITIES__NET__H__
#define __KVIOLET__UTILITIES__NET__H__

#include "../common/common.h"

namespace kviolet {
namespace utilities {
class API_EXPORT Net {
 public:
  /// 转换范围
  static bool AsRange(const std::string& value, uint16_t& head, uint16_t& tail);

  /// 转换网络字节序范围
  static bool AsNetByte(const std::string& value, uint32_t& head, uint32_t& tail);

  /// 转换主机字节序范围
  static bool AsHostByte(const std::string& value, uint32_t& head, uint32_t& tail);

  /// 遍历域名对应的地址列表
  static bool TraverseAddressFromHost(const char* host, std::vector<std::string>& list);

  /// 关闭套接字
  static bool CloseSocket(int32_t socket);

  /// 关闭Nagle算法
  static bool DisableNagle(int32_t socket);

  /// 设置延时关闭
  static bool EnableLinger(int32_t socket, int32_t timeout = 0);

  /// 启用非堵塞
  static bool EnableNonBlock(int32_t socket);

  /// 启用地址复用
  static bool EnableReuseAddress(int32_t socket);

  /// 获取本地地址
  static bool GetLocalAddress(int32_t socket, struct sockaddr_in& address);

  /// 获取远程地址
  static bool GetRemoteAddress(int32_t socket, struct sockaddr_in& address);

  /// 设置发送超时时间
  static bool SetSendTimeout(int32_t sock, std::time_t second);

  /// 设置接收超时时间
  static bool SetReceiveTimeout(int32_t sock, std::time_t second);

  /// 设置发送缓冲区大小
  static bool SetSendBufferSize(int32_t sock, int32_t size);

  /// 设置接收缓冲区大小
  static bool SetReceiveBufferSize(int32_t sock, int32_t size);

  /// 获取协议族
  static int32_t GetFamily(int32_t sock);

  /// 获取发送缓冲区大小
  static int32_t GetSendBufferSize(int32_t sock);

  /// 获取接收缓冲区大小
  static int32_t GetReceiveBufferSize(int32_t sock);

  /// 转换网络字节序
  static uint32_t AsNetByte(const char* value);

  /// 转换主机字节序
  static uint32_t AsHostByte(const char* value);

  /// 转换为字符串
  static std::string AsString(uint32_t value);
};

}  // namespace utilities
}  // namespace kviolet

#endif  // __KVIOLET__UTILITIES__NET__H__
