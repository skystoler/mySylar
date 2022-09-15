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

    //构造指定大小的内存块
    struct Node{
        Node(size_t s);
        Node();
        ~Node();

        //内存块地址指针
        char* ptr;

        //内存块大小
        size_t size;  

        //下一个内存块地址
        Node* next;   
    };

    //使用指定长度的内存块构造ByteArray
    ByteArray(size_t base_size=4096);
    ~ByteArray();

    //write
    //写入固定长度int8_t类型的数据
    void writeFint8(int8_t value);

    //入固定长度uint8_t类型的数据
    void writeFuint8(uint8_t value);

    //写入固定长度int16_t类型的数据(大端/小端)
    void writeFint16(int16_t value);

    //写入固定长度uint16_t类型的数据(大端/小端)
    void writeFuint16(uint16_t value);

    //写入固定长度int32_t类型的数据(大端/小端)
    void writeFint32(int32_t value);

    //写入固定长度uint32_t类型的数据(大端/小端)
    void writeFuint32(uint32_t value);

    //写入固定长度int64_t类型的数据(大端/小端)
    void writeFint64(int64_t value);

    //写入固定长度uint64_t类型的数据(大端/小端)
    void writeFuint64(uint64_t value);
   
    //写入有符号Varint32类型的数据
    void writeInt32(int32_t value);

    //写入无符号Varint32类型的数据
    void writeUint32(uint32_t value);

    //写入有符号Varint64类型的数据
    void writeInt64(int64_t value);

    //写入无符号Varint64类型的数据
    void writeUint64(uint64_t value);

    void writeFloat(float value);
    void writeDouble(double value);

    //写入std::string类型的数据,用uint16_t作为长度类型
    void writeStringF16(const std::string& value);

    //length:int32,data
    void writeStringF32(const std::string& value);

    //length:int64,data
    void writeStringF64(const std::string& value);

    //写入std::string类型的数据,用无符号Varint64作为长度类型
    void writeStringVint(const std::string& value);

    //写入std::string类型的数据,无长度
    void writeStringWithoutLength(const std::string& value);

    //read
    int8_t readFint8();
    uint8_t readFuint8();
    int16_t readFint16();
    uint16_t readFuint16();
    int32_t readFint32();
    uint32_t readFuint32();
    int64_t readFint64();
    uint64_t readFuint64();

    int32_t readInt32();
    uint32_t readUint32();
    int64_t readInt64();
    uint64_t readUint64();

    float readFloat();
    double readDouble();

    std::string readStringF16();
    std::string readStringF32();
    std::string readStringF64();
    std::string readStringVint();

    //内部操作
    //清空ByteArray
    void clear();

    void write(const void* buf,size_t size);
    void read(void* buf,size_t size);

    //返回ByteArray当前位置
    size_t getPosition() const{return m_position;}
    void setPosition(size_t v);

    //把ByteArray的数据写入到文件中
    bool writeToFile(const std::string& name)const;
    void readFromFile(const std::string& name);

    //返回内存块的大小
    size_t getBaseSize()const {return m_baseSize;}

    //返回可读取数据大小
    size_t getReadSize()const {return m_size-m_position;}

    bool isLittleEndian() const;
    void setIsLittleEndian(bool val);
private:
    //扩容ByteArray,使其可以容纳size个数据(如果原本可以可以容纳,则不扩容)
    void addCapacity(size_t size);
    size_t getCapacity() const{return m_capacity-m_position;}
private:
    size_t m_baseSize;
    size_t m_position;
    size_t m_capacity;
    size_t m_size;
    
    Node* m_root;
    Node* m_cur;
    int8_t m_endian;
};
}

#endif