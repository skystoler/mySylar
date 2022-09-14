#ifndef __SYLAR__BYTEARRAY_H__
#define __SYLAR__BYTEARRAY_H__

#include <memory>
#include <string>
#include <stdint.h>
#include "endian.h"

namespace sylar{

class ByteArray{
public:
    using ptr = std::shared_ptr<ByteArray>;

    struct Node{
        Node(size_t s);
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
   
    void writeint32(const int32_t& value);
    void writeuint32(const uint32_t& value);
    void writeint64(const int64_t& value);
    void writeuint64(const uint64_t& value);

    void writeFloat(const float& value);
    void writeDouble(const double& value);
    //length:int16,data
    void writeStringF16(const std::string& value);
    //length:int32,data
    void writeStringF32(const std::string& value);
    //length:int64,data
    void writeStringF64(const std::string& value);
    //length:varint,data
    void writeStringVint(const std::string& value);
    //data
    void writeStringWithoutLength(const std::string& value);

    //read
    int8_t readFint8();
    uint8_t readFUint8();
    int16_t readFint16();
    uint16_t readFUint16();
    int32_t readFint32();
    uint32_t readFUint32();
    int64_t readFint64();
    uint64_t readFUint64();

    int32_t readint32();
    uint32_t readUint32();
    int64_t readint64();
    uint64_t readUint64();

    float readFloat();
    double readDouble();

    std::string readStringF16();
    std::string readStringF32();
    std::string readStringF64();
    std::string readStringVint();

    //内部操作
    void clear();

    void write(const void* buf,size_t size);
    void read(char* buf,size_t size);

    size_t getPosition() const{return m_position;}
    void setPosition(size_t v);

    bool writeToFile(const std::string& name)const;
    void readFromFile(const stdL::string& name);

    size_t getBaseSize()const {return m_baseSize;}
    size_t getReadSize()const {return m_size-m_position;}

    bool isLittleEndian() const;
    void setIsLittleEndian(bool val);
private:
    void addCapacity(size_t size);
    size_t getCapacity() const{return m_capacity-m_position;}
private:
    size_t m_baseSize;
    size_t m_position;
    size_t m_capacity;
    size_t m_size;
    int8_t m_endian;

    Node* m_root;
    Node* m_cur;
};
}

#endif