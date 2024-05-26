cmake_minimum_required(VERSION 3.20.0)
project(test CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp Mutex.h Thread.cpp Thread.h Atomic.h ThreadPool.h 
    Timestamp.h Timestamp.cpp CurrentThread.h EventLoop.h EventLoop.cpp)

target_link_libraries(main pthread)