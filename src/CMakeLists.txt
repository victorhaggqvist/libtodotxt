#project(libtodotxt)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
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

set(LIBGITSRC
    lib/todotxtgit.h
    lib/todotxtgit.cpp
    lib/githelper.h
    lib/githelper.cpp
)

add_library(todotxt ${LIBSRC})

if(build_gitlib)
    message(STATUS "Building todotxt git lib")
    include_directories(../libgit2/include)
    add_library(todotxtgit ${LIBSRC} ${LIBGITSRC})
    target_link_libraries(todotxtgit git2)
endif()

add_executable(${PROJECT_NAME}_run main.cpp ${LIBSRC})

#FIND_LIBRARY(todotxtgit_lib todotxtgit ../libgit2/include)
target_link_libraries(${PROJECT_NAME}_run todotxtgit)
#target_link_libraries(${PROJECT_NAME} test)
