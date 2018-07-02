cmake_minimum_required(VERSION 3.7)
project(Injector)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++")


set(SOURCE_FILES main.cpp)
add_library(Injector SHARED ${SOURCE_FILES})
