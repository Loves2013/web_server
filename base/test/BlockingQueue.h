/*
 * @Author: abin
 * @Date: 2024-05-21 20:54:01
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-22 00:51:00
 * @FilePath: /muduo/web_server/base/test/BlockingQueue.h
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include <deque>
#include <condition_variable>
#include <mutex>
#include <string>
#include <iostream>
namespace muduo
{

template<typename T>
class BlockingQueue {
public:
    BlockingQueue()
        :mutex_(),
        notEmpty_(),
        queue_() {

    }
/* 生产者 */
void Put(const T& x) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push_back(x);
    }    
    notEmpty_.notify_one();
}
/* 消费者 */
T Take() {
    std::unique_lock<std::mutex> lock(mutex_);
    notEmpty_.wait(lock,[this] {
        return !queue_.empty();
    });

    T front_value(queue_.front());
    //std::cout<<"fromt_value:"<<front_value<<std::endl;
    queue_.pop_front();
    return front_value;
}

size_t size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}

private:
    std::mutex  mutex_;
    std::condition_variable notEmpty_;
    std::deque<T> queue_;
};



}
