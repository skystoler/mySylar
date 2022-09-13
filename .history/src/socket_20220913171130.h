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

class Socket:public std::enable_shared_from_this<Socket>,Noncopyable {
public:
    using ptr=std::shared_ptr<Socket>;
    using weak_ptr=std::weak_ptr<Socket>;

    Socket(int family,int type,int protocol=0);
    virtual ~Socket();

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

    virtual Socket::ptr accept();

    virtual bool bind(const Address::ptr addr);

    virtual bool reconnect(uint64_t timeout_ms=-1);

    virtual bool connect(const Address::ptr addr,uint64_t timeout_ms=-1);

    virtual bool listen(int backlog=SOMAXCONN);

    virtual bool close();

    virtual int send(const void* buffer,size_t length,int flags=0);
    virtual int send(const iovec* buffers,size_t length,int flags=0);
    virtual int sendTo(const void* buffer,size_t length,const Address::ptr to,int flags=0);
    virtual int sendTo(const iovec* buffers,size_t length,const Address::ptr to,int flags=0);

    virtual int recv(void* buffer,size_t length,int flags=0);
    virtual int recv(iovec* buffers,size_t length,int flags=0);
    virtual int recvFrom(void* buffer,size_t length,Address::ptr from,int flags=0);
    virtual int recvFrom(iovec* buffers,size_t length,Address::ptr from,int flags=0);

    Address::ptr getRemoteAddress();
    Address::ptr getLocalAddress();

    int getFamily() const {return m_family;}
    int getType() const {return m_type;}
    int getProtocol() const {return m_protocol;}

    bool isConnected() const {return m_isConnected;}
    bool isValid() const;
    int getError();

    virtual std::ostream& dump(std::ostream& os) const;

    //virtual std::string toString() const;

    int getSocket() const {return m_sock;}

    bool cancelRead();
    bool cancelWrite();
    bool cancelAccept();
    bool cancelAll();

private:
    void initSock();
    void newSock();

    virtual bool init(int sock);
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