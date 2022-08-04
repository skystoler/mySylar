#ifndef __SYLAR_UTIL_H
#define __SYLAR_UTIL_H

#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/syscall.h>
#include<stdio.h>
#include<stdint.h>

namespace sylar{
    pid_t GetThreadId();
    uint32_t GetFiberId();
}

void Backtrace(std::vector<std::string>& bt,int size,int skip);
std::string BacktraceToString(int size,int skip);

#endif