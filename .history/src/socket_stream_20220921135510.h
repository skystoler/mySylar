#ifndef __SYLAR_SOCKET_STREAM_H__
#define __SYLAR_SOCKET_STREAM_H__

#include "sttream.h"

namespace sylar{

class SocketStream : public Stream{
public:
    using ptr=std::shared_ptr<SocketStream>;
private:

};

}

#endif