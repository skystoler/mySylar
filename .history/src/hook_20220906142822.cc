#include "hook.h"
#include "fiber.h"
#include "iomanager.h"
#include "config.h"
#include "log.h"
#include "macro.h"
#include <dlfcn.h>

sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

namespace sylar{

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

struct timer_info{
    int cancelled=0;
};

template<typename OriginFun,typename ... Args>
static ssize_t do_io(int fd,OriginFun fun,const char* hook_fun_name,
    uint32_t event,int timeout_so,Args&&... args){
        if(!sylar::t_hook_enable){
            return fun(fd,std::forward<Args>(args)...); 
        }

        sylar::FdCtx::ptr ctx=sylar::FdMgr::GetInstance()->get(fd);

        //如果文件句柄不存在
        if(!ctx){
            return fun(fd,std::forward<Args>(args)...); 
        }

        //如果文件关闭
        if(ctx->isClose()){
            errno=EBADF;
            return -1;
        }

        //如果不是socket描述符或者用户设置了非阻塞
        if(!ctx->isSocket() || ctx->getUserNonblock()){
            return fun(fd,std::forward<Args>(args)...); 
        }

        uint64_t to = ctx->getTimeout(timeout_so);
        std::shared_ptr<timer_info> tinfo(new timer_info);

retry:
        //尝试直接读数据
        ssize_t n=fd(fd,std::forward<Args>(args)...);

        //中断，没有读到数据，重试
        while(n==-1 && errno==EINTR){
            n=fd(fd,std::forward<Args>(args)...);
        }
        //如果阻塞，需要做异步操作
        if(n==-1 && errno==EAGAIN){
            sylar::IOManager* iom=sylar::IOManager::GetThis();
            sylar::Timer::ptr timer;
            std::weak_ptr<timer_info> winfo(tinfo);

            //to存在，存在超时时间，那么设置条件定时器，满足条件会触发回调函数
            if(to!=(uint64_t)-1){
                timer=iom->addConditionTimer(to,[winfo,fd,iom,event](){
                    auto t=winfo.lock();
                    //如果条件没有了或者被取消了
                    if(!t || t->cancelled){
                        return;
                    }
                    t->cancelled=ETIMEDOUT;
                    //超时，把io事件取消掉
                    iom->cancelEvent(fd,(sylar::IOManager::Event)(event));
                },winfo);
            }

            //添加事件
            int rt=iom->addEvent(fd,(sylar::IOManager::Event)(event));

            //添加事件失败，取消定时器
            if(!rt==0){
                SYLAR_LOG_ERROR(g_logger)<<hook_fun_name<<" addEvent("
                    <<fd<<", "<<event<<")";
                if(timer){
                    timer->cancel();
                }
                return -1;
            }else{
                //添加成功，让出cpu时间
                sylar::Fiber::YieldToHold(); 

                //io事件回来之后，会从hold唤醒
                if(timer){
                    timer->cancel();
                }
                if(tinfo->cancelled){
                    errno=tinfo->cancelled;
                    return -1;
                }

                goto retry;
            }
        }

        //读到数据了，从while循环里出来，返回
        return n;
    }

extern "C"{
#define XX(name) name ## _fun name ## _f = nullptr;
    HOOK_FUN(XX);
#undef XX

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
    int fd=socket_f(domain,type,protocol);
    if(fd==-1){
        return fd;
    }
    sylar::FdMgr::GetInstance()->get(fd,true);
    return fd;
}

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){

}

int accept(int s, struct sockaddr *addr, socklen_t *addrlen){
    int fd=do_io(s,accept_f,"accept",sylar::IOManager::READ
                ,SO_RCVTIMEO,addr,addrlen);
    if(fd>=0){
        sylar::FdMgr::GetInstance()->get(fd,true);
    }
    return fd;
}

ssize_t read(int fd, void *buf, size_t count){
    return do_io(fd,read_f,"read",sylar::IOManager::READ
                ,SO_RCVTIMEO,buf,count);
}

ssize_t readv(int fd, const struct iovec *iov, int iovcnt){
    return do_io(fd,readv_f,"readv",sylar::IOManager::READ
                ,SO_RCVTIMEO,buf,count);
}

ssize_t recv(int sockfd, void *buf, size_t len, int flags){
    return do_io(sockfd,recv_f,"recv",sylar::IOManager::READ
            ,SO_RCVTIMEO,buf,len,flags);
}

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, 
            struct sockaddr *src_addr, socklen_t *addrlen){
    return do_io(sockfd,recvfrom_f,"recvfrom",sylar::IOManager::READ
            ,SO_RCVTIMEO,flags,src_addr,addrlen);

}

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags){
    return do_io(sockfd,recvmsg_f,"recvmsg",sylar::IOManager::READ
            ,SO_RCVTIMEO,msg,flags);
}

ssize_t write(int fd, const void *buf, size_t count){
    return do_io(fd,write_f,"write",sylar::IOManager::WRITE
                ,SO_SNDTIMEO,buf,count);
}

ssize_t writev(int fd, const struct iovec *iov, int iovcnt){
    return do_io(fd,writev_f,"writev",sylar::IOManager::WRITE
                ,SO_SNDTIMEO,iov,iovcnt);
}


ssize_t send(int s, const void *msg, size_t len, int flags){
    return do_io(s,send_f,"send",sylar::IOManager::WRITE
                ,SO_SNDTIMEO,len,flags);
}


ssize_t sendto(int s, const void *msg, size_t len, int flags,
            const struct sockaddr *to, socklen_t tolen){
    return do_io(s,sendto_f,"sendto",sylar::IOManager::WRITE
                ,SO_SNDTIMEO,len,flags);
}

ssize_t sendmsg(int s, const struct msghdr *msg, int flags){
    return do_io(s,sendmsg_f,"sendmsg",sylar::IOManager::WRITE
                ,SO_SNDTIMEO,msg,flags);
}

int close(int fd){
    if(!sylar::t_hook_enable){
        return close_f(fd);
    }

    syla::FdCtx::ptr ctx=sylar::FdManager::GetInstance()->get(fd);
    if(ctx){
        auto iom=sylar::IOManager::GetThis();
        if(iom){
            iom->cancelAll(fd);
        }
        sylar::FdManager::GetInstance()->del(fd);
    }
    return close_f(fd);
}


//
int fcntl(int fd, int cmd, ...){
    if(!sylar::t_hook_enable){
        return fcntl_f(fd,cmd,
    }

    va_list va;
    va_start(va,cmd);
    switch(cmd){
        case F_SETFL:
            {
                int arg=va_arg(va,int);
                va_end(va);
                sylar::FdManager::::ptr ctx=sylar::FdManager::GetInstance()->get(fd);
                if(!ctx || ctx->isClosed() || !ctx->isSocket()){
                    return fcntl_f(fd,cmd,arg);
                }
                //检查用户是否设置了非阻塞
                ctx->setUserNonblock(arg & O_NONBLOCK);
                //设置非阻塞
                if(ctx->getSysNonblock()){
                    arg |=O_NONBLOCK;
                //解除非阻塞
                }else{
                    arg &= ~O_NONBLOCK;
                }
                return fcntl_f(fd,cmd,arg);
            }
            break;
        case F_GETFL:
            {
                va_end(va);
                int arg=va_arg(va,int);
                sylar::FdManager::::ptr ctx=sylar::FdManager::GetInstance()->get(fd);
                if(!ctx || ctx->isClosed() || !ctx->isSocket()){
                    return arg;
                }
                //如果是用户态非阻塞
                if(ctx->getUserNonblock()){
                    return arg | O_NONBLOCK;
                }else{
                    return arg & ~O_NONBLOCK;
                }
                if(ctx->getSysNonblock()){
                    arg |=O_NONBLOCK;
                }else{
                    arg &= ~O_NONBLOCK;
                }
                return fcntl_f(fd,cmd,arg);
            }
            break;
        case F_DUPFD:
        case F_DUPFD_CLOEXEC:
        case F_SETFD:
        case F_SETOWN:
        case F_SETSIG:
        case F_SETLEASE:
        case F_NOTIFY:
#ifdef F_SETPIPE_SZ
        case F_SETPIPE_SZ:
#endif
            {
                int arg = va_arg(va, int);
                va_end(va);
                return fcntl_f(fd, cmd, arg); 
            }
            break;
        case F_GETFD:
        case F_GETOWN:
        case F_GETSIG:
        case F_GETLEASE:
#ifdef F_GETPIPE_SZ
        case F_GETPIPE_SZ:
#endif
            {
                va_end(va);
                return fcntl_f(fd, cmd);
            }
            break;
        case F_SETLK:
        case F_SETLKW:
        case F_GETLK:
            {
                struct flock* arg = va_arg(va, struct flock*);
                va_end(va);
                return fcntl_f(fd, cmd, arg);
            }
            break;
        case F_GETOWN_EX:
        case F_SETOWN_EX:
            {
                struct f_owner_exlock* arg = va_arg(va, struct f_owner_exlock*);
                va_end(va);
                return fcntl_f(fd, cmd, arg);
            }
            break;
        default:
            va_end(va);
            return fcntl_f(fd, cmd);
    }
}


int ioctl(int d, unsigned long int request, ...){

}


int getsockopt(int sockfd, int level, int optname, 
    void *optval, socklen_t *optlen){

}


int setsockopt(int sockfd, int level, int optname, 
    const void *optval, socklen_t optlen){

}

}