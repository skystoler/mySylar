#include "src/sylar.h"

sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();

int main(int argc,char** argv){
    sylar::Scheduler sc();
    sc.stop();
    return 0;
}