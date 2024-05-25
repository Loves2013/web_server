/*
 * @Author: abin
 * @Date: 2024-05-24 17:04:18
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-05-24 17:04:42
 * @FilePath: /muduo/web_server/base/test/Time.h
 * @Description: 
 * 
 * Copyright (c) 2024 by 17320066637@163.com, All Rights Reserved. 
 */
#include <stdio.h>
#include <time.h>
#include <string>

/* 获取当前时间 时间格式：year-mon-day hour:min:sec */
std::string getCurrentTime() {

    /* 获取当前时间秒数 */
    time_t time_sec = time(0);
    tm cur_time_type;
    localtime_r(&time_sec,&cur_time_type);
    std::string get_current_time = std::to_string(cur_time_type.tm_year+1900) + "-"
                                + std::to_string(cur_time_type.tm_mon+1) + "-"
                                + std::to_string(cur_time_type.tm_mday) + " "
                                + std::to_string(cur_time_type.tm_hour) + ":"
                                + std::to_string(cur_time_type.tm_min) + ":"
                                + std::to_string(cur_time_type.tm_sec);
    printf("times: %s\n",get_current_time.c_str());
    return get_current_time.c_str();
}

