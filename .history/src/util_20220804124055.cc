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
    void** array=(void**)malloc((sizeof(void*) * size));
    //::用于表示全局变量
    size_t s=::backtrace(array,size);
}

std::string BacktraceToString(int size,int skip){

}

}