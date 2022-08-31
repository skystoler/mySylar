#ifndef __SYLAR_TIMER_H__
#define __SYLAR_TIMER_H__


#include<memory>
#include"thread.h"
namespace sylar{
class Timer:public std::enabled_shared_from_this<Timer>{
public:
    using ptr=std::shared_ptr<Timer>;
private:


};

}

#endif