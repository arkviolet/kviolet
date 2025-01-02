#include "net.h"

namespace kviolet {
namespace utilities {

bool Net::AsRange(const std::string& value, uint16_t& head, uint16_t& tail) {
  std::size_t pos = value.find('-');

  if (pos == std::string::npos) {
    head = static_cast<uint16_t>(strtoul(value.c_str(), nullptr, 10));
    tail = head;
  } else  /// a-b
  {
    head = static_cast<uint16_t>(strtoul(value.substr(0, pos).c_str(), nullptr, 10));
    tail = static_cast<uint16_t>(strtoul(value.substr(pos + 1).c_str(), nullptr, 10));
  }

  return head <= tail;
}

bool Net::AsNetByte(const std::string& value, uint32_t& head, uint32_t& tail) {
  std::size_t pos = value.find('-');

  if (pos == std::string::npos) {
    pos = value.find('/');

    if (pos == std::string::npos)  /// a.b.c.d
    {
      head = AsNetByte(value.c_str());
      tail = head;
    } else {
      if (value.find('.', pos + 1) == std::string::npos)  /// a.b.c.d/e
      {
        int64_t mask = strtol(value.substr(pos + 1).data(), nullptr, 10);

        if (32 < mask || mask < 0) {
          return false;
        }

        head = AsNetByte(value.substr(0, pos).c_str());
        tail = head | ~(mask == 0 ? 0 : htonl(0xFFFFFFFF << (32 - mask)));
      } else  /// a.b.c.d/a.b.c.d
      {
        head = AsNetByte(value.substr(0, pos).c_str());
        tail = AsNetByte(value.substr(pos + 1).c_str());
      }
    }
  } else  /// a.b.c.d-a.b.c.d
  {
    head = AsNetByte(value.substr(0, pos).c_str());
    tail = AsNetByte(value.substr(pos + 1).c_str());
  }

  return head <= tail;
}

bool Net::AsHostByte(const std::string& value, uint32_t& head, uint32_t& tail) {
  std::size_t pos = value.find('-');

  if (pos == std::string::npos) {
    pos = value.find('/');

    if (pos == std::string::npos)  /// a.b.c.d
    {
      head = AsHostByte(value.c_str());
      tail = head;
    } else {
      if (value.find('.', pos + 1) == std::string::npos)  /// a.b.c.d/e
      {
        int64_t mask = strtol(value.substr(pos + 1).data(), nullptr, 10);

        if (32 < mask || mask < 0) {
          return false;
        }

        head = AsHostByte(value.substr(0, pos).c_str());
        tail = head | ~(mask == 0 ? 0 : 0xFFFFFFFF << (32 - mask));
      } else  /// a.b.c.d/a.b.c.d
      {
        head = AsHostByte(value.substr(0, pos).c_str());
        tail = AsHostByte(value.substr(pos + 1).c_str());
      }
    }
  } else  /// a.b.c.d-a.b.c.d
  {
    head = AsHostByte(value.substr(0, pos).c_str());
    tail = AsHostByte(value.substr(pos + 1).c_str());
  }

  return head <= tail;
}

bool Net::TraverseAddressFromHost(const char* host, std::vector<std::string>& list) {
  bool status = false;

  struct addrinfo hints {};
  struct addrinfo* result{nullptr};

  hints.ai_flags = AI_CANONNAME;
  hints.ai_family = AF_UNSPEC;  /// 意味着函数返回的是适用于指定主机名和服务名且适合任何协议族的地址
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;

  auto res = getaddrinfo(host, nullptr, &hints, &result);

  if (res == 0) {
    for (auto iter = result; iter != nullptr; iter = iter->ai_next) {
      char address[1024]{0};

      res = getnameinfo(iter->ai_addr, static_cast<socklen_t>(iter->ai_addrlen), address, sizeof(address), nullptr, 0, NI_NUMERICHOST | NI_NUMERICSERV);

      if (res == 0) {
        status = true;

        list.emplace_back(address);
      } else {
        status = false;

        KVIOLET_ASSERT_CPP(gai_strerror(res));

        break;
      }
    }

    freeaddrinfo(result);
  } else {
    status = false;

    KVIOLET_ASSERT_CPP(gai_strerror(res));
  }

  return status;
}

bool Net::CloseSocket(int32_t socket) {
  return ::close(socket) == 0;
}

bool Net::DisableNagle(int32_t socket) {
  int32_t val = 1l;

  return setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&val), sizeof(val)) == 0;
}

bool Net::EnableLinger(int32_t socket, int32_t timeout) {
  struct linger val {};

  val.l_onoff = 1l;
  val.l_linger = timeout;

  return setsockopt(socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<const char*>(&val), sizeof(val)) == 0;
}

bool Net::EnableNonBlock(int32_t socket) {
  return fcntl(socket, F_SETFL, fcntl(socket, F_GETFL, 0) | O_NONBLOCK) == 0;
}

bool Net::EnableReuseAddress(int32_t socket) {
  int32_t val = 1l;

  return setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&val), sizeof(val)) == 0;
}

bool Net::GetLocalAddress(int32_t socket, struct sockaddr_in& address) {
  std::size_t len = sizeof(struct sockaddr_in);

  return ::getsockname(socket, reinterpret_cast<struct sockaddr*>(&address), reinterpret_cast<socklen_t*>(&len)) == 0;
}

bool Net::GetRemoteAddress(int32_t socket, struct sockaddr_in& address) {
  std::size_t len = sizeof(struct sockaddr_in);

  return ::getpeername(socket, reinterpret_cast<struct sockaddr*>(&address), reinterpret_cast<socklen_t*>(&len)) == 0;
}

bool Net::SetSendTimeout(int32_t sock, std::time_t second) {
  struct timeval timeout {
    .tv_sec = second, .tv_usec = 0
  };

  return setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout)) == 0;
}

bool Net::SetReceiveTimeout(int32_t sock, std::time_t second) {
  struct timeval timeout {
    .tv_sec = second, .tv_usec = 0
  };

  return setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout)) == 0;
}

bool Net::SetSendBufferSize(int32_t sock, int32_t size) {
  return setsockopt(sock, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<const char*>(&size), sizeof(size)) == 0;
}

bool Net::SetReceiveBufferSize(int32_t sock, int32_t size) {
  return setsockopt(sock, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char*>(&size), sizeof(size)) == 0;
}

int32_t Net::GetFamily(int32_t sock) {
  socklen_t len = sizeof(struct sockaddr_storage);

  struct sockaddr_storage storage {};

  return getsockname(sock, reinterpret_cast<struct sockaddr*>(&storage), &len) == 0 ? storage.ss_family : -1;
}

int32_t Net::GetSendBufferSize(int32_t sock) {
  int32_t optionValue = -1;

  socklen_t optionLength = sizeof(optionValue);

  return getsockopt(sock, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<char*>(&optionValue), &optionLength) == 0 ? optionValue : -1;
}

int32_t Net::GetReceiveBufferSize(int32_t sock) {
  int32_t optionValue = -1;

  socklen_t optionLength = sizeof(optionValue);

  return getsockopt(sock, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<char*>(&optionValue), &optionLength) == 0 ? optionValue : -1;
}

uint32_t Net::AsNetByte(const char* value) {
  struct in_addr addr {
    0
  };

  inet_pton(AF_INET, value, &addr);

  return addr.s_addr;
}

uint32_t Net::AsHostByte(const char* value) {
  return inet_network(value);
}

std::string Net::AsString(uint32_t value) {
  return std::to_string((value >> 24) & 0xFF) + "." + std::to_string((value >> 16) & 0xFF) + "." + std::to_string((value >> 8) & 0xFF) + "." + std::to_string((value >> 0) & 0xFF);
}

}  // namespace utilities
}  // namespace kviolet
