#include <iostream>
#include "src/http/http_connection.h"
#include "src/log.h"

static sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();

void run(){
    sylar::Address::ptr addr=sylar::Address::LookupAnyAddress("www.sylar.top:80");
}

int main(int argc,char** argv){
    sylar::IOManager::ptr iom(2);
    iom.schedule(run);
    return 0;
}