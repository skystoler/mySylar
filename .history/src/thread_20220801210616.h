#ifndef __SYLAR_THREAD_H__
#define __SYLAR_THREAD_H__

//pthread__xx
//std::thread,pthread

#include <thread>
#include <functional>
#include <memory>
#include <pthread.h>

namespace sylar{

class Thread{
public:
    using ptr=std::shared_ptr<Thread>;
    Thread(std::function<void()> cb,const std::string& name);
    ~Thread();

    pid_t getId() const{return pid_t;}
    const std::string& getName() const{return m_name;}

    void join();

    static Thread* GetThis();
    static const std::string&  GetName();//给日志用
    static void setName(const std::string& name);
private:
    Thread(const Thread&) = delete;
    Thread(const Thread&&) = delete;
    Thread& operator=(const Thread&) = delete;

    static void* run(void* arg);
private:
    pid_t m_id = -1;
    pthread_t m_thread = 0;
    std::function<void()> m_cb;
    std::string m_name;
};

}

#endif
 