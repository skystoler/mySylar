#include "address.h"
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

}

const sockaddr* IPv4Address::getAddr() const{

}
socklen_t IPv4Address::getAddrLen() const{

}

std::ostream& IPv4Address::insert(std::ostream& os) const{

}

IPAddress::ptr IPv4Address::ibroadcastAddress(uint32_t prefix_len){

}
IPAddress::ptr IPv4Address::inetworkAddress(uint32_t prefix_len){

}
IPAddress::ptr IPv4Address::isubnerMask(uint32_t prefix_len){
    
}


IPv6Address::IPv6Address(uint32_t address,uint32_t port){

}

const sockaddr* IPv6Address::getAddr() const{

}
socklen_t IPv6Address::getAddrLen() const{

}

std::ostream& IPv6Address::insert(std::ostream& os) const{

}

IPAddress::ptr IPv6Address::ibroadcastAddress(uint32_t prefix_len){

}
IPAddress::ptr IPv6Address::inetworkAddress(uint32_t prefix_len){

}
IPAddress::ptr IPv6Address::isubnerMask(uint32_t prefix_len){
    
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