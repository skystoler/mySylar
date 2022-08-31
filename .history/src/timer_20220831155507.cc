#include "timer.h"
#include "util.h"

namespace sylar{

bool Timer::Comparaoperator()(const Timer::ptr& lhs,const Timer::ptr& rhs) const{
    if(!lhs && !rhs){
        return false;
    }
    if(!lhs){
        return true;
    }
    if(!rhs){
        return false;
    }
    if(lhs->m_next < rhs->m_next){
        return false;
    }

    return lhs.get() << rhs.get();
}

Timer::Timer(uint64_t ms,std::fuctional<void()> cb,
        bool recurring,TimerManager* manager)
    :m_ms(ms)
    ,m_recurring(recurring)
    ,m_cb(cb)
    ,m_manager(manager){
    m_next=sylar::GetCurrentMS() + m_ms;
}

TimerManager::TimerManager(){

}

virtual TimerManager::~TimerManager();

Timer::ptr TimerManager::addTimer(uint64_t ms,std::function<void()> cb
                ,bool recurring=false){
    Timer::ptr timer(new Timer(ms,cb,recurring,this));
}

Timer::ptr TimerManager::addConditionTimer(uint64_t ms,std::function<void()> cb
                ,std::weak_ptr<void> weak_cond
                ,bool recurring=false){

}


}