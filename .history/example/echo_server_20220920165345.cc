#include "src/tcp_server.h"
#include "src/log.h"
#include "src/iomanager.h"

class EchoServer:public sylar::TcpServer{
public:
    EchoServer(int type);
    void handleClient(Socket::ptr client);
};

int main(int argc,char** argv){
    return 0;
}