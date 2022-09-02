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

typedef ssize_t (*readv_fun)(int fd, const struct iovec *iov, int iovcnt);
extern readv_fun readv_f;

typedef ssize_t (*recv_fun)(int sockfd, void *buf, size_t len, int flags);
extern recv_fun recv_f;

typedef ssize_t (*recvfrom_fun)(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
extern recvfrom_fun recvfrom_f;

typedef ssize_t (*recvmsg_fun)(int sockfd, struct msghdr *msg, int flags);
extern recvmsg_fun recvmsg_f;

//write
typedef ssize_t (*write_fun)(int fd, const void *buf, size_t count);
extern write_fun write_f;

typedef ssize_t (*writev_fun)(int fd, const struct iovec *iov, int iovcnt);
extern writev_fun writev_f;

typedef ssize_t (*send_fun)(int s, const void *msg, size_t len, int flags);
extern send_fun send_f;

typedef ssize_t (*sendto_fun)(int s, const void *msg, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
extern sendto_fun sendto_f;

typedef ssize_t (*sendmsg_fun)(int s, const struct msghdr *msg, int flags);
extern sendmsg_fun sendmsg_f;

typedef int (*close_fun)(int fd);
extern close_fun close_f;

//
typedef int (*fcntl_fun)(int fd, int cmd, ... /* arg */ );
extern fcntl_fun fcntl_f;

typedef int (*ioctl_fun)(int d, unsigned long int request, ...);
extern ioctl_fun ioctl_f;

typedef int (*getsockopt_fun)(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
extern getsockopt_fun getsockopt_f;

typedef int (*setsockopt_fun)(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
extern setsockopt_fun setsockopt_f;
}


#endif
