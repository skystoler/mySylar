#include "http_server.h"
#include "src/log.h"

namespace sylar{
namespace http{

HttpServer::HttpServer(bool keepalive,sylar::IOManager* worker,sylar::IOManager* accept_worker)
    :TcpServer(worker,accept_worker)
    ,m_isKeepalive(keepalive){

}

void HttpServer::handleClient(Socket::ptr client){
    sylar::http:HttpSession::ptr session(new HttpSession(client));
    do{
        auto req=session->recvRequest();
        if(!req){

        }
    }while(m_isKeepalive);
}


}
}