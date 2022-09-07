#include "address.h"
#include "endian.h"
#include <sstream>

namespace sylar{

int Address::getFamily() const{
    return getAddr()->sa_family;
}

std::string Address::toString(){
    std::stringstream ss;
    insert(ss);
    return ss.str();
}

bool Address::operator<(const Addreess& rhs) const{
    socklen_t minlen=std::min(getAddrLen(),rhs.getAddrLen());
    int result=memcmp(getAddr(),rhs.getAddr(),min_len);
    if(result<0){
        return true;
    }else if(result>0){
        return false;
    }else if(getAddrLen()<rhs.getAddrLen()){
        return true;
    }
    return false;
}

bool Address::operator==(const Addreess& rhs) const{
    return getAddrLen()==rhs.getAddrLen()
        && memcmp(getAddr(),rhs.getAddr(),getAddrLen())==0;
}

bool Address::operator!=(const Addreess& rhs) const{
    return !(*this == rhs);
}

IPv4Address::IPv4Address(uint32_t address,uint32_t port){
    memset(&m_addr,0,sizeof(m_addr));
    m_addr.sin_family=AF_INET;
    m_addr.sin_port=byteswapOnLittleEndian(port);
    m_addr.sin_addr.s_addr=byteswapOnLittleEndian(address);
}

const sockaddr* IPv4Address::getAddr() const{
    return (sockaddr*)&m_addr;
}

socklen_t IPv4Address::getAddrLen() const{
    return sizeof(m_addr);
}

std::ostream& IPv4Address::insert(std::ostream& os) const{
    uint32_t addr=byteswapOnLittleEndian(m_sin.sin_addr.s_addr);
    os  <<(addr>>24) & 0xff << "."
        <<(addr>>16) & 0xff << "."
        <<(addr>>8) & 0xff << "."
        <<(addr) & 0xff ;
    os  << ":" << byteswapOnLittleEndian(m_sin.sin_port);
    return os;
}

IPAddress::ptr IPv4Address::broadcastAddress(uint32_t prefix_len){
    if(prefix_len>32){
        return nullptr;
    }

    sockaddr_in baddr(m_addr);
    baddr.sin_addr.s_addr
}
IPAddress::ptr IPv4Address::networkAddress(uint32_t prefix_len){

}
IPAddress::ptr IPv4Address::subnetMask(uint32_t prefix_len){
    
}

uint32_t IPAddress::getPort() const{
    return byteswapOnLittleEndian(m_addr.sin_port);
}

void IPAddress::setPort(uint32_t v){
    m_addr.sin_port=byteswapOnLittleEndian(v);
}

IPv6Address::IPv6Address(const char* address,uint32_t port){
    memset(&m_addr,0,sizeof(m_addr));
    m_addr.sin6_family=AF_INET;
    m_addr.sin6_port=byteswapOnLittleEndian(port);
    memcpy(&m_addr.sin6_addr.s6_addr,address,16);
    m_addr.sin_addr.s_addr=byteswapOnLittleEndian(address);
}

const sockaddr* IPv6Address::getAddr() const{

}
socklen_t IPv6Address::getAddrLen() const{

}

std::ostream& IPv6Address::insert(std::ostream& os) const{

}

IPAddress::ptr IPv6Address::broadcastAddress(uint32_t prefix_len){

}
IPAddress::ptr IPv6Address::networkAddress(uint32_t prefix_len){

}
IPAddress::ptr IPv6Address::subnetMask(uint32_t prefix_len){
    
}

uint32_t IPv6Address::getPort() const{
    return byteswapOnLittleEndian(m_addr.sin_port);
}

void IPv6Address::setPort(uint32_t v){
    m_addr.sin_port=byteswapOnLittleEndian(v);
}


UnixAddress::UnixAddress(const std::string& path){

}

const sockaddr* UnixAddress::getAddr() const{

}
socklen_t UnixAddress::getAddrLen() const{

}

std::ostream& UnixAddress::insert(std::ostream& os) const{

}

UnkownAddress::UnkownAddress(const std::string& path){

}

const sockaddr* UnkownAddress::getAddr() const{

}
socklen_t UnkownAddress::getAddrLen() const{

}

std::ostream& UnkownAddress::insert(std::ostream& os) const{

}

}