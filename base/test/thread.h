/*
 * @Author: abin
 * @Date: 2024-05-20 21:37:35
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-21 14:26:08
 * @FilePath: /muduo/web_server/base/test/thread.h
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include <iostream>
#include <functional>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include "atomic.h"
#include <functional>
namespace muduo
{
class Thread {
public:
    /* 仿函数 */
    typedef std::function<void()> ThreadFunc;
    explicit Thread(ThreadFunc,const std::string& name = std::string());
    virtual ~Thread();
    /* 线程真实ID */
    pid_t tid() const { return tid_; }
    const std::string& name() { return name_; }
    static int numCreated() { return num_created_.get(); }
    void startThread_();
    void runInThread_();
    void join_();
    
private:
    static void* call_back_(void*);
    void setDefaultName();
    pthread_t pthreadId_;
    pid_t tid_;                            /* 线程的真实id */
    std::string name_;
    bool started_;                         /* 线程是否已经启动 */
    bool joined_;
    ThreadFunc func_;                     /* 回调函数 */
    static AtomicInt32 num_created_;       /* 已经创建的线程的个数 */ 



};
};