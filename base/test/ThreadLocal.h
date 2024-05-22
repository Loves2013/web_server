/*
 * @Author: abin
 * @Date: 2024-05-22 20:37:40
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-23 02:40:50
 * @FilePath: /muduo/web_server/base/test/ThreadLocal.h
 * @Description: 在单线程程序中，我们经常用到全局变量来实现多个函数之间的共享数据
 * 多线程环境下，由于数据空间共享，因此全局变量也为所有线程共享
 * threadlocal :提供给给线程的私有全局变量，仅在某个线程中有效/
 * 可以跨多个函数访问 
 *  pthread_key_create: 一旦一个线程创建了key,所有的线程都有key
 *  有两个线程 t1 t2, t1 有pkey[1],t2 也有pkey[1]
 *  pthread_key_delete   删除pkey
 *  pthread_getspecific: 用来获取线程
 *  pthread_setspecific: 用来指定线程
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include <pthread.h>
namespace muduo 
{
template<typename T>
class ThreadLocal {
public:
    ThreadLocal() {
        pthread_key_create(&pkey_,&ThreadLocal::destructor);
    }
    ~ThreadLocal() {
        /* 销毁的是pkey,不是实际的pkey,实际的数据是由回调函数销毁的 */
        pthread_key_delete(pkey_);
    }
    T& value() {
        T* perThreadValue = static_cast<T*>((pthread_getspecific(pkey_)));
        if(!perThreadValue) {
            T* new_obj = new T();
            pthread_setspecific(pkey_,new_obj);
            perThreadValue = new_obj;
        }
        return *perThreadValue;
    }

private:
    static void destructor(void *x) {
        T* obj = static_cast<T*>(x);
        typedef char T_must_be_complete_type [sizeof(T) == 0 ? -1: 1]; 
        delete obj;
    }
    pthread_key_t pkey_;
};




}