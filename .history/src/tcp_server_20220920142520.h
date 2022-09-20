#ifndef __SYLAR_TCP_SERVER_H__
#define __SYLAR_TCP_SERVER_H__


#inlcude <memory>
#include <fucntional>

namespace sylae{

class TcpServer:public enabled_shared_from_this<TcpServer>{
public:
    using ptr=std::shared_ptr<TcpServer>;
private:
};

}
#endif