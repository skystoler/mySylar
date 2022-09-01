#ifndef __SYLAR_TIMER_H__
#define __SYLAR_TIMER_H__

#include <memory>
#include <vector>
#include <set>
#include "thread.h"

namespace sylar {

class TimerManager;
class Timer : public std::enable_shared_from_this<Timer> {
friend class TimerManager;
public:
    typedef std::shared_ptr<Timer> ptr;
    bool cancel();

    //刷新设置定时器的执行时间
    bool refresh();

    //重置定时器时间
    bool reset(uint64_t ms, bool from_now);
private:
    Timer(uint64_t ms, std::function<void()> cb,
          bool recurring, TimerManager* manager);
    Timer(uint64_t next);
private:
    bool m_recurring = false;       //是否循环定时器
    uint64_t m_ms = 0;              //执行周期
    uint64_t m_next = 0;            //精确的执行时间
    std::function<void()> m_cb;
    TimerManager* m_manager = nullptr;
private:
    struct Comparator {
        bool operator()(const Timer::ptr& lhs, const Timer::ptr& rhs) const;
    };
};

class TimerManager {
friend class Timer;
public:
    typedef RWMutex RWMutexType;

    TimerManager();
    virtual ~TimerManager();

    //添加定时器
    Timer::ptr addTimer(uint64_t ms, std::function<void()> cb
                        ,bool recurring = false);

    //添加条件定时器
    Timer::ptr addConditionTimer(uint64_t ms, std::function<void()> cb
                        ,std::weak_ptr<void> weak_cond
                        ,bool recurring = false);

    //到最近一个定时器执行的时间间隔
    uint64_t getNextTimer();

    //获取需要执行的定时器的回调函数列表
    void listExpiredCb(std::vector<std::function<void()> >& cbs);

    //是否有定时器
    bool hasTimer();
protected:
    virtual void onTimerInsertedAtFront() = 0;
    void addTimer(Timer::ptr val, RWMutexType::WriteLock& lock);
private:
    bool detectClockRollover(uint64_t now_ms);
private:
    RWMutexType m_mutex;
    std::set<Timer::ptr, Timer::Comparator> m_timers;
    bool m_tickled = false;
    uint64_t m_previouseTime = 0;
};

}

#endif