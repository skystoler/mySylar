#include "fiber.h"

namespace sylar{
    
    Fiber(std::function<void()> cb,size_t stacksize){

    }
    ~Fiber(){

    }

    //重置协程函数，并重置状态（init/terminal）
    void reset()(std::function<void()> cb){

    }

    //切换到当前协程执行
    void swapIn(){

    }

    //切换到后台执行
    void swapOut(){

    }

    //返回当前协程
    static Fiber::ptr GetThis(){

    }

    //协程切换到后台，并设置为ready状态
    static void YieldToReady(){

    }

    //协程切换到后台，并设置为hold状态
    static void YieldToHold(){

    }

    //总协程数
    static uint64_t TotalFibers(){

    }

    static MainFunc(){

    }
}