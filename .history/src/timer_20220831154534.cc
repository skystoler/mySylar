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
    m_next=sylar::GetCurrent
}

}