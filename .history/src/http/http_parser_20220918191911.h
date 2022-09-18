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

    size_t excute(const char* data,size_t length,size_t off);
    int isFinished() const;
    int hasError() const;
private:
    http_parser m_data;
    HttpRequest::ptr m_request;
    int m_error;
};

class HttpResponseParser{
public:
    using ptr=std::shared_ptr<HttpRequestParser>;
    HttpResponseParser();

    size_t excute(const char* data,size_t length,size_t off);
    int isFinished() const;
    int hasError() const;
private:
    httpclient_parser m_data;
    HttpResponse::ptr m_response;
    int m_error;
};

}


}


#endif