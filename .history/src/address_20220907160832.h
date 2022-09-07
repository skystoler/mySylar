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

    virtual std::ostream& insert(std::ostream& os) const;
}
}

#endif