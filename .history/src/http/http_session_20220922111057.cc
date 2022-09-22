#include "http_session.h"
#include "http_parser.h"

namespace sylar{
namespace http{

HttpSeesion::HttpSeesion(Socket::ptr sock,bool owner)
    :SocketStream(sock,owner){

}

HttpRequest::ptr HttpSeesion::recvRequest(){
    HttpRequestParser::ptr parser(new HttpRequestParser);
    //最大缓冲区长度
    uint64_t buffer_size=HttpRequestParser::GetHttpRequestBufferSize();
    std::shared_ptr<char> buffer(
            new char[buffer_size],[](char* ptr){
                delete [] ptr;
            });
    char* data=buffer.get();
    int offset=0;

retry:
    //读到的数据长度len
    int len=read(data+offset,buffer_size-offset);
    if(len<=0){
        return nullptr;
    }
    len+=offset;
    //实际解析长度nparse
    size_t nparse=parser->execute(data,len);
    if(parser->hasError()){
        return nullptr;
    }
    offset=len-nparse;
    if(offset==buffer_size){
        return nullptr;
    }
    if(parser->isFinished()){

    }else{
        goto retry;
    }
}

int HttpSeesion::sendResponse(HttpResponse::ptr rsp){
    
}

}
}