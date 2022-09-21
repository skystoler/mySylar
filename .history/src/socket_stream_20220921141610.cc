#include "socket_stream.h"

namespace sylar{

SocketStream::SocketStream(Socket::ptr sock,bool owner)
    :m_socket(sock)
    ,m_owner(owner){

}

SocketStream::~SocketStream(){
    if(owner && m_socket){
        m_socket->close();
    }
}

bool isConnected() const{
    return m_socket && m_socket->isConnected();
}

int SocketStream::read(void* buffer,size_t length) {
    
}

int SocketStream::read(ByteArray::ptr ba,size_t length){
    
}

int SocketStream::write(const void* buffer,size_t length){
    
}

int SocketStream::write(ByteArray::ptr ba,size_t length){
    
}

void SocketStream::close(){

}

}