#include "src/tcp_server.h"
#include "src/log.h"
#include "src/iomanager.h"

class EchoServer:public TcpServer{
public:

    virtual ~TcpServer() override;
    virtual bool bind(sylar::Address::ptr addr) override;
    virtual bool bind(const std::vector<Address::ptr>& addrs
                        ,std::vector<Address::ptr>& fails) override;
    virtual bool start() override;
    virtual void stop() override;

protected:
    virtual void handleClient(Socket::ptr client) override;
    virtual void startAccept(Socket::ptr sock) override; 
private:

};

int main(int argc,char** argv){
    return 0;
}