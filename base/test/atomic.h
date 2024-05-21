/*
 * @Author: abin
 * @Date: 2024-05-20 23:28:53
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-21 09:59:04
 * @FilePath: /muduo/web_server/base/test/atomic.h
 * @Description: 原子类 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include <stdint.h>
namespace muduo
{
template <typename T>
class AtomicIntegerT {
public:
    AtomicIntegerT():value_(0) {

    }
    T get() {
        return __sync_val_compare_and_swap(&value_,0,0);
    }
    T getAndAdd(T x) {
    
          return __sync_fetch_and_add(&value_,x);
    }

    T addAndGet(T x) {
        return getAndAdd(x) + x;
    }

    T incrementAndGet() {
        return addAndGet(1);
    }

    T decrementAndGet() {
        return addAndGet(-1);
    }

    void decrement() {
        decrementAndGet();
    }

    void increment() {
        incrementAndGet();
    }

    T getAndSet(T newValue) {
        return __sync_lock_test_and_set(&value_,newValue);
    }

private:
    volatile T value_;
};
    typedef AtomicIntegerT<int32_t> AtomicInt32;
    typedef AtomicIntegerT<int64_t> AtomicInt64;



}