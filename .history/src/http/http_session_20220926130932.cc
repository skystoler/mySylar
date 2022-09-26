#include "http_session.h"
#include "http_parser.h"

namespace sylar{
namespace http{

HttpSession::HttpSession(Socket::ptr sock,bool owner)
    :SocketStream(sock,owner){

}

HttpRequest::ptr HttpSession::recvRequest(){
    HttpRequestParser::ptr parser(new HttpRequestParser);
    //最大缓冲区长度
    uint64_t buffer_size=HttpRequestParser::GetHttpRequestBufferSize();
    std::shared_ptr<char> buffer(
            new char[buffer_size],[](char* ptr){
                delete [] ptr;
            });
    char* data=buffer.get();
    int offset=0;

    do{
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
        if(offset==(int)buffer_size){
            return nullptr;
        }
        if(parser->isFinished()){
            break;
        }
    }while(true);
    int64_t length=parser->getContentLength();
    if(length>0){
        std::string body;
        body.reserve(length);

        if(length>=offset){
            body.append(data,offset);
        }else{
            body.append(data,length);
        }
        length-=offset;
        if(length>0){
            if(readFixSize(&body[body.size()],length)<=0){
                return nullptr;
            }
        }
        parser->getData()->setBody(body);
    }
    return parser->getData();
}

int HttpSession::sendResponse(HttpResponse::ptr rsp){
    SYLAR_LOG_INFO(g_logger)<<"send response";
    std::stringstream ss;
    ss << *rsp;
    std::string data=ss.str();
    return writeFixSize(data.c_str(),data.size());
}

}
}