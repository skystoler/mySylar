#include "http.h"

namespace sylar{

    HttpRequest(uint8_t version=0x11,bool close=true);

    std::string getHeader(const std::string& key, const std::string& def = "") const;
    std::string getParam(const std::string& key, const std::string& def = "");
    std::string getCookie(const std::string& key, const std::string& def = "");

    void setHeader(const std::string& key, const std::string& val);
    void setParam(const std::string& key, const std::string& val);
    void setCookie(const std::string& key, const std::string& val);

    void delHeader(const std::string& key);
    void delParam(const std::string& key);
    void delCookie(const std::string& key);

    bool hasHeader(const std::string& key, std::string* val = nullptr);
    bool hasParam(const std::string& key, std::string* val = nullptr);
    bool hasCookie(const std::string& key, std::string* val = nullptr);
}