#include "util.h"
#include "log.h"
#include <execinfo.h>

namespace sylar{

sylar::Logger::ptr g_logger=SYLAR_LOG_NAME("system");

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

    char** strings=backtrace_symbols(array,s);
    if(strings == nullptr){
        SYLAR_LOG_ERROR(g_logger)<<"backtrace_symbols error";
        return;
    }

    for(size_t i=skip;i<s;++i){
        bt.push_back(strings[i]);
    }

    free(strings);
    free(array);
}

std::string BacktraceToString(int size,int skip){

}

}