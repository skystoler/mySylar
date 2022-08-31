#include "timer.h"

namespace sylar{

bool Timer::Comparaoperator()(const Timer::ptr& lhs,const Timer::ptr& rhs) const{
    if(!lhs && !rhs){
        return false;
    }
}

Timer::Timer(uint64_t ms,std::fuctional<void()> cb,
        bool recurring,TimerManager* manager){

        }

}