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

static uint32_t EncodeZigzag32(const int32_t& v){
    if(v<0) {
        return (uint32_t)(-v) *2 -1;
    }else{
        return v*2;
    }

}

static uint64_t EncodeZigzag64(const int64_t& v){
    if(v<0) {
        return (uint64_t)(-v) *2 -1;
    }else{
        return v*2;
    }

}

static uint64_t DecodeZigzag32(const int32_t& v){
    return (v>>1) ^ -(v & 1);
}

static uint64_t DecodeZigzag64(const int64_t& v){
    return (v>>1) ^ -(v & 1);
}

void Bytearray::writeInt32(int32_t value){
    writeUint32(EncodeZigzag32(value));
}

void Bytearray::writeUint32(uint32_t value){
    uint8_t tmp[5];
    uint8_t i=0;
    while(value>=0x80){
        tmp[i++]=(value & 0x7F) | 0x80;
        value>>7;
    }
    tmp[i++]=value;
    write(tmp,i)
}

void Bytearray::writeInt64(int64_t value){
    writeUint64(EncodeZigzag64(value));
}

void Bytearray::writeUint64(uint64_t value){
    uint8_t tmp[10];
    uint8_t i=0;
    while(value>=0x80){
        tmp[i++]=(value & 0x7F) | 0x80;
        value>>7;
    }
    tmp[i++]=value;
    write(tmp,i);
}

void Bytearray::writeFloat(float value){
    uint32_t v;
    memcpy(&v,&value,sizeof(value));
    writeFuint32(v);
}

void Bytearray::writeDouble(double value){
    uint64_t v;
    memcpy(&v,&value,sizeof(value));
    writeFuint64(v);
}

//length:int16,data
void Bytearray::writeStringF16(const std::string& value){
    writeFuint16(value.size());
    write(value.c_str(),value.size());
}

//length:int32,data
void Bytearray::writeStringF32(const std::string& value){
    writeFuint32(value.size());
    write(value.c_str(),value.size());
}

//length:int64,data
void Bytearray::writeStringF64(const std::string& value){
    writeFuint64(value.size());
    write(value.c_str(),value.size());
}

//length:varint,data
void Bytearray::writeStringVint(const std::string& value){
    writeUint64(value.size());
    write(value.c_str(),value.size());
}

//data
void Bytearray::writeStringWithoutLength(const std::string& value){
    write(value.c_str(),value.size());
}

//read
int8_t Bytearray::readFint8(){
    int8_t v;
    read(&v,sizeof(v));
    return v;
}

uint8_t Bytearray::readFuint8(){
    int8_t v;
    read(&v,sizeof(v));
    return v;
}

#define XX(type) \
    type v; \
    read(&v,sizeof(v)); \
    if(m_endian==SYLAR_BYTE_ORDER){ \
        return v; \
        
    }else{  \
        byteswap(v); \
    } 

    
int16_t Bytearray::readFint16(){
    XX(int16_t);
}

uint16_t Bytearray::readFuint16(){
    XX(int16_t);
}

int32_t Bytearray::readFint32(){
    XX(int32_t);
}

uint32_t Bytearray::readFuint32(){
    XX(int32_t);
}

int64_t Bytearray::readFint64(){
    XX(int64_t);
}

uint64_t Bytearray::readFuint64(){
    XX(int64_t);
}

#undef XX


int32_t Bytearray::readInt32(){
    return DecodeZigzag32(readUint32());
}

uint32_t Bytearray::readUint32(){
    uint32_t result=0;
    for(int i=0;i<32;i+=7){
        uint8_t b=readFuint8();
        if(v<0x80){
            result |=((uint32_t)b)<<i;
        }else{
            result|=((uint32_t)(b & 0x7f)<<i);
        }
    }
    return result;
}

int64_t Bytearray::readInt64(){
    return DecodeZigzag64(readUint64());
}

uint64_t Bytearray::readUint64(){
    uint64_t result=0;
    for(int i=0;i<64;i+=7){
        uint8_t b=readFUint8();
        if(v<0x80){
            result |=((uint64_t)b)<<i;
        }else{
            result|=((uint64_t)(b & 0x7f))<<I;
        }
    }
    return result;
}

float Bytearray::readFloat(){

}

double Bytearray::readDouble(){

}

std::string Bytearray::readStringF16(){

}

std::string Bytearray::readStringF32(){

}

std::string Bytearray::readStringF64(){

}

std::string Bytearray::readStringVint(){

}

void Bytearray::clear();

void Bytearray::write(const void* buf,size_t size);
void Bytearray::read(char* buf,size_t size);

void Bytearray::setPosition(size_t v);

bool Bytearray::writeToFile(const std::string& name);
void Bytearray::readFromFile(const stdL::string& name);

void Bytearray::addCapacity(size_t size);
}