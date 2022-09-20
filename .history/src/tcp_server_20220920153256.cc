#include "tcp_server.h"
#include "config.h"


namespace sylar{

static sylar::ConfigVar<uint64_t>::ptr g_tcp_server_read_timeout=
    sylar::Config::Lookup("tcp_server.read_timeout",(uint64_t)(60*1000*2),"tcp server read timeout");

static sylar::Logger::ptr g_logger=SYLAR_LOG_NAME("system");

TcpServer::TcpServer(sylar::IOManager* worker)
    :m_worker(worker)
    ,m_readTimeout()
    ,m_name("sylar/1.0.0")
    ,m_stop(false){

}

bool TcpServer::bind(sylar::Address::ptr addr){
    std::vector<Address::ptr> addrs;
    addrs.push_back(addr);
    return bind(addrs);
}

bool TcpServer::bind(const std::vector<Address::ptr>& addrs
                        std::vector<Address::ptr>& fails){
    bool rt=true;
    for(auto& addr:addrs){
        Socket::ptr sock=Socket::CreateTcp(addr);
        if(!sock->bind(addr)){
            SYLAR_LOG_ERROR(g_logger)<<"bind fail errno: "
                <<errno<<" errstr="<<strerror(errno)
                <<" addr=[" <<addr->toString() <<"]";
            fails.push_back(addr);
            continue;
        }
        if(!sock->listen()){
        SYLAR_LOG_ERROR(g_logger)<<"bind fail errno: "
                <<errno<<" errstr="<<strerror(errno)
                <<" addr=[" <<addr->toString() <<"]";
        fails.push_back(addr);
        continue;
    }
    m_socks.push_back(sock);
    }
    
    return rt;
}

bool TcpServer::start(){

}

bool TcpServer::stop(){

}

void TcpServer::handleClient(Socket::ptr client);
}
