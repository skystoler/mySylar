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
        SYLAR_LOG_ERROR(g_logger)<< "pthread_create thread failed, rt=" << rt
            <<" name=" << m_name;
        throw std::logic_error("pthread_create error");
    }
}

//datach or join
Thread::~Thread(){
    if(m_thread){
        pthread_detach(m_thread);
    }

}

void Thread::join(){
    if(m_thread){
        int rt=pthread_join(m_thread,nullptr);
        if(rt){
            SYLAR_LOG_ERROR(g_logger)<< "pthread_join thread failed, rt=" << rt
            <<" name=" << m_name;
            throw std::logic_error("pthread_join error");
        }
        m_thread = 0;
    }

}


void* Thread::run(void* arg){
    Thread* thread = (Thread*)arg;
    t_thread = thread;
    thread->m_id =sylar::GetThreadId();
    pthread_setname_np(pthread_self(),thread->m_name.substr(0,15).c_str());

    std::function<void()> cb;
    cb.swap(thread->m_cb);

    cb();
    return 0;
}

}