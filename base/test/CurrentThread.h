/*
 * @Author: abin
 * @Date: 2024-05-21 00:55:14
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-21 14:59:48
 * @FilePath: /muduo/web_server/base/test/CurrentThread.h
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/prctl.h>
#include <unistd.h>

namespace muduo
{
namespace CurrentThread
{
    /* __thread 修饰的变量是线程局部存储的，每个线程都有一份 */
    extern __thread int t_cachedTid;  /* 线程真实pid(tid)的缓存 */
    extern __thread char t_tidString[32];
    extern __thread int t_tidStringLength;
    extern __thread const char* t_threadName;

    void cacheTid();

    pid_t gettid();

    inline int tid() {
        /* 如果t_cache的Tid == 0 说明没有缓存过 */
        if(__builtin_expect(t_cachedTid == 0,0)) {
            cacheTid();
        }
        return t_cachedTid;
    }

}


}
