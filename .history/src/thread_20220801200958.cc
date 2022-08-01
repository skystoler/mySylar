#include "thread.h"

namespace sylar{

static thread_local Thread* t_thread = nullptr;

Thread* Thread::GetThis(){

}
const std::string&  Thread::GetName(){
   
}
Thread(std::function<void()> cb,const std::string& name);
~Thread();

tid_t getId() const{return tid_t;}
    const std::string& getNmae() const{return m_name;}

    void join();


}