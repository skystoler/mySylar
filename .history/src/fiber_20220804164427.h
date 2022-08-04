#ifndef __SYLAR_FIBER_H__
#define __SYLAR_FIBER_H__

#include <memory>
#include <functional>
#include "thread.h"
#include <ucontext.h>

namespace sylar{
    //继承之后就不会在栈上创建智能指针,从进程的堆中分配一段内存作为协程的栈,有栈协程
class Fiber:public std::enable_shared_from_this<Fiber>{
public:
    std::shared_ptr<Fiber> ptr;

    enum State{
        INIT,
        HOLD,
        EXEC,
        TERM,
        READY
    }
private:
    Fiber();
public:
    Fiber(std::function<void()> cb,size_t stacksize=0);
    ~Fiber();

    void reset()(std::function<void()> cb);
    void swapIn();
    void swapOut();

public:
    //返回当前协程
    static Fiber::ptr GetThis();
    //协程切换到后台，并设置为ready状态
    static void YieldToReady();
    //协程切换到后台，并设置为hold状态
    static void YieldToHold();
    //总协程数
    static uint64_t TotalFibers();
};
}

#endif