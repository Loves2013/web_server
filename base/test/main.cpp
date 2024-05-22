/*
 * @Author: abin
 * @Date: 2024-05-23 00:25:45
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-23 02:42:18
 * @FilePath: /muduo/web_server/base/test/main.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include "ThreadLocal.h"
#include "Thread.h"
#include <iostream>
#include <string>
using namespace muduo;

class Test {
public:
    Test() {
        printf("Test () \n");
    }
    ~Test() {
        printf("~Test() \n");
    }

    const std::string& name() {
        return name_;
    }

    void setName(const std::string& n) {
        name_ = n;
    }

private:
    std::string name_;
};

muduo::ThreadLocal<Test> testObj1;
muduo::ThreadLocal<Test> testObj2;

void print() {
    std::cout<<"&testObj1:::"<<&testObj1.value().name()<<":"
    <<&testObj2.value().name()<<std::endl;
}

void ThreadFunc() {
    print();
    testObj1.value().setName("changed 1");
    testObj1.value().setName("changed 2");

}


int main() {
    testObj1.value().setName("main one");
    print();
    muduo::Thread t1(ThreadFunc);
    t1.startThread_();
    t1.join_();
    
    testObj2.value().setName("main two");
    print();
    pthread_exit(0);

}
