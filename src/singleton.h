#ifndef __SYLAR__SINGLETON__
#define __SYLAR__SINGLETON__

#include<memory>

/**
 *  单例模式封装类
 *  T 类型
 *  X 为了创造多个实例对应的Tag
 *  N 同一个Tag创造多个实例索引
 */
namespace sylar{

template<class T, class X=void, int N=0>
class Singleton{
public:
    static T* GetInstance(){
        static T v;
        return &v;
    }
};

/**
 *  单例模式智能指针封装类
 *  T 类型
 *  X 为了创造多个实例对应的Tag
 *  N 同一个Tag创造多个实例索引
 */
template<class T, class X=void, int N=0>
class SingletonPtr{
public:
    static std::shared_ptr<T> GetInstance(){
        static std::shared_ptr<T> v(new T);
        return v;
    }
};

}


#endif