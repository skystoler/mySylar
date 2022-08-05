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
        READY,
        EXCEPT
    };
private:
    Fiber();
public:
    Fiber(std::function<void()> cb,size_t stacksize=0);
    ~Fiber();

    //重置协程函数，并重置状态（init/terminal）
    void reset(std::function<void()> cb);
    //切换到当前协程执行
    void swapIn();
    //切换到后台执行
    void swapOut();

public:
    //设置当前协程
    static void SetThis(Fiber* f);
    //返回当前协程
    static Fiber::ptr GetThis();
    //协程切换到后台，并设置为ready状态
    static void YieldToReady();
    //协程切换到后台，并设置为hold状态
    static void YieldToHold();
    //总协程数
    static uint64_t TotalFibers();

    static void MainFunc();
private:
    uint64_t m_id = 0;
    uint32_t m_m_stacksize = 0;
    State m_state = INIT;

    ucontext_t m_ctx;
    void* m_stack = nullptr;
    std::function<void()> m_cb;
};
}

#endif