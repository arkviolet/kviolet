#include "http_client.h"

#include <mutex>

std::mutex _mux;  // 锁

HTTPProxy::~HTTPProxy() { Clear(); }

void HTTPProxy::Clear() {
  enable = false;

  host.clear();
  user.clear();
  pass.clear();
  login.clear();

  type = CURLPROXY_HTTP;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

HTTPSession::~HTTPSession() { Clear(); }

void HTTPSession::Clear() {
  count = 0;
  verbose = 0;
  errorCount = 0;
  failedCount = 0;
  successCount = 0;

  timeout = 0;
  receiveTimeout = 0;

  skip = true;

  url.clear();
  user.clear();
  pass.clear();
  login.clear();
  caFile.clear();
  params.clear();
  cookie.clear();
  userAgent.clear();
  requestOption.clear();

  if (headers) {
    curl_slist_free_all(headers);
    headers = nullptr;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

HTTPResponse::~HTTPResponse() { Clear(); }

void HTTPResponse::Clear() {
  code = 0;

  header.clear();
  content.clear();
  askHeader.clear();

  totalTime = 0.0;
  contentLength = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

HTTPClient::HTTPClient(std::string url) { SetUrl(std::move(url)); }

HTTPClient::~HTTPClient() { Clear(); }

bool HTTPClient::Get() {
  SetRequestOption("GET");

  return Launch(HTTP_OPTION_TYPE::GET);
}

bool HTTPClient::Put() {
  SetRequestOption("PUT");

  return Launch(HTTP_OPTION_TYPE::PUT);
}

bool HTTPClient::Post() {
  SetRequestOption("POST");

  return Launch(HTTP_OPTION_TYPE::POST);
}

bool HTTPClient::Request() { return Launch(HTTP_OPTION_TYPE::OTHER); }

const char *HTTPClient::LastError() const {
  return curl_easy_strerror(_errorCode);
}

const HTTPProxy &HTTPClient::Proxy() const { return _proxy; }

const HTTPSession &HTTPClient::Session() const { return _session; }

const HTTPResponse &HTTPClient::Response() const { return _response; }

void HTTPClient::SetUrl(std::string url) {
  _session.url = std::move(url);
  _response.url = _session.url;
}

void HTTPClient::SetLogin(std::string user, std::string pass) {
  _session.user = std::move(user);
  _session.pass = std::move(pass);

  if (!_session.user.empty() || !_session.pass.empty()) {
    _session.login = _session.user + ":" + _session.pass;
  }
}

void HTTPClient::SetProxy(std::string host, std::string user, std::string pass,
                          curl_proxytype type) {
  _proxy.type = type;
  _proxy.host = std::move(host);
  _proxy.user = std::move(user);
  _proxy.pass = std::move(pass);
  _proxy.enable = true;

  if (!_proxy.user.empty() || !_proxy.pass.empty()) {
    _proxy.login = _proxy.user + ":" + _proxy.pass;
  }
}

void HTTPClient::SetParam(std::string param) {
  _session.params = std::move(param);
}

void HTTPClient::SetSkip(bool skip) { _session.skip = skip; }

void HTTPClient::SetCAFile(std::string caFile) {
  _session.caFile = std::move(caFile);
}

void HTTPClient::SetCookie(std::string cookie) {
  _session.cookie = std::move(cookie);
}

void HTTPClient::SetHeader(const char *header) {
  if (_session.headers) {
    curl_slist_free_all(_session.headers);

    _session.headers = nullptr;
  }

  AddHeader(header);
}

void HTTPClient::SetUserAgent(std::string userAgent) {
  _session.userAgent = std::move(userAgent);
}

void HTTPClient::SetConnectTimeout(std::time_t timeout) {
  _session.timeout = timeout;
}

void HTTPClient::SetReceiveTimeout(std::time_t timeout) {
  _session.receiveTimeout = timeout;
}

void HTTPClient::SetRequestOption(std::string requestOption) {
  _session.requestOption = std::move(requestOption);
}

void HTTPClient::AddParam(const std::string &param) {
  _session.params += param;
}

void HTTPClient::AddHeader(const char *header) {
  _session.headers = curl_slist_append(_session.headers, header);
}

void HTTPClient::Clear() {
  ClearProxy();
  ClearSession();
  ClearResponse();

  _errorCode = CURLE_OK;

  _isFirstWrite = true;

  if (_curl) {
    curl_easy_cleanup(_curl);

    _curl = nullptr;
  }
}

void HTTPClient::ClearProxy() { _proxy.Clear(); }

void HTTPClient::ClearSession() { _session.Clear(); }

void HTTPClient::ClearResponse() { _response.Clear(); }

void HTTPClient::EnableVerbose() { _session.verbose = 1L; }

void HTTPClient::DisableVerbose() { _session.verbose = 0L; }

void HTTPClient::GlobalRelease() { curl_global_cleanup(); }

bool HTTPClient::GlobalInitialize() {
  return curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK;
}

bool HTTPClient::Initialize() {
  _response.Clear();

  _curl = curl_easy_init();

  _errorCode = CURLE_OK;

  _isFirstWrite = true;

  SetShareDNSCache(_curl);

  if (_curl) {
    return true;
  } else {
    _errorCode = CURLE_FAILED_INIT;

    ++_session.errorCount;

    return false;
  }
}

void HTTPClient::SetProxy() {
  if (_proxy.enable) {
    curl_easy_setopt(_curl, CURLOPT_PROXY, _proxy.host.c_str());  /// 代理主机
    curl_easy_setopt(_curl, CURLOPT_PROXYTYPE, _proxy.type);  /// 代理类型
    curl_easy_setopt(_curl, CURLOPT_PROXYAUTH, CURLAUTH_ANY);  /// 代理认证模式

    if (!_proxy.login.empty()) {
      /// 代理登陆信息
      curl_easy_setopt(_curl, CURLOPT_PROXYUSERPWD, _proxy.login.c_str());
    }
  }
}

void HTTPClient::SetSession(HTTP_OPTION_TYPE option) {
  if (_session.headers) {
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, _session.headers);
  }

  if (_session.timeout == 0) {
    curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, 3);
  } else {
    curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, _session.timeout);
  }

  if (_session.receiveTimeout == 0) {
    curl_easy_setopt(_curl, CURLOPT_TIMEOUT, 3);
  } else {
    curl_easy_setopt(_curl, CURLOPT_TIMEOUT, _session.receiveTimeout);
  }

  if (!_session.url.empty()) {
    curl_easy_setopt(_curl, CURLOPT_URL, _session.url.c_str());
  }

  if (!_session.login.empty()) {
    curl_easy_setopt(_curl, CURLOPT_USERPWD, _session.login.c_str());
  }

  if (_session.caFile.empty()) {

    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);    /// 不验证证书
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 0L);    /// 不验证证书中是否设置域名
  } else {

    curl_easy_setopt(_curl, CURLOPT_CAINFO, _session.caFile.c_str());    /// CA根证书
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 1L);    /// 只信任CA颁布的证书

    /// 检查证书中是否设置域名, 并且是否与提供的主机名匹配
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 2L);
  }

  switch (option) {
    case HTTP_OPTION_TYPE::GET: {
      break;
    }

    case HTTP_OPTION_TYPE::PUT: {
      curl_easy_setopt(_curl, CURLOPT_PUT, 1L);  /// 设置put操作
      if (!_session.params.empty()) {
        curl_easy_setopt(_curl, CURLOPT_POSTFIELDS,
                         _session.params.c_str());  /// 设置提交的数据
      }

      break;
    }
    case HTTP_OPTION_TYPE::POST: {
      curl_easy_setopt(_curl, CURLOPT_POST, 1L);  /// 设置post操作
      if (!_session.params.empty()) {
        curl_easy_setopt(_curl, CURLOPT_POSTFIELDS,
                         _session.params.c_str());  /// 设置提交的数据
      }
      break;
    }
    default: {
      curl_easy_setopt(_curl, CURLOPT_CUSTOMREQUEST, _session.requestOption.c_str());  /// 设置自定义请求方式
      break;
    }
  }

  // 设置获取请求头
  curl_easy_setopt(_curl, CURLOPT_VERBOSE, 1L);  // 启用汇报信息
  curl_easy_setopt(_curl, CURLOPT_DEBUGFUNCTION, AskHeaderFunction);
  curl_easy_setopt(_curl, CURLOPT_DEBUGDATA, this);

  // curl_easy_setopt(_curl, CURLOPT_USERAGENT,);  /// 设置用户代理

  curl_easy_setopt(_curl, CURLOPT_WRITEDATA, this);   /// 设置获取返回内容的缓冲区
  curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteFunction);  /// 设置获取返回内容的回调函数
  curl_easy_setopt(_curl, CURLOPT_HEADERDATA, this);  /// 设置获取头部信息的缓冲区
  curl_easy_setopt(_curl, CURLOPT_HEADERFUNCTION, HeaderFunction);  /// 设置获取头部信息的回调函数

  /// 当多个线程都使用超时处理的时候, 同时主线程中有sleep或是wait等操作.
  /// 如果不设置这个选项, 将会发信号打断wait从而导致程序退出.
  curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);

  curl_easy_setopt(_curl, CURLOPT_MAXREDIRS, 3L);  /// 查找次数，防止查找太深
  /// 默认情况下完成一个任务以后, 出于重用连接的考虑不会马上关闭,
  /// 如果没有新的TCP请求来重用这个连接, 那么只能等到CLOSE_WAIT超时
  /// 这个时间默认在7200秒甚至更高, 太多的CLOSE_WAIT连接会导致性能问题
  curl_easy_setopt(_curl, CURLOPT_FORBID_REUSE, 1L);
  /// 返回的头部中有Location(一般直接请求的url没找到, 301/302跳转),
  /// 则继续请求Location对应的数据

  if (_session.skip) {
    curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
  }

  {
    static std::string type{};
    static std::string name{};
    static std::string pass{};
    static std::string cookie{};

    if (!cookie.empty()) {
      curl_easy_setopt(_curl, CURLOPT_COOKIE, cookie.c_str());  /// 设置cookie
    }

    // CURLAUTH_NTLM CURLAUTH_BASIC CURLAUTH_DIGEST CURLAUTH_ANY
    curl_easy_setopt(_curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    curl_easy_setopt(_curl, CURLOPT_USERNAME, name.c_str());
    curl_easy_setopt(_curl, CURLOPT_PASSWORD, pass.c_str());
  }
}

void HTTPClient::SetShareDNSCache(CURL *curl) {
  static CURLSH *shareHandle = nullptr;

  if (shareHandle == nullptr) {
    shareHandle = curl_share_init();

    /**
     *
     * curl_easy_perform每次执行时, 都会启动一个线程用于做DNS解析
     *
     * 每一个handle有一个DNS cache, 默认超时时间为60秒, 如果不重用handle的话,
     * 这个dns cache在连接完成后就被析构了
     *
     * 每一个handle执行前, 使用CURLOPT_SHARE选项把这个shareHandle设置给handle,
     * 这样多个handle就可以共用同一个DNS cache了
     *
     * 在超时时间内, 每次curl_easy_perform执行时不会再启动解析DNS的线程了,
     * 效率大大提高
     *
     */
    curl_share_setopt(shareHandle, CURLSHOPT_SHARE,
                      CURL_LOCK_DATA_DNS);  /// 设置共享DNS cache
  }

  curl_easy_setopt(curl, CURLOPT_SHARE, shareHandle);  /// 设置共享句柄
  curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 60 * 5);  /// 设置超时时间
}

void HTTPClient::ParseResponseCode() {
  if (curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &_response.code) !=
      CURLE_OK) {
    _response.code = 0;
  }
}

void HTTPClient::ParseResponseLength() {
  if (curl_easy_getinfo(_curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &_response.contentLength) == CURLE_OK) {
    if (_response.contentLength > 0) {
      _response.content.reserve(static_cast<std::size_t>(_response.contentLength));
    }
  } else {
    _response.contentLength = 0.0;
  }

  if (curl_easy_getinfo(_curl, CURLINFO_SIZE_DOWNLOAD, &_response.contentLengthZip) == CURLE_OK) {
    if (_response.contentLength > 0) {
      _response.content.reserve(static_cast<std::size_t>(_response.contentLengthZip));
    }
  } else {
    _response.contentLengthZip = 0.0;
  }

  char *host = NULL;
  curl_easy_getinfo(_curl, CURLINFO_PRIMARY_IP, &host);  // 获取ip
  _response.host = host;
}

bool HTTPClient::Launch(HTTP_OPTION_TYPE option) {
  std::lock_guard<std::mutex> lock(_mux);

  ++_session.count;

  if (!Initialize()) {
    return false;
  }

  SetProxy();
  SetSession(option);

  _errorCode = curl_easy_perform(_curl);
  if (_errorCode == CURLE_OK) {
    ++_session.successCount;
  } else {
    ++_session.failedCount;
  }

  if (_curl) {
    curl_easy_cleanup(_curl);

    _curl = nullptr;
  }

  return _errorCode == CURLE_OK;
}

std::size_t HTTPClient::WriteFunction(void *buffer, std::size_t size,
                                      std::size_t nmemb, void *stream) {
  auto count = nmemb * size;
  auto *client = reinterpret_cast<HTTPClient *>(stream);
  if (client == nullptr) {
    return count;
  }

  if (client->_isFirstWrite) {
    client->_isFirstWrite = false;
    client->ParseResponseCode();
    client->ParseResponseLength();
  }

  client->_response.content.append(reinterpret_cast<const char *>(buffer), count);

  return count;
}

std::size_t HTTPClient::HeaderFunction(void *buffer, std::size_t size,
                                       std::size_t nmemb, void *stream) {
  auto count = nmemb * size;
  auto *client = reinterpret_cast<HTTPClient *>(stream);

  if (client == nullptr) {
    return count;
  }

  client->_response.header.append(reinterpret_cast<const char *>(buffer), count);

  return count;
}

// 获取请求头
size_t HTTPClient::AskHeaderFunction(CURL *, curl_infotype type, void *buffer,
                                     size_t size, void *stream) {
  auto *client = reinterpret_cast<HTTPClient *>(stream);

  if (client == nullptr) {
    return size;
  }

  if (type == CURLINFO_HEADER_OUT)  // CURLINFO_TEXT  CURLINFO_HEADER_IN CURLINFO_DATA_IN CURLINFO_DATA_OUT
  {
    client->_response.askHeader.clear();
    client->_response.askHeader.append(reinterpret_cast<const char *>(buffer), size);
  }
  return size;
}
