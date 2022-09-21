#ifndef __SYLAR_STREAM_H__
#define __SYLAR_STREAM_H__

#include <memory>
#include "bytearray.h"

namespace sylar{

class Stream{
public:
    using ptr=std::shared_ptr<Stream>;
    Stream();
    virtual ~Stream();

    int read(void* buffer,size_t length);
    int read(ByteArray::ptr ba,size_t length);
    int write(const void* buffer,size_t length);
    int write(ByteArray::ptr ba,size_t length);
};

}

#endif