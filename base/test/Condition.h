/*
 * @Author: abin
 * @Date: 2024-05-22 07:45:13
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-22 07:52:59
 * @FilePath: /muduo/web_server/base/test/Condition.h
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include "Mutex.h"
#include <pthread.h>

namespace muduo
{
class Condition {
public:
    Condition(MutexLock& mutex) :mutex_(mutex) {
        pthread_cond_init(&pcond_,NULL);
    }

    ~Condition() {
        pthread_cond_destroy(&pcond_);
    }

    // void wait() {
    //     pthread_cond_wait(&pcond_,mutex_);
    // }

private:
    MutexLock& mutex_;
    pthread_cond_t pcond_;

};



}
