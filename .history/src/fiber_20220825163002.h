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
    //无参构造，每个线程的第一个协程构造
    Fiber();
public:
    /* 
    cb 协程执行的函数
    stacksize 协程栈大小
    use_caller 是否在MainFiber上调度
    */
    Fiber(std::function<void()> cb,size_t stacksize=0,bool use_caller=false);
    ~Fiber();

    //重置协程函数，并重置状态（init/terminal）
    void reset(std::function<void()> cb);

    //将当前协程切换到运行状态
    void swapIn();

    //将当前协程切换到后台
    void swapOut();

    //将当前线程切换到运行状态，执行者为当前线程的主协程
    void call();

    //将当前线程切换到后台，执行者为该协程，返回到线程的主协程
    void back();

    //返回协程id
    uint64_t getId() const{return m_id;}
    
    //返回协程状态
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

    //协程执行函数，执行完成后返回到线程调度协程
    static void MainFunc();

    static void CallerMainFunc();

    //获取当前协程id
    static uint64_t GetFiberId();
private:
    uint64_t m_id = 0;
    uint32_t m_stacksize = 0;
    State m_state = INIT;

    //协程上下文
    ucontext_t m_ctx;

    //协程运行栈指针
    void* m_stack = nullptr;
    
    //协程运行函数
    std::function<void()> m_cb;
};
}

#endif