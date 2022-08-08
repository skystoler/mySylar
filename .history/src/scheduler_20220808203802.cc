#include "scheduler.h"
#include "log.h"

namespace sylar{
static sylar::Loggerptr g_logger=SYLAR_LOG_NAME("system");

Scheduler(size_t threads=1,bool use_caller=true,const std::string& name="");

Scheduler:: ~Scheduler();

Scheduler* Scheduler::GetThis();
Scheduler::Fiber* GetMainFiber();

void Scheduler::start();
void Scheduler::stop();

}