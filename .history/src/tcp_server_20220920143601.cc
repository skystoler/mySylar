#include "tcp_server.h"

namespace sylar{
TcpServer::TcpServer(sylar::IOManager* worker)
    :m_worker(worker)
    ,m_readTimeout()
    ,m_name("sylar/1.0.0")
    ,m_stop(false){

}

virtual ~TcpServer::TcpServer(){

}

virtual bool bind(sylar::Address::ptr addr){

}

virtual bool bind(const std::vector<Address::ptr>& addrs){

}

virtual bool start(){

}

virtual bool stop(){

}

uint64_t getReadTimeout() const {return m_readTimeout;}
std::string getNmae() const {return m_name;}
void serReadTimeout(uint64_t v){m_readTimeout=v;}
void setName(std::string& v){m_name=v;}

bool isStop() const{return m_isStop;}

virtual void handleClient(Socket::ptr client);
}
