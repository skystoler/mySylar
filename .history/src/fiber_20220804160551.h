#ifndef __SYLAR_FIBER_H__
#define __SYLAR_FIBER_H__

#include <memory>
#include "thread.h"
#include <ucontext.h>

namespace sylar{
    //继承之后就不会在栈上创建智能指针
class Fiber:public std::enable_shared_from_this<Fiber>{
public:
    std::shared_ptr<Fiber> ptr;

    enum State{
        INT,
        HOLD,
        EXEC,
        TERM,
        READY
    }
private:


};
}

#endif