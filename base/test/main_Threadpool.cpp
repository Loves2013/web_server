/*
 * @Author: abin
 * @Date: 2024-05-22 17:05:58
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-22 17:17:09
 * @FilePath: /muduo/web_server/base/test/main.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include <iostream>
#include "ThreadPool.h"
using namespace muduo;

void print() {
    printf("print() ===========================> \n");
}

void printfString(const std::string& str) {
    printf("printfString()===================> \n");
}

int main() {
    muduo::Threadpool pool("MainThreadPool");
    pool.start(5);
    pool.run(print);
    pool.run(print);
    for(int i = 0; i < 100; i++) {
        char buf[32];
        snprintf(buf,sizeof(buf), "task %d",i);
        pool.run(std::bind(printfString,std::string(buf)));
    }
    sleep(4);
    return 0;
}