/*
 * @Author: abin
 * @Date: 2024-05-20 21:37:45
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-22 17:27:37
 * @FilePath: /muduo/web_server/base/test/Thread.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include "Thread.h"

namespace muduo
{
    
AtomicInt32 Thread::num_created_;

Thread::Thread(ThreadFunc func,const std::string& n)
    :started_(false),
    joined_(false),
    pthreadId_(0),
    tid_(0),
    func_(std::move(func)),
    name_(n) {
        setDefaultName();
    }

Thread::~Thread() {
    std::cout<<"~Thread ... \n";
}
void Thread::runInThread_() {
    
    // tid_ = muduo::CurrentThread::tid();
    // muduo::CurrentThread::t_threadName = name_.c_str();
    func_();
};

void* Thread::call_back_(void* arg) {
    Thread* thread = static_cast<Thread*>(arg);
    thread->runInThread_();
    return NULL;
}

void Thread::setDefaultName() {
   // muduo::CurrentThread::t_cachedTid = 0;
    int num = num_created_.incrementAndGet();
    std::cout<<"当前线程数量"<<num<<std::endl;
    if(name_.empty()) 
    {
        char buf[32];
        snprintf(buf,sizeof(buf),"Thread %d",num);
        name_ = buf;
        std::cout<<"name_ :"<<name_<<std::endl;
    }
}

void Thread::startThread_() {
    if(pthread_create(&pthreadId_,NULL,call_back_,this)) {
       started_ = false;
       printf("create pthread failed .\n"); 
    }
    started_ = true;
    printf("create pthread success .\n");
}


void Thread::join_() {
    pthread_join(pthreadId_,NULL);
}



}


