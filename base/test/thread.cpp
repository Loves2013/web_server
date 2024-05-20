/*
 * @Author: abin
 * @Date: 2024-05-20 21:37:45
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-20 22:29:42
 * @FilePath: /muduo/web_server/base/test/thread.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include "thread.h"
using namespace muduo;
Thread::Thread() {
   std::cout<<"Thread ... \n";
}

Thread::~Thread() {
    std::cout<<"~Thread ... \n";
}

void Thread::start_() {
    pthread_create(&pthreadId_,NULL,call_back_,this);
}

void* Thread::call_back_(void* arg) {
    Thread* thread = static_cast<Thread*>(arg);
    thread->run_();
    return NULL;
}

void Thread::join_() {
    pthread_join(pthreadId_,NULL);
}

void Thread::run_() {
    
}

// thread::thread() {
//     std::cout<<"Thread...\n";
// }
// thread::~thread() {
//     std::cout<<"~Thread...\n";
// }
// void thread::Start() {
//     pthread_create(&threadId_,NULL,thread_routine_,this);
// }

// void* thread::thread_routine_(void* arg) {

//     thread* t_ = static_cast<thread*>(arg);
//     t_->Run();
//     return NULL;
// }
// void thread::Run() {
    
// }
// void thread::join() {
//     pthread_join(threadId_,NULL);
// }

