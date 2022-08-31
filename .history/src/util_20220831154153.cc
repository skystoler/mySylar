#include "util.h"
#include "log.h"
#include "fiber.h"
#include <execinfo.h>
#include <sys/time.h>

namespace sylar{

sylar::Logger::ptr g_logger=SYLAR_LOG_NAME("system");

pid_t GetThreadId(){
    return syscall(SYS_gettid);
}

uint32_t GetFiberId(){
    return sylar::Fiber::GetFiberId();
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

std::string BacktraceToString(int size,int skip,const std::string& prefix){
    std::vector<std::string> bt;
    Backtrace(bt,size,skip);
    std::stringstream ss;
    for(size_t i=0;i<bt.size();++i){
        ss << prefix << bt[i] << std::endl;
    }
    return ss.str();
}

uint64_t GetCurrentMS(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_second*1000ul +tv.tv_usec/1000;
}

uint64_t GetCurrentUS(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_second*1000*1000ul +tv.tv_usec/1000;
}

}