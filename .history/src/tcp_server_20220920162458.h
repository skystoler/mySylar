#ifndef __SYLAR_TCP_SERVER_H__
#define __SYLAR_TCP_SERVER_H__


#include <memory>
#include <functional>
#include "iomanager.h"
#include "socket.h"
#include "noncopyable.h"
#include "address.h"

namespace sylar{

class TcpServer:public std::enable_shared_from_this<TcpServer>
                    ,Noncopyable{
public:
    using ptr=std::shared_ptr<TcpServer>;

    TcpServer(sylar::IOManager* worker=sylar::IOManager::GetThis()
            ,sylar::IOManager* accept_worker=sylar::IOManager::GetThis());
    virtual ~TcpServer();
    virtual bool bind(sylar::Address::ptr addr);
    virtual bool bind(const std::vector<Address::ptr>& addrs
                        ,std::vector<Address::ptr>& fails);
    virtual bool start();
    virtual void stop();

    uint64_t getReadTimeout() const {return m_readTimeout;}
    std::string getNmae() const {return m_name;}
    void serReadTimeout(uint64_t v){m_readTimeout=v;}
    void setName(std::string& v){m_name=v;}

    bool isStop() const{return m_isStop;}
protected:
    virtual void handleClient(Socket::ptr client);
    virtual void startAccept(Socket::ptr sock);
private:
    std::vector<Socket::ptr> m_socks;
    IOManager* m_worker;
    IOManager* m_acceptWorker;
    uint64_t m_readTimeout;
    std::string m_name;
    bool m_isStop;
};

}
#endif