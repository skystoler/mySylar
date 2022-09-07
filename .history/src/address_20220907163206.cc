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

}

bool Address::operator==(const Addreess& rhs) const{

}

bool Address::operator!=(const Addreess& rhs) const{

}
    
const sockaddr* getAddr() const{

}
socklen_t getAddrLen() const{

}

std::ostream& insert(std::ostream& os) const{

}

}