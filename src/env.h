#ifndef __SYLAR_ENV_H__
#define __SYLAR_ENV_H__


#include "singleton.h"
#include<map>
#include<vector>

namespace sylar{


class Env{
public:
    void init();
private:
    
};

using EnvMgr=sylar::Singleton<Env>;

}


#endif
