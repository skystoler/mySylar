#ifndef __SYLAR__BYTEARRAY_H__
#define __SYLAR__BYTEARRAY_H__

#include<memory>
#include<string>
#include<stdint.h>

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
    void writeFint8(const int8_t& value);
    void writeFuint8(const uint8_t& value);
    void writeFint16(const int16_t& value);
    void writeFuint16(const uint16_t& value);
    void writeFint32(const int32_t& value);
    void writeFuint32(const uint32_t& value);
    void writeFint64(const int64_t& value);
    void writeFuint64(const uint64_t& value);
   

    void writeint8(const int8_t& value);
    void writeuint8(const uint8_t& value);
    void writeint16(const int16_t& value);
    void writeuint16(const uint16_t& value);
    void writeint32(const int32_t& value);
    void writeuint32(const uint32_t& value);
    void writeint64(const int64_t& value);
    void writeuint64(const uint64_t& value);


    void writeFloat(const float& value);
    void writeDouble(const double& value);
    void writeStringF16(const std::string& value);
    void writeStringF32(const std::string& value);
    void writeStringF64(const std::string& value);
    void writeStringVint(const std::string& value);


private:


};
}

#endif