#ifndef __SYLAR_NONCOPYABLE_H__
#define __SYLAR_NONCOPYABLE_H__

namespace sylar {

//对象无法拷贝,赋值
class Noncopyable {
public:
    //默认构造函数
    Noncopyable() = default;

    // 默认析构函数
    ~Noncopyable() = default;

    // 拷贝构造函数(禁用)
    Noncopyable(const Noncopyable&) = delete;

    //赋值函数(禁用)
    Noncopyable& operator=(const Noncopyable&) = delete;
};

}

#endif