cmake_minimum_required(VERSION 3.20.0)
project(test CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp Mutex.h thread.cpp thread.h Atomic.h )

target_link_libraries(main pthread)