#include "bytearray.h"

namespace sylar{

Bytearray::Node::Node(size_t s)
    ,ptr(new char[s])
    ,size(s)
    ,next(nullptr){

}

Bytearray::Node::Node(){

}

Bytearray::Node::~Node(){

}
}