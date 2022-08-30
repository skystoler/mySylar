#ifndef __SYLAR_IOMANAGER_H__
#define __SYLAR_IOMANAGER_H__

#include "scheduler.h"

namespace sylar{

class IOManager : public Scheduler{
public:
    using ptr=std::shared_ptr<IOManager>;
    using RWMutexType=RWMutex;

    //IO事件
    enum Event{
        NONE=0x0,
        READ=0x1,
        WRITE=0x2,
    };
private:
    //socket事件上下文类
    struct FdContext{
        using MutexType=Mutex;
        //事件上下文类
        struct EventContext{
            Scheduler* scheduler=nullptr;     //事件执行的scheduler
            Fiber::ptr fiber;                 //事件协程
            std::function<void()> cb;         //事件的回调函数
        };
        

        EventContext& getContext(Event event);

        //重置事件上下文
        void resetContext(EventContext& ctx);

        //触发事件
        void triggerEvent(Event event);

        EventContext read;   //读事件
        EventContext write;  //写事件
        int fd;              //事件关联的句柄
        Event events=NONE;   //已经注册的事件

        MutexType mutex;
    };
public:
    //use_caller是否将调用线程包含进去
    IOManager(size_t threads=1,bool use_caller=true,const std::string& name="");
    ~IOManager();

    //添加事件：句柄，事件类型，事件回调函数
    int addEvent(int fd,Event event,std::function<void()> cb=nullptr);
    bool delEvent(int fd,Event event);
    bool cancelEvent(int fd,Event event);

    bool cancelAll(int fd);

    static IOManager* GetThis();

protected:
    void tickle() override;
    bool stopping() override;
    void idle() override;

    //重置socket句柄上下文的容器大小
    void contextResize(size_t size);
private:
    int m_epfd=0;
    int m_tickleFds[2];

    std::atomic<size_t> m_pendingEventCount={0};
    RWMutexType m_mutex;

    //socket事件上下文容器
    std::vector<FdContext*> m_fdContexts;

};

}

#endif

