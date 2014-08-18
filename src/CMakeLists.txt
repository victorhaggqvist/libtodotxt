#project(libtodotxt)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_BUILD_TYPE Debug)
#aux_source_directory(. SRC_LIST)
#file(GLOB SRC . *.cpp)
include_directories(.)
include_directories(./lib)
set(LIBSRC
    lib/todotxtmanager.h
    lib/todoitem.cpp
    lib/todoitem.h
    lib/todotxt.cpp
    lib/todotxt.h
)
add_executable(${PROJECT_NAME}_run main.cpp ${LIBSRC})
add_library(todotxt ${LIBSRC})
#target_link_libraries(${PROJECT_NAME} test)
