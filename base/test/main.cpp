/*
 * @Author: abin
 * @Date: 2024-05-20 22:09:24
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-21 15:50:08
 * @FilePath: /muduo/web_server/base/test/main.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include "thread.h"
#include <assert.h>
#include "CurrentThread.h"

using namespace muduo;
void threadFunc() {
    std::cout<<"================ func1() method 无参数 ================ \n";
}

void threadFunc1(int x) {
   // printf("tid=%d\n ",muduo::CurrentThread::tid());
    std::cout<<"int x:"<<x<<std::endl;
}

void threadFunc2(std::string y) {
   // printf("tid = %d, string: %s \n",muduo::CurrentThread::tid(),y);
    printf("threadFunc %s",y);
}
class Foo {
public:
    Foo(double x) :x_(x) {

    }
    void memberFunc(std::string& text) {
      //  printf("tid= %d, Foo::X_=%f text = %s \n",muduo::CurrentThread::tid(),x_,text.c_str());
    }
private:
    double x_;
};
int main() {
  //  printf("pid = %d,tid = %d\n",getpid(),muduo::CurrentThread::tid());
    muduo::Thread t1(threadFunc);
    t1.startThread_();
    printf("t1.tid =%d\n",t1.tid());
    t1.join_();

    muduo::Thread t2(std::bind(threadFunc1,1024),
                "thread for free function with argument ");
    t2.startThread_();
    printf("t2.tid = %d \n",t1.tid());
    t2.join_();

    // Foo foo(1612.0);
    // muduo::Thread t3(std::bind(&Foo::memberFunc,&foo),
    //         "thread for member function Foo::memberFunc ");

    sleep(2);
    return 0;
}