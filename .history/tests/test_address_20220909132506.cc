#include "address.h"
#include "log.h"

sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();

void test(){
    std::vector<sylar::Address::ptr> addrs;

    sylar::Address::Lookup(addrs,"www.baidu.com"); 
}

int main(int argc,char** argv){
    return 0;
}