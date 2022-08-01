#include "thread.h"
#include "log.h"

namespace sylar{

//线程指针
static thread_local Thread* t_thread = nullptr;
static thread_local std::string t_thread_name = "UNKNOW";

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

Thread* Thread::GetThis(){
    return t_thread;
}
const std::string& Thread::GetName(){
   return t_thread_name;
}

void Thread::SetName(const std::string& name){
    if(t_thread){
        t_thread->m_name = name;
    }
    t_thread_name = name;
}

Thread::Thread(std::function<void()> cb,const std::string& name){
    if(name.empty()){
        m_name="UNKNOW";
    }
    int rt=pthread_create(&m_thread,nullptr,&Thread::run,this);
    if(rt){

    }

}

~Thread();

void* run(void* arg){


}

tid_t getId() const{return tid_t;}
    const std::string& getNmae() const{return m_name;}

    void join();


}