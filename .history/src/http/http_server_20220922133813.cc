#include "http_server.h"

namespace sylar{
namespace http{

HttpServer::HttpServer(bool keepalive,sylar::IOManager* worker,sylar::IOManager* accept_worker)
    :TcpServer(worker,accept_worker)
    ,m_isKeepalive(keepalive){

}

void HttpServer::handleClient(Socket::ptr client){

}


}
}