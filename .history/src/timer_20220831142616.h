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


};

}

#endif