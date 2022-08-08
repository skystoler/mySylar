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
private:
    MutexType m_mutex;
    std::vector<Thread::ptr> m_threads;
    std::list<> m_fibers;
};


}
