project(libtodotxt_test)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_BUILD_TYPE Debug)
#aux_source_directory(. SRC_LIST)

#add_subdirectory(gtest)
#include_directories(../gtest/include)
#add_executable(${PROJECT_NAME} main.cpp)
#find_package(GTest REQUIRED)
#set(GTEST_SOURCE_DIR gtest)
add_subdirectory(gtest)
INCLUDE_DIRECTORIES(${gtest_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(../src/lib)
#set(GTEST ${GTEST_SOURCE_DIR}/include)
#INCLUDE_DIRECTORIES(${GTEST_SOURCE_DIR}/include)
#include_directories(${GTEST_INCLUDE_DIRS})
file(GLOB SRC . *.cpp)
set(LIBSRC
../src/lib/todotxtmanager.h
../src/lib/todotxt.cpp
../src/lib/todotxt.h
../src/lib/todoitem.cpp
../src/lib/todoitem.h
)
set(SOURCES ${SRC} ${LIBSRC})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gtest gtest_main pthread)
#target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread ${SRC})
#target_link_libraries(todoitem_test ${GTEST_INCLUDE_DIRS} pthread)

#if (gtest)
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
#add_executable(todoitem_test todoitem_test.cpp)
#endif()
