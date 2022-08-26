#ifndef __SYLAR_IOMANAGER_H__
#define __SYLAR_IOMANAGER_H__

#include "scheduler.h"

namespace sylar{

class IOManager : public Scheduler{
public:
    using ptr=std::shared_ptr<IOManager>;
    using RWMutexType=RWMutex;

    enum Event{
        NONE=0x0;
        READ=0x1;
        WRITE=0x2;
    };
private:
    struct FdContext{
        using MutexType=Mutex;
        struct EventContext{
            Scheduler* scheduler=nullptr;     //事件执行的scheduler
            Fiber::ptr fiber;                 //事件协程
            std::function<void()> cb;         //事件的回调函数
        };
        
        EventContext read;   //读事件
        EventContext write;  //写事件
        int fd;              //事件关联的句柄
        Event m_events=NONE; //已经注册的事件

        MutexType mutex;
    };
};

}

#endif

