#ifndef __SYLAR_HTTP_SERVER_H__
#define __SYLAR_HTTP_SERVER_H__

#include "src/tcp_server.h"
#include "http_session.h"

namespace syalr{
namespace http{

class HttpServer :public TcpServer{
public:
    using ptr=std::shared_ptr<HttpServer>;

protected:
    virtual void handleClient(Socket::ptr client) override;

private:
    bool m_isKeepalive;

};

}
}

#endif