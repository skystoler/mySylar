#include <iostream>
#include "src/http/http_connection.h"
#include "src/log.h"

static sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();

void run(){
    sylar::Address::ptr addr=sylar::Address::LookupAnyAddress("www.sylar.top:80");
    if(!addr){
        SYLAR_LOG_INFO(g_logger)<<"get addr error";
        return;
    }

    sylar::Socket::ptr sock=sylar::Socket::CreateTcp(addr);
    bool rt=sock->connect(addr);
    if(!rt){
        SYLAR_LOG_INFO(g_logger)<<"connect "<<addr<<" failed";
        return;
    }

    sylar::http::HttpConnection::ptr req(new sylar::http:HttpRequest);
}

int main(int argc,char** argv){
    sylar::IOManager::ptr iom(2);
    iom.schedule(run);
    return 0;
}