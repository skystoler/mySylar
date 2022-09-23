#ifndef __SYLAR_HOOK_H__
#define __SYLAR_HOOK_H__

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

namespace sylar{
    bool is_hook_enable();
    void set_hook_enable(bool flag);
}

//让编译器以处理 C 语言代码的方式来处理修饰的 C++ 代码。
extern "C"{

//sleep
using sleep_fun=unsigned int(*)(unsigned int seconds);
extern sleep_fun sleep_f;

using usleep_fun=unsigned int(*) (useconds_t usec);
extern usleep_fun usleep_f;

using nanosleep_fun=unsigned int(*)(const struct timespec *req,struct timespec *rem);
extern nanosleep_fun nanosleep_f;

//socket
using socket_fun=int(*)(int domain, int type, int protocol);
extern socket_fun socket_f;

using connect_fun=int(*)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
extern connect_fun connect_f;

using accept_fun=int(*)(int s, struct sockaddr *addr, socklen_t *addrlen);
extern accept_fun accept_f;

//read
using read_fun=ssize_t(*)(int fd, void *buf, size_t count);
extern read_fun read_f;

//高级io，分散读
using readv_fun=ssize_t(*)(int fd, const struct iovec *iov, int iovcnt);
extern readv_fun readv_f;

//TCP
using recv_fun=ssize_t(*)(int sockfd, void *buf, size_t len, int flags);
extern recv_fun recv_f;

//UDP
using recvfrom_fun=ssize_t(*)(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
extern recvfrom_fun recvfrom_f;

//TCP & UDP
using recvmsg_fun=ssize_t(*)(int sockfd, struct msghdr *msg, int flags);
extern recvmsg_fun recvmsg_f;

//write
using write_fun=ssize_t(*)(int fd, const void *buf, size_t count);
extern write_fun write_f;

//高级io，分散一并写
using writev_fun=ssize_t(*)(int fd, const struct iovec *iov, int iovcnt);
extern writev_fun writev_f;

//TCP
using send_fun=ssize_t(*)(int s, const void *msg, size_t len, int flags);
extern send_fun send_f;

//UDP
using sendto_fun=ssize_t(*)(int s, const void *msg, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
extern sendto_fun sendto_f;

//TCP & UDP
using sendmsg_fun=ssize_t(*)(int s, const struct msghdr *msg, int flags);
extern sendmsg_fun sendmsg_f;

using close_fun=int(*)(int fd);
extern close_fun close_f;

//通用文件描述符
using fcntl_fun=int(*)(int fd, int cmd, ... /* arg */ );
extern fcntl_fun fcntl_f;

using ioctl_fun=int(*)(int d, unsigned long int request, ...);
extern ioctl_fun ioctl_f;


//socket选项，专用于socket文件描述符
using getsockopt_fun=int(*)(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
extern getsockopt_fun getsockopt_f;

using setsockopt_fun =int(*)(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
extern setsockopt_fun setsockopt_f;

extern int connect_with_timeout(int fd,const struct sockaddr* addr,socklen_t addrlen,uint64_t timeout_ms);
}


#endif
