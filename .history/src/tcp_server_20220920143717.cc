#include "tcp_server.h"
#include "config.h"

namespace sylar{

static sylar::ConfigVar<>
TcpServer::TcpServer(sylar::IOManager* worker)
    :m_worker(worker)
    ,m_readTimeout()
    ,m_name("sylar/1.0.0")
    ,m_stop(false){

}

TcpServer::~TcpServer(){

}

bool TcpServer::bind(sylar::Address::ptr addr){

}

bool TcpServer::bind(const std::vector<Address::ptr>& addrs){

}

bool TcpServer::start(){

}

bool TcpServer::stop(){

}

void TcpServer::handleClient(Socket::ptr client);
}
