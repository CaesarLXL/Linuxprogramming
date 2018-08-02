cmake_minimum_required(VERSION 3.10)
project(Linuxprogramming)

set(CMAKE_CXX_STANDARD 11)

add_executable(Linuxprogramming main.cpp CLStatus.cpp CLStatus.h CLLogger.cpp CLLogger.h CLThread.cpp CLThread.h)

find_package(Threads REQUIRED)
target_link_libraries(Linuxprogramming Threads::Threads)