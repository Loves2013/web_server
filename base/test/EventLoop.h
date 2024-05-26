/*
 * @Author: abin
 * @Date: 2024-05-26 08:32:27
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-26 09:23:19
 * @FilePath: /muduo/web_server/base/test/EventLoop.h
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include "Thread.h"
#include "CurrentThread.h"
#include <iostream>
#include <atomic>
#include <any>
#include <functional>
#include <vector>
using namespace muduo::CurrentThread;
namespace muduo
{
namespace net
{
class EventLoop {
public:
    EventLoop();
    ~EventLoop();
    void loop();

    void assertInLoopThread() {
        if(!isInLoopThread()) {
            abortNotLoopThread();
        }
    }
    bool isInLoopThread() const { return threadId_ == muduo::CurrentThread::tid();}
    static EventLoop* getEventLoopOfCurrentThread();
private:
    void abortNotLoopThread(){
        std::cout<<"AborNotLoopThread() end.... \n";
        exit(-1);
    }

    bool looping_;
    const pid_t threadId_;

};
}
}

#endif // !MUDUO_NET_EVENTLOOP_H