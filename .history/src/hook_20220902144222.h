#ifndef __SYLAR_HOOK_H__
#define __SYLAR_HOOK_H__

#include "sylar.h"
#include <unistd.h>

namespace sylar{
    bool is_hook_enable();
    void set_hook_enable(bool flag);
}

extern "C"{
    unsigned int sleep(unsigned int seconds);

    int useep(useconds_t usec);
}


#endif
