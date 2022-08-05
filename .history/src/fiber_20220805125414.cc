#include "fiber.h"
#include <atomic>
#include "macro.h"
#include "config.h"
#include "log.h"

namespace sylar{

static Logger::ptr g_logger = SYLAR_LOG_NAME("system");

static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_count {0};

static thread_local Fiber* t_fiber = nullptr;
static thread_local Fiber::ptr t_threadFiber= nullptr;

static ConfigVar<uint32_t>::ptr g_fiber_stack_size=
    Config::Lookup<uint32_t>("fiber.stack_size",128*1024,"fiber stack size");

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
        SYLAR_ASSERT(m_state == TERM || m_state== INIT || m_state==EXCEPT);
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

//重置协程函数，并重置状态（init/terminal/except）
void Fiber::reset()(std::function<void()> cb){
    SYLAR_ASSERT(m_stack);
    SYLAR_ASSERT(m_state== TERM || m_state==INIT || m_state==EXCEPT);
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
    m_state=EXEC;
    if(swapcontext(&t_threadFiber->m_ctx,&m_ctx)){
        SYLAR_ASSERT2(false,"swapcontext");
    }
}

//切换到后台执行
void Fiber::swapOut(){
    SetThis(t_threadFiber);
    if(swapcontext(&m_ctx,&t_threadFiber->m_ctxx)){
        SYLAR_ASSERT2(false,"swapcontext");
    }
}

//设置当前协程
void Fiber::ptr SetThis(Fiber* f){
    t_fiber=f;
}

//返回当前协程
Fiber::ptr GetThis(){
    //t_fiber是裸指针，要转成智能指针，存在则直接返回
    if(t_fiber){
        return t_fiber->shared_from_this();
    }
    Fiber::ptr main_fiber(new Fiber);
    //智能指针通过get访问裸指针
    SYLAR_ASSERT(t_fiber == main_fiber.get());
    t_threadFiber=main_fiber;
    return t_fiber->shared_from_this();
}

//协程切换到后台，并设置为ready状态
void Fiber::YieldToReady(){
    Fiber::ptr cur = GetThis();
    SYLAR_ASSERT(cur->m_state == EXEC);
    cur->m_state=READY;
    cur->swapOut();
}

//协程切换到后台，并设置为hold状态
void Fiber::YieldToHold(){
    Fiber::ptr cur = GetThis();
    SYLAR_ASSERT(cur->m_state == EXEC);
    cur->m_state=HOLD;
    cur->swapOut();
}

//总协程数
uint64_t Fiber::TotalFibers(){
    return s_fiber_count;
}

void Fiber::MainFunc(){
    Fiber::ptr cur=GetThis();
    SYLAR_ASSERT(cur);
    try{
        cur->m_cb();
        cur->m_cb=nullptr;
        cur->m_state = TERM;
    }catch(std::exception& ex{
        cur->m_state=EXCEPT;
        SYLAR_LOG_ERROR(g_logger)<<"Fiber Except: "<<ex.what();
    }catch(...){
        cur->m_state=EXCEPT;
        SYLAR_LOG_ERROR(g_logger)<<"Fiber Except: ";
    }
}

}