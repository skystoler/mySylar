#include "bytearray.h"

namespace sylar{

Bytearray::Node::Node(size_t s)
    :ptr(new char[s])
    ,size(s)
    ,next(nullptr){

}

Bytearray::Node::Node()
    :ptr(nullptr)
    ,size(0)
    ,next(nullptr){

}

Bytearray::Node::~Node(){
    if(ptr){
        delete[] ptr;
    }
}

Bytearray::ByteArray(size_t base_size)
    :m_baseSize(base_size)
    ,m_position(0)
    ,m_capacity(base_size)
    ,m_size(0)
    ,m_root(new Node(base_size))
    ,m_cur(m_root)
    ,m_endian(SYLAR_BIG_ENDIAN){
}

~Bytearray::ByteArray(){
    Node* tmp=m_root;
    while(tmp){
        m_cur=tmp;
        tmp=tmp->next;
        delete m_cur;
    }
}

bool Bytearray::isLittleEndian() {
    return m_endian==SYLAR_LITTLE_ENDIAN;
}

void Bytearray::setIsLittleEndian(bool val){
    if(val) m_endian=SYLAR_LITTLE_ENDIAN;
    else m_endian=SYLAR_BIG_ENDIAN;
}

//write
void Bytearray::writeFint8(int8_t value){
    write(value,sizeof(value));
}

void Bytearray::writeFuint8(uint8_t value){
    write(value,sizeof(value));
}

void Bytearray::writeFint16(int16_t value){
    if(m_endian != SYLAR_BYTE_ORDER){
        value=byteswap(value);
    }
    write(value,sizeof(value));
}

void Bytearray::writeFuint16(uint16_t value){
    if(m_endian != SYLAR_BYTE_ORDER){
        value=byteswap(value);
    }
    write(value,sizeof(value));
}

void Bytearray::writeFint32(int32_t value){
    if(m_endian != SYLAR_BYTE_ORDER){
        value=byteswap(value);
    }
    write(value,sizeof(value));
}

void Bytearray::writeFuint32(uint32_t value){
    if(m_endian != SYLAR_BYTE_ORDER){
        value=byteswap(value);
    }
    write(value,sizeof(value));
}

void Bytearray::writeFint64(int64_t value){
    if(m_endian != SYLAR_BYTE_ORDER){
        value=byteswap(value);
    }
    write(value,sizeof(value));
}

void Bytearray::writeFuint64(uint64_t value){
    if(m_endian != SYLAR_BYTE_ORDER){
        value=byteswap(value);
    }
    write(value,sizeof(value));
}

void Bytearray::writeInt32(int32_t& value){

}

void Bytearray::writeUint32(uint32_t& value){

}

void Bytearray::writeInt64(int64_t& value){

}

void Bytearray::writeUint64(uint64_t& value){

}

void Bytearray::writeFloat(float& value){

}

void Bytearray::writeDouble(double& value){

}

//length:int16,data
void Bytearray::writeStringF16(const std::string& value){

}

//length:int32,data
void Bytearray::writeStringF32(const std::string& value){

}

//length:int64,data
void Bytearray::writeStringF64(const std::string& value){

}

//length:varint,data
void Bytearray::writeStringVint(const std::string& value){

}

//data
void Bytearray::writeStringWithoutLength(const std::string& value){

}

//read
int8_t Bytearray::readFint8();
uint8_t Bytearray::readFUint8();
int16_t Bytearray::readFint16();
uint16_t Bytearray::readFUint16();
int32_t Bytearray::readFint32();
uint32_t Bytearray::readFUint32();
int64_t Bytearray::readFint64();
uint64_t Bytearray::readFUint64();

int32_t Bytearray::readint32();
uint32_t Bytearray::readUint32();
int64_t Bytearray::readint64();
uint64_t Bytearray::readUint64();

float Bytearray::readFloat();
double Bytearray::readDouble();

std::string Bytearray::readStringF16();
std::string Bytearray::readStringF32();
std::string Bytearray::readStringF64();
std::string Bytearray::readStringVint();

void Bytearray::clear();

void Bytearray::write(const void* buf,size_t size);
void Bytearray::read(char* buf,size_t size);

void Bytearray::setPosition(size_t v);

bool Bytearray::writeToFile(const std::string& name);
void Bytearray::readFromFile(const stdL::string& name);

void Bytearray::addCapacity(size_t size);
}