#include "address.h"

namespace sylar{

int getFamily() const{
    return getAddr()->sa_family
}

const sockaddr* getAddr() const{

}
socklen_t getAddrLen() const{

}

std::ostream& insert(std::ostream& os) const{

}

}