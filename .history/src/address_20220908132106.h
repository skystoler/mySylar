#ifndef __SYLAR_ADDRESS_H__
#define __SYLAR_ADDRESS_H__

#include <memory>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <map>

namespace sylar{

class Address{
public:
    using ptr=std::shared_ptr<Address>;
    virtual ~Address(){}

    int getFamily() const;

    virtual const sockaddr* getAddr() const=0;
    virtual socklen_t getAddrLen() const=0;

    virtual std::ostream& insert(std::ostream& os) const=0;
    
    std::string toString() const;

    bool operator<(const Address& rhs) const;
    bool operator==(const Address& rhs) const;
    bool operator!=(const Address& rhs) const;
};

class IPAddress:public Address{
public:
    using ptr=std::shared_ptr<IPAddress>;

    virtual IPAddress::ptr broadcastAddress(uint32_t prefix_len)=0;
    virtual IPAddress::ptr networkAddress(uint32_t prefix_len)=0;
    virtual IPAddress::ptr subnetMask(uint32_t prefix_len)=0;

    virtual uint32_t getPort() const=0;
    virtual void setPort(uint32_t v)=0;
};

class IPv4Address:public IPAddress{
public:
    using ptr=std::shared_ptr<IPAddress>;

    IPv4Address(const sockaddr_in& address);
    IPv4Address(uint32_t address=INADDR_ANY,uint32_t port=0);

    const sockaddr* getAddr() const override;
    socklen_t getAddrLen() const override;
    std::ostream& insert(std::ostream& os) const override;

    IPAddress::ptr broadcastAddress(uint32_t prefix_len) override;
    IPAddress::ptr networkAddress(uint32_t prefix_len) override;
    IPAddress::ptr subnetMask(uint32_t prefix_len) override;

    uint32_t getPort() const override;
    void setPort(uint32_t v) override;
private:
    sockaddr_in m_addr;
};

class IPv6Address:public IPAddress{
public:
    using ptr=std::shared_ptr<IPAddress>;

    IPv6Address();
    IPv6Address(const char* address,uint32_t port=0);

    const sockaddr* getAddr() const override;
    socklen_t getAddrLen() const override;
    std::ostream& insert(std::ostream& os) const override;

    IPAddress::ptr broadcastAddress(uint32_t prefix_len) override;
    IPAddress::ptr networkAddress(uint32_t prefix_len) override;
    IPAddress::ptr subnetMask(uint32_t prefix_len) override;

    uint32_t getPort() const override;
    void setPort(uint32_t v) override;
private:
    sockaddr_in6 m_addr;
};

class UnixAddress:public Address{
public:
    using ptr=std::shared_ptr<IPAddress>;

    UnixAddress();
    UnixAddress(const std::string& path);

    const sockaddr* getAddr() const override;
    socklen_t getAddrLen() const override;
    std::ostream& insert(std::ostream& os) const override;

private:
    struct sockaddr_un m_addr;
    socklen_t m_length;
};

class UnknownAddress:public Address{
public:
    using ptr=std::shared_ptr<IPAddress>;

    UnknownAddress(int family);
    const sockaddr* getAddr() const override;
    socklen_t getAddrLen() const override;
    std::ostream& insert(std::ostream& os) const override;
private:
    sockaddr m_addr;
};

}
#endif