#include "fiber.h"
#include <atomic>
#include "macro.h"
#include "config.h"

namespace sylar{

static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_count {0};

static thread_local Fiber* t_fiber = nullptr;
static thread_local std::shared_ptr<Fiber::ptr> = nullptr;

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
        SYlAR_ASSERT(false,"getcontext");
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
        SYlAR_ASSERT(false,"getcontext");
    }
    //生成上下文关联
    m_ctx.uc_link = nullptr;
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_m_stacksize;

    makecontext(&m_ctx,&Fiber::MainFunc,0);
}

Fiber::~Fiber(){
    --s_fiber_count;
    if(m_stack){
        SYlAR_ASSERT(m_state == TERM || m_state== INIT);
        //有栈则为子协程，回收栈
        StackAllocator::Dealloc(m_stack,m_stacksize);
    }else{
        SYlAR_ASSERT(!m_cb);
        SYlAR_ASSERT(m_state == EXEC);

        Fiber* cur = t_fiber;
    }
}

//重置协程函数，并重置状态（init/terminal）
void reset()(std::function<void()> cb){

}

//切换到当前协程执行
void swapIn(){

}

//切换到后台执行
void swapOut(){

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