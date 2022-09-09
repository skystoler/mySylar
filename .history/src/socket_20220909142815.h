#ifndef __SYLAR_SOCKET_H__
#define __SYLAR_SOCKET_H__

#include <memory>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include "address.h"
#include "noncopyable.h"

namespace sylar {

class Socket:public std::enabled_shared_from_this<Socket>,Noncopyable {
public:
    using ptr=std::shared_ptr<Socket>;
    using weak_ptr=std::weak_ptr<Socket>;

    Socket(int family,int type,int protocol=0);
    ~Socket();

    int64_t getSendTimeout();
    void setSendTimeout(int64_t v);

    int64_t getRecvTimeout();
    void setRecvTimeout(int64_t v);

    bool getOption(int level,int option,void* result,size_t* len);

    template<class T>
    bool getOption(int level,int option,T* result){
        size_t length=sizeof(T);
        return getOption(level,option,&result,&length);
    }

    bool setOption(int level,int option,const void* result,size_t len);
    template<class T>
    bool setOption(int level,int option,const T& value){
        return setOption(level,option,&result,sizeof(T));
    }

priavte:

}

}