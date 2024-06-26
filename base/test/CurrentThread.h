/*
 * @Author: abin
 * @Date: 2024-05-26 09:28:16
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-26 11:20:15
 * @FilePath: /muduo/web_server/base/test/CurrentThread.h
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#ifndef MUDUO_CURRENTTHREAD_H
#define MUDUO_CURRENTTHREAD_H
#include <stdint.h>
#include <string>
#include <string.h>
#include "Timestamp.h"
#include <type_traits>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>
namespace muduo
{
namespace CurrentThread
{
  // internal
  inline __thread int t_cachedTid;
  inline __thread char t_tidString[32];
  inline __thread int t_tidStringLength;
  inline __thread const char* t_threadName;

    inline pid_t gettid()
    {
        return static_cast<pid_t>(::syscall(SYS_gettid));
    }

    inline void cacheTid()
    {
        if (t_cachedTid == 0)
        {
            t_cachedTid = gettid();
            t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
        }
    }


  inline int tid()
  {
    if (__builtin_expect(t_cachedTid == 0, 0))
    {
      cacheTid();
    }
    return t_cachedTid;
  }

  inline const char* tidString() // for logging
  {
    return t_tidString;
  }

  inline int tidStringLength() // for logging
  {
    return t_tidStringLength;
  }

  inline const char* name()
  {
    return t_threadName;
  }


inline bool isMainThread()
{
  return tid() == ::getpid();
}

inline void sleepUsec(int64_t usec)
{
  struct timespec ts = { 0, 0 };
  ts.tv_sec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond);
  ts.tv_nsec = static_cast<long>(usec % Timestamp::kMicroSecondsPerSecond * 1000);
  ::nanosleep(&ts, NULL);
}



}  
}  
#endif 