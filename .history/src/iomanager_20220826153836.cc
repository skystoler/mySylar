#include "iomanager.h"
#include "macro.h"
#include "log.h"

#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>

namespace sylar{

static sylar::Logger::ptr g_logger=SYLAR_lOG_NAME("system");

IOManager::IOManager(size_t threads,bool use_caller,const std::string& name)
    :Scheduler(threads,use_caller,name){
    m_epfd=epoll_create(5000);
    SYLAR_ASSERT(m_epfd>0);

    int rt=pipe(m_tickleFds);
    SYLAR_ASSERT(rt);

    epoll_event event;
    memset(&event,0,sizeof(epoll_event));
    event.events=EPOLLIN | EPOLLET; //边缘触发
    event.data.fd=m_tickleFds[0];

    //把文件状态标识（F_SETFL）设置为非阻塞（NONBLOCK）
    rt=fcntl(m_tickleFds[0],F_SETFL,O_NONOBLOCK);
    SYLAR_ASSERT(rt);

    //把文件描述符注册到epoll中(EPOLL_CTL_ADD)
    rt=epoll_ctl(m_epfd,EPOLL_CTL_ADD,m_tickleFds[0],&event);
    SYLAR_ASSERT(rt);

    contextResize(32);
    //m_fdContexts.resize(64);

    start();
}
IOManager::~IOManager(){
    stop();
    close(m_epfd);
    close(m_tickleFds[0]);
    close(m_tickleFds[1]);

    for(size_t i=0;i<m_fdContexts.size();++i){
        if(m_fdContexts[i]){
            delete m_fdContexts[i];
        }
    }
}

void IOManager::contextResize(size_t size){
    m_fdContexts.resize(size);

    for(size_t i=0;i<m_fdContexts.size();++i){
        if(!m_fdContexts[i]){
            m_fdContexts=new FdContext;
            m_fdContexts[i]->fd=i;
        }
    }
}

int IOManager::addEvent(int fd,Event event,std::function<void()> cb){
    FdContext* fd_ctx=nullptr;
    RWMutexType::ReadLock lock(m_mutex);
    if(m_fdContexts.size() > fd){
        fd_ctx=m_fdContexts[fd];
    }else{
        lock.unlock();
        RWMutexType::WriteLock lock2(m_mutex);
        contextResize(m_fdContexts.size()*1.5);
        fd_ctx=m_fdContexts[fd];
    }

    FdContext::MutexType::Lock lock(fd_ctx->mutex);
}

bool IOManager::delEvent(int fd,Event event){

}

bool IOManager::cancelEvent(itn fd,Event event){

}

bool IOManager::cancelAll(int fd){

}

static IOManager* GetThis();

protected:
    void tickle() override;
    void stopping() override;
    void idle() override;
}