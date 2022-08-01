#include "thread.h"

namespace sylar{

static thread_local Thread* t_thread = nullptr;
static thread_local std::string t_thread_name = "UNKNOW";

Thread* Thread::GetThis(){
    return t_thread;
}
const std::string&  Thread::GetName(){
   return t_thread_name;
}
Thread(std::function<void()> cb,const std::string& name);
~Thread();

tid_t getId() const{return tid_t;}
    const std::string& getNmae() const{return m_name;}

    void join();


}