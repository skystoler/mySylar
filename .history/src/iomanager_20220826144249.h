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
public:
    IOManager(size_t threads=1,bool use_caller=true,const std::string& name="");
    ~IOManager();

    int addEvent(int fd,Event event,std::function<void()> cb=nullptr);
    bool delEvent(int fd,Event event);
    bool cancelEvent(itn fd,Event event);

    bool cancelAll(int fd);

    static IOManager* GetThis();
};

}

#endif

