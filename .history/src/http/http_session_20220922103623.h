#ifndef __SYLAR_HTTP_SESSION_H__
#define __SYLAR_HTTP_SESSION_H__

#include "src/socket_stream.cc"
#include "http.h"

namespace sylar{

class HttpSeesion:public SocketStream{

public:
    using ptr=std::shared_ptr<SocketStream>;
    
};

}

#endif