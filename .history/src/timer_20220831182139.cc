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

Timer::Timer(uint64_t next)
    :m_next(next){

}

bool Timer::cancel(){
    TimerManager::RWMutexType::WriteLock lock(m_manager->m_mutex);
    if(m_cb){
        m_cb=nullptr;
        auto it=m_manager->m_timers.find(shared_from_this());
        m_manager->m_timers.erase(it);
        return true;
    }
    return false;
}

bool Timer::refresh(){
    TimerManager::RWMutexType::WriteLock lock(m_manager->m_mutex);
    if(!m_cb){
        return false;
    }
    auto it=m_manager->m_timers.find(shared_from_this());
    if(it==m_manager->m_timers.end()){
        return false;
    }
    m_manager->m_timers.erase(it);
    m_next=sylar::GetCurrent()+m_ms;
    m_manager->m_timers.insert(shared_from_this());
    return true;
}

bool Timer::reset(uint64_t ms,bool from_now){
    if(ms==m_ms && !from_now){
        return true;
    }
    TimerManager::RWMutexType::WriteLock lock(m_manager->m_mutex);
    if(!m_cb){
        return false;
    }
    auto it=m_manager->m_timers.find(shared_from_this());
    if(it==m_manager->m_timers.end()){
        return false;
    }
    m_manager->m_timers.erase(it);
    uint64_t start=0;
    if(from_now){
        start=sylar::GetCurrentMS();
    }else{
        start=m_next-m_ms;
    }
    m_ms=ms;
    m_next=start+m_ms;
    it=m_manager->m_timers.insert(shared_from_this()).first;
    return true;
}

TimerManager::TimerManager(){

}

virtual TimerManager::~TimerManager();

Timer::ptr TimerManager::addTimer(uint64_t ms,std::function<void()> cb
                ,bool recurring=false){
    Timer::ptr timer(new Timer(ms,cb,recurring,this));
    RWMutexType::WriteLock lock(m_mutex);
    auto it=m_timers.insert(timer).first;
    bool at_front=(it==m_timers.begin());
    lock.unlock();

    if(at_front){
        onTimerInsertedAtFront();
    } 
    return timer;
}

static void OnTimer(std::weak_ptr<void> weak_cond,std::function<void()> cb){
    std::shared_ptr<void> tmp=weak_cond.lock();
    if(tmp){
        cb();
    }
}

Timer::ptr TimerManager::addConditionTimer(uint64_t ms,std::function<void()> cb
                ,std::weak_ptr<void> weak_cond
                ,bool recurring=false){
    return addTimer(ms,std::bind(&onTimer,weak_cond,cb),recurring);
}

uint64_t TimerManager::getNextTimer(){
    sylar::RWMutexType::ReadLock lock(m_mutex);
    if(m_timers.empty()){
        return ~0ull;
    }

    const Timer::ptr& next=*m_timers.begin();
    uint64_t now_ms=sylar::GetCurrentMS();
    if(now_ms>=next->m_next){
        return 0;
    }else{
        return next->m_next-now_ms;
    }
}

void TimerManager::listExpiredCb(std::vector<std::function<void()>>& cbs){
    uint64_t now_ms=syalr::GetCurrentMS();
    std::vector<Timer::ptr> expired;

    {
        RWMutexType::ReadLock lock(m_mutex);
        if(m_timers.empty()){
            return;
        }
    }
    RWMutexType::WriteLock lock(m_mutex);
    Timer::ptr now_timer(new Timer(now_ms));
    auto it=m_timers.lowerbound(now_timer);
    while(it!=m_timers.end() && (*it)->m_next==now_ms){
        ++it;
    }
    expired.insert(expired.begin(),m_timers.begin(),it);
    m_timers.erase(m_timers.begin(),it);
    cbs.reserve(expired.size());

    for(auto& timer:expired){
        cbs.push_back(timer->m_cb);
        if(timer->m_recurring){
            timer->m_next=now_ms+timer->m_ms;
            m_timers.insert(timer);
        }else{
            timer->m_cb=nullptr;
        }
    }

}

void TimerManager::addTimer(Timer::ptr val){
    auto it=m_timers.insert(timer).first;
    bool at_front=(it==m_timers.begin());
    lock.unlock();

    if(at_front){
        onTimerInsertedAtFront();
    } 
}
}