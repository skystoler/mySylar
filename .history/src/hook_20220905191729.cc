#include "hook.h"
#include "fiber.h"
#include "iomanager.h"
#include "config.h"
#include "log.h"
#include "macro.h"
#include <dlfcn.h>

namespace sylar{

sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

static thread_local bool t_hook_enable=false;


#define HOOK_FUN(XX) \
    XX(sleep) \
    XX(usleep) \
    XX(nanosleep) \
    XX(socket) \
    XX(connect) \
    XX(accept) \
    XX(read) \
    XX(readv) \
    XX(recv) \
    XX(recvfrom) \
    XX(recvmsg) \
    XX(write) \
    XX(writev) \
    XX(send) \
    XX(sendto) \
    XX(sendmsg) \
    XX(close) \
    XX(fcntl) \
    XX(ioctl) \
    XX(getsockopt) \
    XX(setsockopt)

void hook_init(){
    static bool is_inited=false;
    if(is_inited){
        return;
    }

#define XX(name) name ## _f =(name ## _fun)dlsym(RTLD_NEXT, #name);
    HOOK_FUN(XX);
#undef XX
} 
 
struct _HookIniter{
    _HookIniter(){
        hook_init();
    }
};

static _HookIniter s_hook_initer;

bool is_hook_enable(){
    return t_hook_enable;
}

void set_hook_enable(bool flag){
    t_hook_enable=flag;
}

}

extern "C"{
#define XX(name) name ## _fun name ## _f = nullptr;
    HOOK_FUN(XX);
#undef XX

struct time_info{
    int cancelled=0;
}
 
template <typename OriginFun,tyname ... Args>
static ssize_t do_io(int fd,OriginFun fun,const char* hook_fun_name,
    uint32_t event,int timeout_so,ssize_t buflen,Args&&... args){
        if(!sylar::t_hook_enable){
            return fun(fd,std::forward<Args>(args)...); 
        }

        sylar::FdCtx::ptr ctx=sylar::FdMgr::GetInstance()->get(fd);

        //如果不是文件描述符
        if(!ctx){
            return fun(fd,std::forward<Args>(args)...); 
        }

        //如果文件关闭
        if(ctx->isClose()){
            errno=EBADF;
            return -1;
        }

        //如果不是socket描述符
        if(!ctx->isSocket() || ctx->getUserNonBlock()){
            return fun(fd,std::forward<Args>(args)...); 
        }

        uint64_t to = ctx->getTimeout(timeout_so);
        std::shared_ptr<timer_info> tinfo(new timer_info);

        ssize_t n=fd(fd,std::forward<Args>(args)...);

        //重试
        while(n==-1 && errno==EINTR){
            n=fd(fd,std::forward<Args>(args)...);
        }
        //如果阻塞，就添加定时器
        if(n==-1 && errno==EAGAIN){
            sylar::IOManager* iom=sylar::IOManager::GetThis();
            sylar::Timer::ptr timer;
            std::weak_ptr<time_info> winfo(tinfo);

            if(to!=(uint64_t)-1){
                timer=iomanager->addConditonTimer(to,[winfo,fd,iom,event](){
                    auto t=winfo.lock();
                    if(!t || t->cancelled){
                        return;
                    }
                    t->cancelled=ETIMEOUT;
                    iom->cancelEvent(fd,(sylar::IOManager::Event)(event));
                },wifo);
            }
            // int c=0;
            // uint64_t now=0;

            int rt=iom->addTimer(fd,(sylar::IOManager::Event)(event));

            //添加定时器失败，取消定时器
            if(!rt==0){
                SYLAR_LOG_ERROR(g_logger)<<hook_fun_name<<" addEvent("\
                    <<fd<<", "<<event<<")";
                if(timer){
                    timer->cancel();
                }
                return -1;
            }else{
                sylar::Fiber::YieldToReady();
            }
        }

    }

unsigned int sleep(unsigned int seconds){
    if(!sylar::t_hook_enable){
        return sleep_f(seconds);
    }
    sylar::Fiber::ptr fiber=sylar::Fiber::GetThis();
    sylar::IOManager* iom=sylar::IOManager::GetThis();
    iom->addTimer(seconds*1000,[iom,fiber](){
        iom->schedule(fiber);
    });
    sylar::Fiber::YieldToHold();
    return 0;
}

int usleep(useconds_t usec){
    if(!sylar::t_hook_enable){
        return usleep_f(usec);
    }
    sylar::Fiber::ptr fiber=sylar::Fiber::GetThis();
    sylar::IOManager* iom=sylar::IOManager::GetThis();
    iom->addTimer(usec/1000,[iom,fiber](){
        iom->schedule(fiber);
    });
    sylar::Fiber::YieldToHold();
    return 0;
}

int nanosleep(const struct timespec *req,struct timespec *rem){
    if(!sylar::t_hook_enable){
        return nanosleep_f(req,rem);
    }

    int timeout_ms=req->tv_sec*1000+req->tv_nsec/1000/1000;
    sylar::Fiber::ptr fiber=sylar::Fiber::GetThis();
    sylar::IOManager* iom=sylar::IOManager::GetThis();
    iom->addTimer(timeout_ms,[iom,fiber](){
        iom->schedule(fiber);
    });
    sylar::Fiber::YieldToHold();
    return 0;
}

int socket(int domain,int type,int protocol){
    if(!sylar::t_hook_enable) {
        return socket_f(domain, type, protocol);
    }
    return fd;
}


}