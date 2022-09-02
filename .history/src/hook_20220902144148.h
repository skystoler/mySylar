#ifndef __SYLAR_HOOK_H__
#define __SYLAR_HOOK_H__

#include "sylar.h"
#include <unistd.h>

namespace sylar{

class Hook{
    bool is_hook_enable();
    void set_hook_enable();
};


}

unsigned int sleep(unsigned int seconds);

int useep(useconds_t usec);

#endif
