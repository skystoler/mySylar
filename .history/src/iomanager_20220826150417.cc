#include "iomanager.h"
#include "macro.h"
#include "log.h"

#include <unistd.h>
#include <sys/epoll.h>

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
    event.events=EPOLLIN | ET;
}
IOManager::~IOManager();

    int addEvent(int fd,Event event,std::function<void()> cb=nullptr);
    bool delEvent(int fd,Event event);
    bool cancelEvent(itn fd,Event event);

    bool cancelAll(int fd);

    static IOManager* GetThis();

protected:
    void tickle() override;
    void stopping() override;
    void idle() override;
}