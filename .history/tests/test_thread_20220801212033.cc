#include "util.h"
#include "config.h"
#include "log.h"
#include "singleton.h"

sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();
void fun1(){

}


void fun2(){

}

int main(int argc,char** argv){
    std::vector<sylar::Thread::ptr> thrs;
    for(int i=0;i<5;++i){
        sylar::Thread::ptr thr(new sylar::Thread(&fun1,"name_"+std::to_string(i)));
        thrs.push_back(thr);
    }

    for(int i=0;i<5;++i){
        thrs[i]->join();
    }
    return 0;
}