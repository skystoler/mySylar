#include "fiber.h"
#include <atomic>
#include "macro.h"
#include "config.h"

namespace sylar{

static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_count {0};

static thread_local Fiber* t_fiber = nullptr;
static thread_local Fiber::ptr t_threadFiber= nullptr;

static ConfigVar<uint32_t>::ptr g_fiber_stack_size=
    Config::Lookup<uint32_t>("fiber.stack_size",1024*1024*,"fiber stack size");

class MallocStackAllocator{
public:
    static void* Alloc(size_t size){
        return malloc(size);
    }

    static void Dealloc(void* vp,size_t size){
        return free(vp);
    }

};

using StackAllocator=MallocStackAllocator; 

//假构造，把线程->协程
Fiber::Fiber(){
    m_state =  EXEC;
    SetThis(this);

    if(getcontext(&m_ctx)){
        SYLAR_ASSERT2(false,"getcontext");
    }

    ++s_fiber_count;
}

//真正构造一个新协程
Fiber::Fiber(std::function<void()> cb,size_t stacksize)
    :m_id(++s_fiber_id)
    ,m_cb(cb){
    ++s_fiber_count;
    m_stacksize=stacksize ? stacksize : g_fiber_stack_size->getValue();

    //分配栈空间
    m_stack=StackAllocator::Alloc(m_stacksize);
    if(getcontext(&m_ctx)){
        SYLAR_ASSERT2(false,"getcontext");
    }
    //生成上下文关联
    m_ctx.uc_link = nullptr;
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_m_stacksize;

    makecontext(&m_ctx,&Fiber::MainFunc,0);
}

Fiber::~Fiber(){
    --s_fiber_count;
    //有栈则为子协程，回收栈
    if(m_stack){
        SYLAR_ASSERT(m_state == TERM || m_state== INIT);
        StackAllocator::Dealloc(m_stack,m_stacksize);
    }else{
        //没有栈为主协程
        SYLAR_ASSERT(!m_cb);
        SYLAR_ASSERT(m_state == EXEC);

        Fiber* cur = t_fiber;
        if(cur==this){
            SetThis(nullptr);
        }
    }
}

//重置协程函数，并重置状态（init/terminal）
void Fiber::reset()(std::function<void()> cb){
    SYLAR_ASSERT(m_stack);
    SYLAR_ASSERT(m_state== TERM || m_state==INIT);
    m_cb=cb;
    if(getcontext(&m_ctx)){
        SYLAR_ASSERT2(false,"getcontext");
    }
    m_ctx.uc_link = nullptr;
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_m_stacksize;

    makecontext(&m_ctx,&Fiber::MainFunc,0);
    m_state=INIT;
}

//当前执行协程切换到当前操作协程执行
void Fiber::swapIn(){
    SetThis(this);
    SYLAR_ASSERT(m_state!=EXEC);


    if(swapcontext(t_threadFiber))
}

//切换到后台执行
void Fiber::swapOut(){

}

static Fiber::ptr SetThis(Fiber* f){

}

//返回当前协程
static Fiber::ptr GetThis(){

}

//协程切换到后台，并设置为ready状态
static void YieldToReady(){

}

//协程切换到后台，并设置为hold状态
static void YieldToHold(){

}

//总协程数
static uint64_t TotalFibers(){

}

static MainFunc(){

}

}