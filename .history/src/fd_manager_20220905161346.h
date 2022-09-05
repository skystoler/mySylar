#ifndef __FD_MANAGER_H__
#define __FD_MANAGER_H__

#include <memory>
#include "thread.h"

namespace sylar{
class FdCtx:public std::shared_from_this<FdCtx>{
public:
    using ptr=std::shared_ptr<FdCtx>;
    using MutexType=sylar::Mutex
private:
    bool m_isInit;
    bool m_isSocket;
    bool m_sysNonblock;
    int m_fd;

    uint64_t m_recvTimeout;
    uint64_t m_sendTimeout;

    sylar::IOManager* iomanager;
}
}

#endif