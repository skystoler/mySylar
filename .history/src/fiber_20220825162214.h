#ifndef __SYLAR_FIBER_H__
#define __SYLAR_FIBER_H__

#include <memory>
#include <functional>
#include "thread.h"
#include <ucontext.h>

namespace sylar{

class Scheduler;
    //继承之后就不会在栈上创建智能指针,从进程的堆中分配一段内存作为协程的栈,有栈协程
class Fiber:public std::enable_shared_from_this<Fiber>{
friend class Scheduler;
public:
    using ptr=std::shared_ptr<Fiber>;

    enum State{
        //初始化
        INIT,
        //暂停
        HOLD,
        //执行中
        EXEC,
        //结束
        TERM,
        //可执行
        READY,
        //异常
        EXCEPT
    };
private:
    Fiber();
public:
    //use_caller 是否在MainFiber上调度
    Fiber(std::function<void()> cb,size_t stacksize=0,bool use_caller=false);
    ~Fiber();

    //重置协程函数，并重置状态（init/terminal）
    void reset(std::function<void()> cb);
    //切换到当前协程执行
    void swapIn();
    //切换到后台执行
    void swapOut();

    void call();

    void back();

    uint64_t getId() const{return m_id;}
    
    State getState() const { return m_state;}
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

    static void CallerMainFunc();

    static uint64_t GetFiberId();
private:
    uint64_t m_id = 0;
    uint32_t m_stacksize = 0;
    State m_state = INIT;

    ucontext_t m_ctx;
    void* m_stack = nullptr;
    std::function<void()> m_cb;
};
}

#endif