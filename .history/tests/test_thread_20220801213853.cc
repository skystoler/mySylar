#include "src/util.h"
#include "src/config.h"
#include "src/log.h"
#include "src/singleton.h"
#include "src/thread.h"
#include <unistd.h>

sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();

void fun1(){
    SYLAR_LOG_INFO(g_logger)<<"name: "<<sylar::Thread::GetName()
                            <<" this.name: "<<sylar::Thread::GetThis()->getName()
                            <<" id: "<<sylar::GetThreadId()
                            <<" this.id: "<<sylar::Thread::GetThis()->getId();
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
    SYLAR_LOG_INFO(g_logger) << "thread test end";
    return 0;
}