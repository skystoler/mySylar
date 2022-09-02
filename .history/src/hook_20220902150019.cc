#include "hook.h"

namespace sylar{
    bool is_hook_enable(){

    }
    void set_hook_enable(bool flag){
        
    }
}

using sleep_fun=unsigned int(*)(unsigned int seconds);
extern sleep_fun sleep_f;

using usleep_fun=unsigned int(*) (useconds_t usec);
extern usleep_fun usleep_f;