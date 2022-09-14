#ifndef __SYLAR__BYTEARRAY_H__
#define __SYLAR__BYTEARRAY_H__

namespace sylar{

class ByteArray{
public:
    using ptr = std::shared_ptr<ByteArray>;

    struct Node{
        Node(size_t size);
        Node();
        ~Node();

        char* ptr;
        Node* next;
        size_t size;     
    };

    ByteArray(size_t base_size=4096);
    ~ByteArray();

    //write
    
private:


};
}

#endif