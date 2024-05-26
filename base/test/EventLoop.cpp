/*
 * @Author: abin
 * @Date: 2024-05-26 08:54:01
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-26 09:25:31
 * @FilePath: /muduo/web_server/base/test/EventLoop.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include "EventLoop.h"

using namespace muduo;
using namespace muduo::net;
using namespace muduo::CurrentThread;
namespace 
{
    __thread EventLoop* t_loopInThisThread = 0;
};

EventLoop::EventLoop() 
    :looping_(false),
    threadId_(CurrentThread::tid()){
        std::cout<<"EventLoop created:"<<this <<"is thread"<<threadId_<<"\n";
        if(t_loopInThisThread) {
            std::cout<<"t_loopInThisThread notEmpty()"<<"\n";
        }else {
            t_loopInThisThread = this;
        }   
}

EventLoop::~EventLoop() {
    std::cout<<"~EventLoop() = null \n";
    t_loopInThisThread = NULL;

}
EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
    return t_loopInThisThread;
}


void EventLoop::loop() {
    assertInLoopThread();
    looping_ = true;
    std::cout<<"EventLoop"<<this<<"start looping_ \n";
    sleep(2);
    std::cout<<"EventLoop"<<this<<"stop looping \n";
    looping_ = false;
}
