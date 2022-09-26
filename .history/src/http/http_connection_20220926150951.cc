#include "http_connection.h"
#include "http_parser.h"

namespace sylar{
namespace http{

HttpConnection::HttpConnection(Socket::ptr sock,bool owner)
    :SocketStream(sock,owner){

}

HttpResponse::ptr HttpConnection::recvResponse(){
    HttpResponseParser::ptr parser(new HttpResponseParser);
    //最大缓冲区长度
    uint64_t buffer_size=HttpResponseParser::GetHttpResponseBufferSize();
    std::shared_ptr<char> buffer(
            new char[buffer_size + 1],[](char* ptr){
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
        data[len]='\0';
        //实际解析长度nparse
        size_t nparse=parser->execute(data,len,false);
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
    auto client_parser=parser->getParser();
    if(client_parser.chuncked){
        std::string body;
        int len=offset;
        do{
            do{
                int rt=read(data+len,buffer_size-len);
                if(rt<=0){
                    return nullptr;
                }
                len+=rt;
                size_t nparse=parser->execute(data,len,true);
                if(parser->hasError()){
                    return nullptr;
                }
                len-=nparse;
                if(len==(int)buffer_size){
                    return nullptr;
                }
            }while(!parser->isFinished());
            if(client_parser.content_len<=len){
                body.append(data,client_parser.content_len);
                memmove(data,data+client_parser.content_len
                        ,len-client_parser.content_len);
                len-=client_parser.content_len;
            }else{
                body.append(data,len);
                len=0;
                int left=client_parser.content_len-len;
                while(left>0){
                    int rt=read(data,left>buffer_size ? buffer_size:left);
                    if(rt<=0){
                        return nullptr;
                    }
                    body.append(data,rt);
                    left-=rt;
                }
                len=0;
            }
        }while(!client_parser.chunks_done);
    }else{
        int64_t length=parser->getContentLength();
        if(length>0){
            std::string body;
            body.resize(length);

            int len=0;

            if(length>=offset){
                memcpy(&body[0],data,offset);
                len=offset;
            }else{
                memcpy(&body[0],data,length);
                len=length;
            }
            length-=offset;
            if(length>0){
                if(readFixSize(&body[len],length)<=0){
                    return nullptr;
                }
            }
            parser->getData()->setBody(body);
        }
    }

    return parser->getData();
}

int HttpConnection::sendRequest(HttpRequest::ptr rsp){
    //SYLAR_LOG_INFO(g_logger)<<"send request";
    std::stringstream ss;
    ss << *rsp;
    std::string data=ss.str();
    return writeFixSize(data.c_str(),data.size());
}

}
}