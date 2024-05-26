/*
 * @Author: abin
 * @Date: 2024-05-26 08:32:10
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-26 11:25:29
 * @FilePath: /muduo/web_server/base/test/main.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include "EventLoop.h"
using namespace muduo;
using namespace muduo::net;
using namespace muduo::CurrentThread;

void threadFunc() {
    printf("threadFunc : pid = %d，tid = %d \n",getpid(),tid());
    EventLoop loop;
    loop.loop();
}

int main() {
    printf("main(): pid = %d，tid = %d \n",getpid(),tid());
    
    EventLoop l;
    Thread t(threadFunc);
    t.startThread_();
    t.join_();

    return 0;
}