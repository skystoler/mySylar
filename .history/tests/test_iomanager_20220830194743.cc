#include "src/sylar.h"
#include "src/iomanager.h"
#include <sys/types.h>
#includE <sys/socket.h>

sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();

void test_fiber(){
    SYLAR_LOG_INFO(g_logger)<<"test_fiber";
}

void test1(){
    sylar::IOManager iom;
    iom.schedule(&test_fiber);

    int sock=socket(AF_INET,SOCK_STREAM,0);
    fcntl(sock,F_SETFL,O_NONBLOCK);
}

int main(int argc,char** argv){
    test1();
    return 0;
}