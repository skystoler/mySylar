#ifndef __SYLAR_THREAD_H__
#define __SYLAR_THREAD_H__

//pthread__xx
//std::thread,pthread

#include <thread>
#include <functional>
#include <memory>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>

namespace sylar{

//信号量
class Semaphore{
public:
    Semaphore(uint32_t count = 0);
    ~Semaphore();

    void wait();
    void notify();
private:
    Semaphore(const Semaphore&) = delete;
    Semaphore(const Semaphore&&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;
private:
    sem_t m_semaphore;
};

//局部锁模板
template <class T>
struct ScopedLockImpl{
public:
    ScopedLockImpl(T& mutex)
        :m_mutex(mutex){
            m_mutex.lock();
            m_locked=true;
        }
    ~ScopedLockImpl(){
        unlock();
    }

    void lock(){
        if(!m_locked){
            m_mutex.lock();
            m_locked=true;
        }
    }

    void unlock(){
        if(m_locked){
            m_mutex.unlock();
            m_locked=false;
        }   
    }

private:
    T& m_mutex;
    bool m_locked;
};


//局部读锁模板
template <class T>
struct ReadScopedLockImpl{
public:
    ReadScopedLockImpl(T& mutex)
        :m_mutex(mutex){
            m_mutex.rdlock();
            m_locked=true;
        }
    ~ReadScopedLockImpl(){
        unlock();
    }

    void lock(){
        if(!m_locked){
            m_mutex.rdlock();
            m_locked=true;
        }
    }

    void unlock(){
        if(m_locked){
            m_mutex.unlock();
            m_locked=false;
        }   
    }

private:
    T& m_mutex;
    bool m_locked;
};

//局部写锁模板
template <class T>
struct WriteScopedLockImpl{
public:
    WriteScopedLockImpl(T& mutex)
        :m_mutex(mutex){
            m_mutex.wrlock();
            m_locked=true;
        }
    ~WriteScopedLockImpl(){
        unlock();
    }

    void lock(){
        if(!m_locked){
            m_mutex.wrlock();
            m_locked=true;
        }
    }

    void unlock(){
        if(m_locked){
            m_mutex.unlock();
            m_locked=false;
        }   
    }

private:
    T& m_mutex;
    bool m_locked;
};

//互斥量
class Mutex{
public:
    using Lock=ScopedLockImpl<Mutex>;
    Mutex(){
        pthread_mutex_init(&m_mutex,nullptr);
    }

    ~Mutex(){
        pthread_mutex_destroy(&m_mutex);
    }
    void lock(){
        pthread_mutex_lock(&m_mutex);
    }
    void unlock(){
        pthread_mutex_unlock(&m_mutex);
    }
private:
    pthread_mutex_t m_mutex;
};

//空锁，用于调试
class NullMutex{
public:
    using Lock=ScopedLockImpl<NullMutex>;
    NullMutex(){}
    ~NullMutex(){}
    void lock(){}
    void unlock(){}
};

//读写互斥量
class RWMutex{
public:
    using ReadLock=ReadScopedLockImpl<RWMutex>;
    using WriteLock=WriteScopedLockImpl<RWMutex>;
    RWMutex(){
        pthread_rwlock_init(&m_lock,nullptr);
    }

    ~RWMutex(){
        pthread_rwlock_destroy(&m_lock);
    }

    void rdlock(){
        pthread_rwlock_rdlock(&m_lock);
    }

    void wrlock(){
        pthread_rwlock_wrlock(&m_lock);
    }

    void unlock(){
        pthread_rwlock_unlock(&m_lock);
    }

private:
    pthread_rwlock_t m_lock;
};

//空读写锁，用于调试
class NullRWMutex{
public:
    using ReadLock=ReadScopedLockImpl<NullMutex>;
    using WriteLock=WriteScopedLockImpl<NullMutex>;
    NullRWMutex(){}
    ~NullRWMutex(){}
    void lock(){}
    void unlock(){}
};

//自旋锁，cpu消耗更高，但冲突时间更短
class Spinlock(){
public:
    using Lock=ScopedLockImpl<Spinlock>;
    Spinlock() {
        pthread_spin_init(&m_mutex, 0);
    }

    ~Spinlock() {
        pthread_spin_destroy(&m_mutex);
    }

    void lock() {
        pthread_spin_lock(&m_mutex);
    }

    void unlock() {
        pthread_spin_unlock(&m_mutex);
    }
private:
    pthread_spinlock_t m_mutex;
};

//原子锁
class CASLock(){
public:
    using Lock=ScopedLockImpl<CASLock>;
private:
    volatile std::atomic_flag m_mutex;
};

class Thread{
public:
    using ptr=std::shared_ptr<Thread>;
    Thread(std::function<void()> cb,const std::string& name);
    ~Thread();

    pid_t getId() const{return m_id;}
    const std::string& getName() const{return m_name;}

    void join();

    static Thread* GetThis();
    static const std::string&  GetName();//给日志用
    static void SetName(const std::string& name);
private:
    // Thread(const Thread&) = delete;
    // Thread(const Thread&&) = delete;
    Thread& operator=(const Thread&) = delete;

    static void* run(void* arg);
private:
    pid_t m_id = -1;
    pthread_t m_thread = 0;
    std::function<void()> m_cb;
    std::string m_name;

    Semaphore m_semaphore;
};

}

#endif
 