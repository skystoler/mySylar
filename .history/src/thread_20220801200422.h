#ifndef __SYLAR_THREAD_H__
#define __SYLAR_THREAD_H__

//pthread__xx
//std::thread,pthread

#include <thread>
#include <functional>
#include<memory>

namespace sylar{

class Thread{
public:
    using ptr=std::shared_ptr<Thread>;
private:
    Thread(const Thread&) = delete;
    Thread(const Thread&&) = delete;
    Thread& operator=(const Thread&) = delete;
private:
    tid_t m_id;
    pthread_t m_thread;
    std::function<void()> m_cb;
    std::string m_name;
};

}

#endif
 