#include "src/sylar.h"
#include "src/iomanager"

sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();
void test_sleep(){
    sylar::IOManager iom(1);

    iom.schedule([](){
        sleep(2);
        SYLAR_LOG_INFO(g_logger)<<"sleep 2";
    })
}

int main(int arc,char** argv){
    test_sleep();
    return 0;
}