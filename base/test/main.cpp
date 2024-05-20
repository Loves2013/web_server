/*
 * @Author: abin
 * @Date: 2024-05-20 22:09:24
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-20 22:49:50
 * @FilePath: /muduo/web_server/base/test/main.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include "application_thread.h"

int main() {
    std::cout<<"=========================== \n";
    Application_Thread* t1 = new Application_Thread;
    t1->start_();
    std::cout<<"--------------------------\n";
    t1->join_(); /* 等待线程执行完毕后结束 主线程*/
    std::cout<<"```````````````````````````\n";

    return 0;
}