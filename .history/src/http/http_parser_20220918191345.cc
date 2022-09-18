#include "http_parser.h"

namespace sylar{

namespace http{

HttpRequestParser::HttpRequestParser(){
    http_parser_init(m_parser);
}

size_t HttpRequestParser::excute(const char* data,size_t length,size_t off){

}

int HttpRequestParser::isFinished() const{

}

int HttpRequestParser::hasError() const{

}

HttpResponseParser::HttpResponseParser(){

}

size_t HttpResponseParser::excute(const char* data,size_t length,size_t off){

}

int HttpResponseParser::isFinished() const{

}

int HttpResponseParser::hasError() const{

}

}

}