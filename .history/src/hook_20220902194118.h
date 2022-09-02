#ifndef __SYLAR_HOOK_H__
#define __SYLAR_HOOK_H__

#include <unistd.h>
#include <time.h>

namespace sylar{
    bool is_hook_enable();
    void set_hook_enable(bool flag);
}

//让编译器以处理 C 语言代码的方式来处理修饰的 C++ 代码。
extern "C"{

using sleep_fun=unsigned int(*)(unsigned int seconds);
extern sleep_fun sleep_f;

using usleep_fun=unsigned int(*) (useconds_t usec);
extern usleep_fun usleep_f;

unsigned int sleep(unsigned int seconds);

int useep(useconds_t usec);

using 
}


#endif
