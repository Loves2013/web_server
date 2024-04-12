/*
 * @Author: abin
 * @Date: 2024-04-12 05:54:29
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-04-12 08:09:32
 * @FilePath: /web_server/sylar/log.cc
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include "log.h"
namespace sylar
{
///////////////////////////////////////////////////////////////
Logger::Logger(const std::string& name):m_name(name)
{
        
}

void Logger::addAppender(LogAppender::ptr appender)
{
    m_appenders.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender)
{
    for(auto it = m_appenders.begin();it != m_appenders.end(); ++it)
    {
        if(*it == appender)
        {
            m_appenders.erase(it);
            break;
        }
    }
}
void Logger::log(LogLevel::Level level,LogEvent::ptr event)
{
    if(level >= m_level)
    {
        for(auto& i : m_appenders)
        {
            i->log(level,event);
        }
    }
}

void Logger::debug(LogEvent::ptr event)
{
    log(LogLevel::DEBUG,event);
}

void Logger::info(LogEvent::ptr event)
{
    log(LogLevel::INFO,event);
}

void Logger::warn(LogEvent::ptr event)
{
    log(LogLevel::WARN,event);
}

void Logger::error(LogEvent::ptr event)
{
    log(LogLevel::ERROR,event);
}

void Logger::fatal(LogEvent::ptr event)
{
    log(LogLevel::FATAL,event);    

};

void StdouLogAppender::log(LogLevel::Level level,LogEvent::ptr event)
{
    if(level >= m_level)
    {
        std::cout<< m_formatter.format(event)<<std::endl;
    }
}
FileLogAppender::FileLogAppender(const std::string& filename)
    :m_filename(filename){
        
}

void FileLogAppender::log(LogLevel::Level level,LogEvent::ptr event)
{
    if(level >= m_level)
    {
        m_filestream << m_formatter.format(event);
    }    
};

bool FileLogAppender::reopen()
{
    if(m_filestream)
    {
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return !!m_filestream;

    
}


}