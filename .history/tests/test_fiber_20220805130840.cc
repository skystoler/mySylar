#include "sylar.h"

sylar::Logger g_logger=SYLAR_LOG_ROOT();

int main(int argc,char** argv){
    sylar::Fiber::ptr fiber(new sylar::Fiber(run_in_fiber));

    return 0;
}