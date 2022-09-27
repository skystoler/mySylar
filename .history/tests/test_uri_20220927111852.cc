#include "src/uri.h"
#include <iostream>

int main(int argc,char** argv){
    sylar::Uri::ptr uri=sylar::Uri::Create("http://www.sylar.top/test/uri?id=100&name=sylar#frg");
    std::cout<<uri->toString()<<std::endl;
    auto addr=uri->createAddress();
    std::cout<<*addr<<std::endl;
    return 0;
}