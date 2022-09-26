#ifndef __SYLAR_HTTP_HTTP_CONNECTION_H__
#define __SYLAR_HTTP_HTTP_CONNECTION_H__

#include "src/streams/socket_stream.h"
#include "http.h"

namespace sylar{
namespace http{

class HttpConnection:public SocketStream{

public:
    using ptr=std::shared_ptr<HttpConnection>;
    HttpConnection(Socket::ptr sock,bool owner=true);
    HttpResponse::ptr recvResponse();
    int sendRequest(HttpRequest::ptr req);

};

}
}

#endif