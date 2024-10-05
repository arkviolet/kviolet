#ifndef __KVIOLET__ENCKIT__HTTP__CLIENT__H__
#define __KVIOLET__ENCKIT__HTTP__CLIENT__H__

#include <curl/curl.h>
#include <math.h>

#include <ctime>
#include <string>

class HTTPProxy {
 public:
  HTTPProxy() = default;
  ~HTTPProxy();

 public:
  void Clear();

 public:
  bool enable{false};
  std::string host{};
  std::string user{};
  std::string pass{};
  std::string login{};
  curl_proxytype type{CURLPROXY_HTTP};
};

class HTTPSession {
 public:
  HTTPSession() = default;
  ~HTTPSession();

 public:
  void Clear();

 public:
  uint32_t count{0};
  uint32_t verbose{0};
  uint32_t errorCount{0};
  uint32_t failedCount{0};
  uint32_t successCount{0};

  bool skip{true};  // 302 是否跳转

  std::time_t timeout{0};
  std::time_t receiveTimeout{0};

  std::string url{};
  std::string user{};
  std::string pass{};
  std::string login{};
  std::string caFile{};
  std::string params{};
  std::string cookie{};
  std::string userAgent{};
  std::string requestOption{};

  struct curl_slist *headers{nullptr};
};

class HTTPResponse {
 public:
  HTTPResponse() = default;
  ~HTTPResponse();

 public:
  void Clear();

 public:
  uint32_t code{0};
  std::string url{};
  std::string host{};
  std::string header{};
  std::string content{};
  std::string askHeader{};
  std::double_t totalTime{0.0};
  std::double_t contentLength{0.0};
  std::double_t contentLengthZip{0.0};
};

class HTTPClient {
  enum class HTTP_OPTION_TYPE : uint8_t {
    GET,
    PUT,
    POST,
    OTHER,
  };

 public:
  HTTPClient() = default;
  HTTPClient(std::string url);
  ~HTTPClient();

 public:
  bool Get();
  bool Put();
  bool Post();
  bool Request();
  const char *LastError() const;
  const HTTPProxy &Proxy() const;
  const HTTPSession &Session() const;
  const HTTPResponse &Response() const;
  void SetUrl(std::string url);
  void SetLogin(std::string user, std::string pass);
  void SetProxy(std::string host, std::string user, std::string pass, curl_proxytype type = CURLPROXY_HTTP);
  void SetParam(std::string param);
  void SetSkip(bool skip);
  void SetCAFile(std::string caFile);
  void SetCookie(std::string cookie);
  void SetHeader(const char *header);
  void SetUserAgent(std::string userAgent);
  void SetConnectTimeout(std::time_t timeout);
  void SetReceiveTimeout(std::time_t timeout);
  void SetRequestOption(std::string requestOption);
  void AddParam(const std::string &param);
  void AddHeader(const char *header);
  void Clear();
  void ClearProxy();
  void ClearSession();
  void ClearResponse();
  void EnableVerbose();
  void DisableVerbose();

  static void GlobalRelease();
  static bool GlobalInitialize();

 protected:
  bool Initialize();
  void SetProxy();
  void SetSession(HTTP_OPTION_TYPE option);
  void SetShareDNSCache(CURL *curl);
  void ParseResponseCode();
  void ParseResponseLength();
  bool Launch(HTTP_OPTION_TYPE option);
  static std::size_t WriteFunction(void *buffer, std::size_t size, std::size_t nmemb, void *stream);
  static std::size_t HeaderFunction(void *buffer, std::size_t size, std::size_t nmemb, void *stream);
  static size_t AskHeaderFunction(CURL *handle, curl_infotype type, void *buffer, size_t size, void *stream);

 protected:
  bool _isFirstWrite{true};
  CURL *_curl{nullptr};
  CURLcode _errorCode{CURLE_OK};
  HTTPProxy _proxy{};
  HTTPSession _session{};
  HTTPResponse _response{};
};

#endif  // __KVIOLET__ENCKIT__HTTP__CLIENT__H__
