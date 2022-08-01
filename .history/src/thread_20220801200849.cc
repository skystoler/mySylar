#include "thread.h"

namespace sylar{

Thread* GetThis();
const std::string&  GetName();//给日志用

Thread(std::function<void()> cb,const std::string& name);
~Thread();

tid_t getId() const{return tid_t;}
    const std::string& getNmae() const{return m_name;}

    void join();


}