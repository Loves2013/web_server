/*
 * @Author: abin
 * @Date: 2024-05-20 21:37:35
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-20 22:17:53
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
namespace muduo
{
class Thread {
public:
    Thread();
    virtual ~Thread();
    void start_();
    void join_();
    virtual void run_() = 0;

private:
    static void* call_back_(void*);
    pthread_t pthreadId_;
    

}; 


};