/*
 * @Author: abin
 * @Date: 2024-05-22 07:53:54
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-22 17:15:47
 * @FilePath: /muduo/web_server/base/test/ThreadPool.h
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include <deque>
#include <vector>
#include "Thread.h"
#include <mutex>
#include <string>
#include <condition_variable>
#include <numeric>
namespace muduo
{
using namespace std;
class Threadpool {
public: 
    /* 任务 */
    typedef std::function<void()> Task;
    Threadpool(const string& nameArg = string("ThradPool"))
        :mutex_(),
        name_(nameArg),
        running_(false){

    }
    ~Threadpool(){
        /* 判断线程是否关闭 */
        if(running_) {
            stop();
        }
    } 
    /* 启动线程池 启动的线程池个数 */
    void start(int numThreads) {
        running_ = true;
        /* 预先准备vector 的空间*/
        threads_.reserve(numThreads);
        /* 添加线程vector然后执行 */
        for(int i = 0; i <numThreads; i++) {
            threads_.emplace_back(new muduo::Thread(
                /* pthread::rallback会调用 runInThread 这个函数 */
                std::bind(&Threadpool::runInThread,this),i+""));
            threads_[i]->startThread_();
        }
    }
    /*关闭*/
    void stop() {
        {
            lock_guard<mutex> lock(mutex_);
            running_ = false;
            cond_.notify_all();
        }
        for(auto& thr: threads_) {
            thr->join_();
        }
        
    }
    /* 将这个任务添加到线程池的队列中 */
    void run(const Task& task) {
        if(threads_.empty()) {  /* 如果发现线程池中的任务时空的，则执行这个任务*/
            task();
        }else {
            lock_guard<mutex> lock(mutex_);
            queue_.push_back(task);
            cond_.notify_one();
        }
    }
    /* 线程池中的线程所执行的任务*/ 
    void runInThread() {
        try
        {
            while(running_) {
                Task task(take());
                /* 取任务，如果这个任务不为空就去执行这个任务 */
                if(task) {
                    task(); // 执行这个任务 
                }
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    /* 线程池中的线程要获取任务 */
    Threadpool::Task take() {
        unique_lock<mutex> lock(mutex_);
        /* 如果queue 队列为空，且running为true(处于运行状态) */
        while(queue_.empty() && running_) {
            cond_.wait(lock);
        }
        Task task;  
        if(!queue_.empty()) {   /* 有任务到来 queue_不为空*/
            task = queue_.front();
            queue_.pop_front();
        }
        return task;
    }
private:
    mutex mutex_;
    condition_variable cond_;
    string name_;
    Task threadInitCallback_;
    vector<unique_ptr<muduo::Thread>> threads_;
    deque<Task> queue_;
    bool running_;    

};

}

