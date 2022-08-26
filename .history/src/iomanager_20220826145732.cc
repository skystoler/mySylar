#include "iomanager.h"

namespace sylar{
IOManager::IOManager(size_t threads=1,bool use_caller=true,const std::string& name="");
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