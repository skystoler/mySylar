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

    //通过sockaddr指针创建Address
    static Address::ptr Create(const sockaddr* addr,socklen_t addrlen);

    //通过host地址返回对应条件的任意Address
    static bool Lookup(std::vector<Address::ptr>& result,const std::string& host,
            int family=AF_UNSPEC,int type=0,int protocol=0);

    //过host地址返回对应条件的任意IPAddress
    static std::shared_ptr<IPAddress> LookupAnyIPAddress(const std::string& host,
            int family = AF_INET, int type = 0, int protocol = 0);

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

    //通过域名,IP,服务器名创建IPAddress
    static IPAddress::ptr Create(const char* address,uint32_t port=0);

    //获取该地址的广播地址
    virtual IPAddress::ptr broadcastAddress(uint32_t prefix_len)=0;

    //获取该地址的网段
    virtual IPAddress::ptr networkAddress(uint32_t prefix_len)=0;

    //获取子网掩码地址
    virtual IPAddress::ptr subnetMask(uint32_t prefix_len)=0;

    virtual uint32_t getPort() const=0;
    virtual void setPort(uint32_t v)=0;
};

class IPv4Address:public IPAddress{
public:
    using ptr=std::shared_ptr<IPAddress>;

    //使用点分十进制地址创建IPv4Address
    static IPv4Address::ptr Create(const char* address,uint32_t port=0);

    //通过sockaddr_in构造IPv4Address
    IPv4Address(const sockaddr_in& address);

    //通过二进制地址构造IPv4Address
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

    //通过IPv6地址字符串构造IPv6Address
    static IPv6Address::ptr Create(const char* address,uint32_t port=0);

    IPv6Address();

    //通过sockaddr_in6构造IPv6Address
    IPv6Address(const sockaddr_in6& address);

    //通过二进制地址构造IPv6Address
    IPv6Address(const uint8_t address[16],uint32_t port=0);

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
    UnknownAddress(const sockaddr& addr);
    const sockaddr* getAddr() const override;
    socklen_t getAddrLen() const override;
    std::ostream& insert(std::ostream& os) const override;
private:
    sockaddr m_addr;
};

}
#endif