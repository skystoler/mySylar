#include "sylar.h"

sylar::Logger g_logger=SYLAR_LOG_ROOT();

void run_in_fiber(){
    SYLAR_LOG_INFO(g_logger)<<"main begin";

}

int main(int argc,char** argv){
    sylar::Fiber::ptr fiber(new sylar::Fiber(run_in_fiber));
    fiber->swapIn();
    return 0;
}