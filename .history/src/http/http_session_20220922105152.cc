#include "http_session.h"
#include "http_parser.h"

namespace sylar{
namespace http{

HttpSeesion::HttpSeesion(Socket::ptr sock,bool owner)
    :SocketStream(sock,owner){

}

HttpRequest::ptr HttpSeesion::recvRequest(){
    HttpRequestParser::ptr parser(new HttpRequestParser);
    uint64_t buffer_size=HttpRequestParser::GetHttpRequestBufferSize();
    std::shared_ptr<char> buffer(
            new char[buffer_size],[](char* ptr){
                delete [] ptr;
            });
}

int HttpSeesion::sendResponse(HttpResponse::ptr rsp){
    
}

}
}