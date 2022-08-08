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

    Scheduler();
    ~Scheduler();
private:
    MutexType m_mutex;
    std::vector<Thread::ptr> m_threads;
    std::list<> m_fibers;
};


}
