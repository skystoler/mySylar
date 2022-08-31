#ifndef __SYLAR_TIMER_H__
#define __SYLAR_TIMER_H__


#include<memory>
#include"thread.h"

namespace sylar{

class TimerManager;
class Timer:public std::enabled_shared_from_this<Timer>{
public:
    using ptr=std::shared_ptr<Timer>;
private:
    Timer(uint64_t ms,std::fuctional<void()> cb,
            bool recurring,TimerManager* manager);

private:
    bool m_recurring=false;     //是否循环定时器
    uint64_t m_ms=0;            //执行周期
    uint64_t m_next=0;          //精确的执行时间
    TimerManager* m_manager=nullptr;
private:
    struct Comparator{
        bool operator()(const Timer::ptr& lhs,const Timer::ptr& rhs) const;
    };
};

class TimerManager{
public:
    using RWMutexType=RWMutex;

    TimerManager();
    virtual ~TimerManager();

    Timer::ptr addTimer(uint64_t ms,std::function<void()> cb
                        ,bool recurring=false);

    Timer::ptr addConditionTimer(uint64_t ms,std::function<void()> cb
                        ,std::weak_ptr<void> weak_cond
                        ,bool recurring=false);
protected:
    virtual void onTimerInsertedAtFront();
private:
    RWMutexType m_mutex;
    std::set<Timer::ptr,Timer::Comparator> m_timers;
};

}

#endif