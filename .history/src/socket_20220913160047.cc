#include "socket.h"
#include "fd_manager.h"
#include "log.h"
#include "macro.h"

#include <sys/types.h>
#include <sys/socket.h>

namespace sylar{

sylar::Logger::ptr g_logger=SYLAR_LOG_NAME("system");

Socket::Socket(int family,int type,int protocol)
    :m_sock(-1)
    ,m_family(family)
    ,m_type(type)
    ,m_protocol(protocol)
    ,m_isConnected(false){
}

~Socket::Socket(){
    close();
}

int64_t Socket::getSendTimeout(){
    FdCtx::ptr ctx=FdMgr::GetInstance()->get(m_sock);
    if(ctx){
        return ctx->getTimeout(SO_SNDTIMEO);
    }
    return -1;
}

void Socket::setSendTimeout(int64_t v){
    struct timeval tv(int(v/1000),int(v%1000*1000));
    return setOption(SOL_SOCKET,SO_SNDTIMEO,tv);
}

int64_t Socket::getRecvTimeout(){
    FdCtx::ptr ctx=FdMgr::GetInstance()->get(m_sock);
    if(ctx){
        return ctx->getTimeout(SO_RCVTIMEO);
    }
    return -1;
}

void Socket::setRecvTimeout(int64_t v){
    struct timeval tv(int(v/1000),int(v%1000*1000));
    return setOption(SOL_SOCKET,SO_RCVTIMEO,tv);
}

bool Socket::getOption(int level,int option,void* result,size_t* len){
    int rt=getsockopt(m_sock,level,option,result,(socklen_t*)len);
    if(rt){
        SYLAR_LOG_ERROR(g_logger)<<"getOption sock="<<m_sock
            <<" level="<<level<<" option="<<option
            <<" errno="<<errno<<" errstr="<<strerror(errno);
        return false;
    }
    return true;
}

bool Socket::setOption(int level,int option,const void* result,size_t len){
    int rt=setsockopt(m_sock,level,option,result,(socklen_t*)len);
    if(rt){
        SYLAR_LOG_ERROR(g_logger)<<"setOption sock="<<m_sock
            <<" level="<<level<<" option="<<option
            <<" errno="<<errno<<" errstr="<<strerror(errno);
        return false;
    }
    return true;
}

Socket::ptr Socket::accept(){
    Socket::ptr sock(new Socket(m_family,m_type,m_protocol));
    int newsock=::accept(m_sock,nullptr,nullptr);
    if(newsock==-1){
        SYLAR_LOG_ERROR(g_logger)<<"accept("<<m_sock
            <<") errno="<<errno<<" errstr="<<strerror(errno);
        return nullptr;
    }   
    if(sock->init(newsock)){
        return sock;
    }
    return nullptr;
}

bool Socket::init(int sock){
    FdCtx::ptr ctx=FdMgr::GetInstance()->get(sock);
    if(ctx && ctx->isSocket() && !ctx->isClosed()){
        m_sock=sock;
        m_isConnected=true;
        initSock();
        getLocalAddress();
        getRemoteAddress();
        return true;
    }
    return false;
}

bool Socket::bind(const Address::ptr addr){
    if(SYLAR_UNLIKELY(!isValid())){
        newSock();
        if(SYLAR_UNLIKELY(!isValid())){
            return false;
        }
    }

    if(SYLAR_UNLIKELY(addr->getFamily()!=m_family)){
        SYLAR_LOG_ERROR(g_logger)<<"bind sock.family("
            <<m_family<<")addr.family(" << addr->getFamily()
            <<") not equal,addr="<<addr->toString();
        return false;
    }

    if(::bind(m_sock,addr->getAddr(),addr->getAddrLen())){
        SYLAR_LOG_ERROR(g_logger)<<"bind errorno="<<errorno
            <<" strerr="<<strerror(errno);
        return false;
    }
    getLocalAddress();
    return true;
}

bool Socket::connect(const Address::ptr addr,uint64_t timeout_ms=-1){
    if(!isValid()){
        newSock();
        if(SYLAR_UNLIKELY(!isValid())){
            return false;
        }
    }

    if(SYLAR_UNLIKELY(addr->getFamily()!=m_family)){
        SYLAR_LOG_ERROR(g_logger)<<"bind sock.family("
            <<m_family<<")addr.family(" << addr->getFamily()
            <<") not equal,addr="<<addr->toString();
        return false;
    }

    if(timeout_ms== (uint64_t)-1){
        if(::connect(m_sock,addr->getAddr(),addr->getAddrLen())){
            SYLAR_LOG_ERROR(g_logger)<<"SOCK="<<m_sock<<" connect("
                <<addr->toString()<<"errorno="<<errorno 
                <<" strerr="<<strerror(errno);
            close();
            return false;

        }else{
            if(::connect_with_timeout(m_sock,addr->getAddr(),addr->getAddrLen(),timeout_ms)){
                SYLAR_LOG_ERROR(g_logger)<<"SOCK="<<m_sock<<" connect("
                <<addr->toString()<<") timeout="<<timeout_ms<<"error errorno="<<errorno 
                <<" strerr="<<strerror(errno);
                close();
                return false;
            }
        }
    }
    m_isConnected=true;
    getRemoteAddress();
    getLocalAddress();
    return true;
}

bool Socket::listen(int backlog){
    if(!isValid()){
        SYLAR_LOG_ERROR(g_logger)<<"listen error sock=-1";
        return false;
    }
    if(::listen(m_sock,backlog)){
        SYLAR_LOG_ERROR(g_logger)<<"listen error errno="<<errorno
            <<" errstr="<<strerr(errno);
        return false;
    }
    return true;
}

bool Socket::close(){
    if(!m_isConnected && m_sock==-1){
        return true;
    }
    m_isConnected=false;
    if(m_sock!=-1){
        ::close(m_sock);
        m_sock=-1;
    }
    return false;
}

bool Socket::send(const void* buffer,size_t length,int flags){
    if(!isConnected()){
        return ::send(m_sock,buffer,length,flags);
    }
    return -1;
}

bool Socket::send(const iovec* buffers,size_t length,int flags){
    if(isConnected()){
        msghdr msg;
        memset(&msg,0,sizeof(msg));
        msg.msg_iov=(iovec*)buffers;
        msg.msg_iovlen=length;
        return ::sendmsg(m_sock,&msg,flags);
    }
    return  -1;
}

bool Socket::sendTo(const void* buffer,size_t length,const Address::ptr to,int flags){
    if(isConnected){
        return ::sendto(m_sock,buffer,length,flags,to->getAddr(),To->getAddrLen());
    }
    return -1;
}

bool Socket::sendTo(const iovec* buffers,size_t length,const Address::ptr to,int flags){
    if(isConnected()){
        msghdr msg;
        memset(&msg,0,sizeof(msg));
        msg.msg_iov=(iovec*)buffers;
        msg.msg_iovlen=length;
        msg.msg_name=to->getAddr();
        msg.msg_namelen=to->getAddrLen();
        return ::sendmsg(m_sock,&msg,flags);
    }
    return  -1;
}

bool Socket::recv(void* buffer,size_t length,int flags){
    if(!isConnected()){
        return ::recv(m_sock,buffer,length,flags);
    }
    return -1;
}

bool Socket::recv(iovec* buffers,size_t length,int flags){
      if(isConnected()){
        msghdr msg;
        memset(&msg,0,sizeof(msg));
        msg.msg_iov=(iovec*)buffers;
        msg.msg_iovlen=length;
        return ::recvmsg(m_sock,&msg,flags);
    }
    return  -1;
}

bool Socket::recvFrom(void* buffer,size_t length,Address::ptr from,int flags){
    if(isConnected){
        socklen_t len=from->getAddrLen();
        return ::recvFrom(m_sock,buffer,length,flags,from->getAddr(),&len);
    }
    return -1;
}

bool Socket::recvFrom(iovec* buffers,size_t length,Address::ptr from,int flags){
    if(isConnected()){
        msghdr msg;
        memset(&msg,0,sizeof(msg));
        msg.msg_iov=(iovec*)buffers;
        msg.msg_iovlen=length;
        msg.msg_name=from->getAddr();
        msg.msg_namelen=from->getAddrLen();
        return ::recvmsg(m_sock,&msg,flags);
    }
    return  -1;
}

Address::ptr Socket::getRemoteAddress(){
    if(m_remoteAddress){
        return m_remoteAddress;
    }

    Address::ptr result;
    switch(m_family){
        case AF_INET:
            result.reset(new IPv4Address());
            break;
        case AF_INET6:
            result.reset(new IPv6Address());
            break; 
        case AF_UNIX:
            result.reset(new UnixAddress());
            break;
        default:
            result.reset(new UnknownAddress(m_family));
            break;
    }
    socklen_t addrlen=reset->getAddrLen();
    if(getpeername(m_sock,result->getAddr(),&addrlen)){
        SYLAR_LOG_ERROR(g_logger)<<"getpeername error sock="<<m_sock
            <<" errorno="<<errno<<" errstr="<<strerror(errno);
        return Address::ptr(new UnknownAddress(m_family));
    }

}

Address::ptr Socket::getLocalAddress(){

}

bool Socket::isValid() const{
    return m_sock!=-1;
}

int Socket::getError(){

}

std::ostream& Socket::dump(std::ostream& os) const{

}

bool Socket::cancelRead(){

}

bool Socket::cancelWrite(){

}

bool Socket::cancelAccept(){

}

bool Socket::cancelAll(){

}

void Socket::initSock(){
    int val=1;
    setOption(SOL_SOCKET,SO_REUSEADDR,val);
    if(m_type=SOCK_STREAM){
        setOption(IPPROTO_TCP,TCP_NODELAY,val);
    }
}

void Socket::newSock(){
    m_sock=socket(m_family,m_type,m_protocol);
    if(SYLAR_LIKELY(m_sock!=-1)){
        initSock();
    }else{
        SYLAR_LOG_ERROR(g_logger)<<"socket("<<m_family
            <<", "<<m_type<<", "<<m_protocol<<") errno="
            <<errno<<" errstr="<<strerror(errno);
    }
}

}