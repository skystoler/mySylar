#include "scheduler.h"
#include "log.h"
#include "macro.h"

namespace sylar{

static sylar::Loggerptr g_logger=SYLAR_LOG_NAME("system");

static thread_local Scheduler* t_scheduler = nullptr;

static thread_local Fiber* t_fiber = nullptr;

Scheduler::Scheduler(size_t threads,bool use_caller=true,const std::string& name)
    :m_name(name){
    SYLAR_ASSERT(threads>0);

    if(use_caller){
        sylar::Fiber::GetThis();
        --threads;

        SYLAR_ASSERT(GetThis()==nullptr);
        t_scheduler=this;

        m_rootFiber.reset(new Fiber(std::bind(&Scheduler::run,this)));
        sylar::Thread::SetName(m_name);

        t_fiber=m_rootFiber.get();
        m_rootThread=sylar::GetThreadId();
        m_threadIds.push_back(m_rootThread);
    }else{
        m_rootThread=-1;
    }
    m_threadCount=threads;
}

Scheduler::~Scheduler(){
    SYLAR_ASSERT(m_stopping);
    if(GetThis()==this){
        t_scheduler=nullptr;
    }
}

Scheduler* Scheduler::GetThis(){
    return t_scheduler;
}

Fiber* Scheduler::GetMainFiber(){
    return t_fiber;
}

void Scheduler::start(){
    MutexType::Lock lock(m_mutex);
    if(!m_stopping){
        return;
    }
    SYLAR_ASSERT(m_threads.empty());

    m_threads.resize(m_threadCount);
    for(size_t i=0;i<m_threadCount;++i){
        m_threads[i].reset(new Thread(std::bind(&Scheduler::run,this)
                            ,m_name+"_"+std::to_string(i)));
    }
}

void Scheduler::stop(){
    
}

void Scheduler::run(){

}
}