#include "http.h"

namespace sylar{
namespace http{

HttpMethod StringToHttpMethod(const std::string& m){
#define XX(num,name,string) \
    if(strcmp(#string,m.c_str()) == 0 ){ \
        return HttpMethod::name; \
    }
    HTTP_METHOD_MAP(XX)
#undef XX
    return HttpMethod::INVALID_METHOD;
}

HttpMethod CharsToHttpMethod(const char* m){
#define XX(num,name,string) \
    if(strcmp(#string,m) == 0 ){ \
        return HttpMethod::name; \
    }
    HTTP_METHOD_MAP(XX)
#undef XX
    return HttpMethod::INVALID_METHOD;
}

static const char* s_method_string[]={
#define XX(num, name, string) #string,
    HTTP_METHOD_MAP(XX)
#undef XX
};

const char* HttpMethodToString(const HttpMethod& m){
    uint32_t idx = (uint32_t)m;
    if(idx >= (sizeof(s_method_string) / sizeof(s_method_string[0]))) {
        return "<unknown>";
    }
    return s_method_string[idx];
}

const char* HttpStatusToString(const HttpStatus& m){
switch(s) {
#define XX(code, name, msg) \
        case HttpStatus::name: \
            return #msg;
        HTTP_STATUS_MAP(XX);
#undef XX
        default:
            return "<unknown>";
    }
}


bool CaseInensitiveLessoperator() (const std::string& lhs
                ,const std::string& rhs) const{
    return strcasecmp(lhs.c_str(),rhs.c_str()) < 0;
}
http::HttpRequest(uint8_t version=0x11,bool close=true);

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
}