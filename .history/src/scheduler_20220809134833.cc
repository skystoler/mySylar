#include "scheduler.h"
#include "log.h"
#include "macro.h"

namespace sylar{

static sylar::Loggerptr g_logger=SYLAR_LOG_NAME("system");

static thread_local Scheduler* t_scheduler = nullptr;

static thread_local Fiber* t_fiber = nullptr;

Scheduler::Scheduler(size_t threads,bool use_caller=true,const std::string& name){

}

Scheduler::~Scheduler(){

}

Scheduler* Scheduler::GetThis(){

}

Fiber* Scheduler::GetMainFiber(){

}

void Scheduler::start(){

}

void Scheduler::stop(){
    
}

}