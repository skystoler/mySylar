#ifndef __SYLAR_SCHEDULER_H__
#define __SYLAR_SCHEDULER_H__

#include <memory>
#include <vector>
#include <list>
#include <iostream>
#include "fiber.h"
#include "thread.h"
//#include "mutex.h"

namespace sylar{

class Scheduler{
public:
    using ptr=std::shared_ptr<Scheduler>;
    using MutexType=Mutex;

    Scheduler(size_t threads=1,bool use_caller=true,const std::string& name="");
    virtual ~Scheduler();

    const std:;string& getName() const{return m_name;}

    static Scheduler* GetThis();
    static Fiber* GetMainFiber();

    void start();
    void stop();

private:
    struct FiberAndThread{
        Fiber::ptr fiber;
        std::functional<void()> cb;
        int thread;

        FiberAndThread(Fiber::ptr f,int thr)
            :fiber(f),thread(thr){}
        
        //一种技巧，f传进来swap后就变成空指针，引用计数-1
        FiberAndThread(Fiber::ptr* f,int thr)
            :thread(thr){
            fiber.swap(*f);
        }
    };
private:
    MutexType m_mutex;
    std::vector<Thread::ptr> m_threads;
    std::list<> m_fibers;
    std::string m_name;
};


}
