set(CMAKE_CXX_COMPILER clang++)
project(libtodotxt)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
option(TESTS "Build unittests." ON)
option(GITLIB "Build gitenabled lib." ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(GITLIB)
    message(STATUS "Building libgit2")
    add_subdirectory(libgit2)
endif()

add_subdirectory(src)

########################################################################
#
# Unittests with gtest for libtodotxt
#
# They are not built by default.  To build them, set the
# build_tests option to ON.  You can do it by running ccmake
# or specifying the -Dbuild_tests=ON flag when running cmake.

if(TESTS)
    message(STATUS "Building unittests")
    add_subdirectory(test)
    #enable_testing()
    #add_test(unittest bin/libtodotxt_test)
#    add_custom_target(test bin/libtodotxt_test)
endif()
