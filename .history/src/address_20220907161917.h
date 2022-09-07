#ifndef __SYLAR_ADDRESS_H__
#define __SYLAR_ADDRESS_H__

#include <memory>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>

namespace sylar{

class Addreess{
public:
    using ptr=shared_ptr<Addreess>;
    virtual ~Addreess(){}

    int getFamily() const;

    virtual const sockaddr* getAddr() const=0;
    virtual socklen_t getAddrLen() const=0;

    virtual std::ostream& insert(std::ostream& os) const=0;
    
    std::string toString();

    bool operator<(const Addreess& rhs) const;
    bool operator==(const Addreess& rhs) const;
    bool operator!=(const Addreess& rhs) const;
};

class IPAddress:public Addreess{
public:
    using ptr=shared_ptr<IPAddress>;

    virtual IPAddress::ptr broadcastAddress(uint32_t prefix_len)=0;
    virtual IPAddress::ptr networkAddress(uint32_t prefix_len)=0;
    virtual IPAddress::ptr subnerMask(uint32_t prefix_len)=0;

    virtual uint32_t getPort() const=0;
    virtual void setPort(uint32_t v)=0;
};

class IPv4Address:public IPAddress{
public:
    using ptr=shared_ptr<IPAddress>;

    IPv4Address(uint32_t address=INADDR_ANY,uint32_t port=0);

    
    const sockaddr* getAddr() const override;
    socklen_t getAddrLen() const override;
    std::ostream& insert(std::ostream& os) const override;

    IPAddress::ptr broadcastAddress(uint32_t prefix_len) override;
    IPAddress::ptr networkAddress(uint32_t prefix_len) override;
    IPAddress::ptr subnerMask(uint32_t prefix_len) override;

    uint32_t getPort() const override;
    void setPort(uint32_t v) override;
private:
    sockaddr_in m_addr;
};

class IPv6 Address:public IPAddress{
public:
    using ptr=shared_ptr<IPAddress>;

    IPv4Address(uint32_t address=INADDR_ANY,uint32_t port=0);

    
    const sockaddr* getAddr() const override;
    socklen_t getAddrLen() const override;
    std::ostream& insert(std::ostream& os) const override;

    IPAddress::ptr broadcastAddress(uint32_t prefix_len) override;
    IPAddress::ptr networkAddress(uint32_t prefix_len) override;
    IPAddress::ptr subnerMask(uint32_t prefix_len) override;

    uint32_t getPort() const override;
    void setPort(uint32_t v) override;
private:
    sockaddr_in m_addr;
};

#endif