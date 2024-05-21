/*
 * @Author: abin
 * @Date: 2024-05-21 15:59:16
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-21 16:34:31
 * @FilePath: /muduo/web_server/base/test/Mutex.h
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include <pthread.h>

namespace muduo {

class MutexLock {
public:
    MutexLock()
    :holder_(0) {   /* 购买一把锁 */
        pthread_mutex_init(&mutex_,NULL);
    }

    ~MutexLock() {
        if(holder_ == 0) {
            pthread_mutex_destroy(&mutex_);
        }
    }

    void lock() {
        pthread_mutex_unlock(&mutex_);
    }

    void unlock() {
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t mutex_;
    pid_t holder_;
};

}