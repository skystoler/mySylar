#include "src/tcp_server.h"
#include "src/log.h"
#include "src/iomanager.h"
#include "src/bytearray.h"

static sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();

class EchoServer:public sylar::TcpServer{
public:
    EchoServer(int type);
    void handleClient(Socket::ptr client);
private:
    int m_type=0;
};

EchoServer::EchoServer(int type)
    :m_type(type){

}

void EchoServer::handleClient(Socket::ptr client){
    SYLAR_LOG_INFO(g_logger)<<"handleClient "<<*client;
    sylar::ByteArray::ptr ba(new sylar::ByteArray);
    while(true){    
        ba->clear();
        std::vector<iovec> iovs;
        
    }
}

int main(int argc,char** argv){
    return 0;
}