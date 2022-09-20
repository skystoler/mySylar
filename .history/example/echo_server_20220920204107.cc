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
        ba->getWriteBuffers(iovs,1024);

        int rt=client->recv(&iovs[0],iovs.size());
        if(rt==0){
            SYLAR_LOG_INFO(g_logger)<<"client close"<<*client;
            break;
        }else if(rt<0){
            SYLAR_LOG_INFO(g_logger)<<"client error rt="<<rt
                <<" errno="<<errno<<" errstr="<<strerror(errno);
            break;
        }
        //rt>0表示已经读到一部分数据了，那么重设初始位置
        ba->setPosition(ba->getPosition()+rt);
        //为了tostring全部输出出来
        ba->setPosition(0);
        if(m_type==1){//text
            SYLAR_LOG_INFO(g_logger)<<ba->toString();
        }else{
            SYLAR_LOG_INFO(g_logger)<<ba->toHexString();
        }
    }
}

void run(){

}

int main(int argc,char** argv){
    sylar::IOManager iom(2);
    iom.schedule(&run);
    return 0;
}