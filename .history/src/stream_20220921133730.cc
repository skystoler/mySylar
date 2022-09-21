#include "stream.h"

namespace sylar{

int readFixSize(void* buffer,size_t length){
    size_t offset=0;
    size_t left=length;
    while(left>0){
        size_t len=read(buffer,left);
    }
}

int readFixSize(ByteArray::ptr ba,size_t length){

}

int writeFixSize(const void* buffer,size_t length){

}

int writeFixSize(ByteArray::ptr ba,size_t length){

}

}
