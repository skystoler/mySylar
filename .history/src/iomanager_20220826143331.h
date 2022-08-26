#ifndef __SYLAR_IOMANAGER_H__
#define __SYLAR_IOMANAGER_H__

#include "scheduler.h"

namespace sylar{

class IOManager : public Scheduler{
public:
    using ptr=std::shared_ptr<IOManager>;
    using RWMutexType=RWMutex;

    enum Event{
        NONE=0x0;
        READ=0x1;
        WRITE=0x2;
    };
private:
};

}

#endif

