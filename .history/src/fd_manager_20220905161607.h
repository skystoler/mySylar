#ifndef __FD_MANAGER_H__
#define __FD_MANAGER_H__

#include <memory>
#include "thread.h"

namespace sylar{
class FdCtx:public std::shared_from_this<FdCtx>{
public:
    using ptr=std::shared_ptr<FdCtx>;
private:
    bool m_isInit:1;
    bool m_isSocket:1;
    bool m_sysNonblock:1;
    bool m_userNonblock:1;
    bool m_isClosed:1;
    int m_fd;
    uint64_t m_recvTimeout;
    uint64_t m_sendTimeout;
    sylar::IOManager* iomanager;
}
}

#endif