/*
 * @Author: abin
 * @Date: 2024-05-20 22:09:24
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-22 07:42:45
 * @FilePath: /muduo/web_server/base/test/main.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include <assert.h>
#include <vector>
#include "Mutex.h"
#include "Thread.h"
#include "functional"
using namespace muduo;
using namespace std;
MutexLock _mutex;
std::vector<int> _vec;
const int Count = 10 * 10;

void threadFunc() {
    for(int i = 0; i < Count; i++) {
        _mutex.lock();
        std::cout<<"================ threadFunc() method 无参数第: "<<i<<" ================ \n";
        sleep(1);
        _vec.push_back(i);
        _mutex.unlock();
    }
}

void threadFunc1(int x) {
   // printf("tid=%d\n ",muduo::CurrentThread::tid());
     for(int i = 0; i < Count; i++) {
        _mutex.lock();
        std::cout<<"================threadFunc1() method int x: "<<x<<"==========="<<std::endl;
        sleep(2);
        _vec.push_back(i);
        _mutex.unlock();
     }
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

    muduo::Thread t1(threadFunc,"threadFunc");
    t1.startThread_();

    muduo::Thread t2(std::bind(threadFunc1,1024),
                "threadFunc1");
    t2.startThread_();
    t1.join_();
    t2.join_();
    return 0;
}