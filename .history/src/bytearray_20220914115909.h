#ifndef __SYLAR__BYTEARRAY_H__
#define __SYLAR__BYTEARRAY_H__

namespace sylar{

class ByteArray{
public:
    typedef std::shared_ptr<ByteArray> ptr;

    struct Node{
        Node(size_t size);
        Node();
        ~Node();

        char* ptr;
        size_t size;
        Node* next;
    };
private:


};
}

#endif