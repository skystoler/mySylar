#ifndef __SYLAR_HTTP_PARSER_H__
#define __SYLAR_HTTP_PARSER_H__

#include "http.h"
#include "http11_parser.h"
#include "httpclient_parser.h"
namespace sylar{

namespace http{

class HttpRequestParser{
public:
    using ptr=std::shared_ptr<HttpRequestParser>;
    HttpRequestParser();

    size_t excute(const char* data,size_t length);
    int isFinished() const;
    int hasError() const;

    HttpRequest::ptr getData() const{return m_data;}
    void setError(int v){m_error=v;}
private:
    http_parser m_parser;
    HttpRequest::ptr m_data;
    //1000: invalid method
    //1001: invalid version
    //1002: invalid field
    int m_error;
};

class HttpResponseParser{
public:
    using ptr=std::shared_ptr<HttpRequestParser>;
    HttpResponseParser();

    size_t excute(const char* data,size_t length);
    int isFinished() const;
    int hasError() const;

    HttpResponse::ptr getData() const{return m_data;}
private:
    httpclient_parser m_parser;
    HttpResponse::ptr m_data;

    int m_error;
};

}


}


#endif