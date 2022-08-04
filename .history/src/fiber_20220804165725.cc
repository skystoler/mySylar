#include "fiber.h"
#include <atomic>

namespace sylar{

static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_count {0};

static thread_local Fiber* t_fiber = nullptr;
static thread_local std::shared_ptr<Fiber::ptr> = nullptr;

class MallocStackAllocator{
public:
    static void* Alloc(size_t size){
        return malloc(size);
    }

    static void Dealloc(void* vp,size_t size){
        return free(vp);
    }

};

Fiber::Fiber(){

}

Fiber::Fiber(std::function<void()> cb,size_t stacksize){

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