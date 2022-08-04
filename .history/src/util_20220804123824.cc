#include "util.h"
#include <execinfo.h>

namespace sylar{
pid_t GetThreadId(){
    return syscall(SYS_gettid);
}

uint32_t GetFiberId(){
    return 0;
}

void Backtrace(std::vector<std::string>& bt,int size,int skip){
    void** array=(void**)malloc((sizeof()))
}

std::string BacktraceToString(int size,int skip){

}

}