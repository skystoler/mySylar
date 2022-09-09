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
        return setOption(level,option,&value,sizeof(T));
    }

    Socket::ptr accept();

    bool bind(const Address::ptr addr);

    bool connect(const Address::ptr addr,uint64_t timeout_ms=-1);

    bool listen(int backlog=SOMAXCONN);

    bool close();

    bool send(const void* buffer,size_t length,int flags=0);
    bool send(const iovec* buffers,size_t length,int flags=0);
    bool sendTo(const void* buffer,size_t length,const Address::ptr to,int flags=0);
    bool sendTo(const iovec* buffers,size_t length,const Address::ptr to,int flags=0);

    bool recv(void* buffer,size_t length,int flags=0);
    bool recv(iovec* buffers,size_t length,int flags=0);
    bool recvFrom(void* buffer,size_t length,Address::ptr from,int flags=0);
    bool recvFrom(iovec* buffers,size_t length,Address::ptr from,int flags=0);

    Address::ptr getRemoteAddress();
    Address::ptr getLocalAddress();

    int getFamily() const;
    int getType() const;
    int getProtocol() const;

    bool isConnected() const;
    bool isValid() const;
    int getError();

    std::ostream& dump(std::ostream& os) const;
    int getSocket() const;

    bool cancelRead();
    bool cancelWrite();
    bool cancelAccept();
    bool cancelAll();

private:
    void initSock();
    void newSock();

private:
    int m_sock;
    int m_family;
    int m_type;
    int m_protocol;
    bool m_isConnected;

    Address::ptr m_localAddress;
    Address::ptr m_remoteAddress;
};

}

#endif