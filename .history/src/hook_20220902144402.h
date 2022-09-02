#ifndef __SYLAR_HOOK_H__
#define __SYLAR_HOOK_H__

#include "sylar.h"
#include <unistd.h>

namespace sylar{
    bool is_hook_enable();
    void set_hook_enable(bool flag);
}

//让编译器以处理 C 语言代码的方式来处理修饰的 C++ 代码。
extern "C"{
    using unsigned int seconds=unsigned int(*sleep_fun);
    unsigned int sleep(unsigned int seconds);

    int useep(useconds_t usec);
}


#endif
