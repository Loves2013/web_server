/*
 * @Author: abin
 * @Date: 2024-05-20 21:38:22
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-21 09:39:30
 * @FilePath: /muduo/web_server/base/test/application_thread.h
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include "thread.h"
using namespace muduo;
class Application_Thread : public Thread {
public:
    Application_Thread() {
        std::cout<<"Application_Thread() ... \n";
    }
    ~Application_Thread() {
        std::cout<<"~Application_Thread() ... \n";
    }

 
};