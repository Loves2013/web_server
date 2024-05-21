/*
 * @Author: abin
 * @Date: 2024-05-21 10:05:03
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-21 14:40:52
 * @FilePath: /muduo/web_server/base/test/CurrentThread.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include "CurrentThread.h"

namespace muduo 
{
    /* 用系统函数syscall() 来获取真实的tid */
pid_t CurrentThread::gettid() {
    return static_cast<pid_t>(syscall(SYS_gettid));
}

void CurrentThread::cacheTid() {
    if(t_cachedTid == 0) {
        t_cachedTid = gettid();
        t_tidStringLength = snprintf(t_tidString,sizeof(t_tidString),"%5d",t_cachedTid);
    }
}

}