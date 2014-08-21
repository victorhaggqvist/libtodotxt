project(libtodotxt)
cmake_minimum_required(VERSION 2.8)
#set(CMAKE_COMPILER_IS_CLANG 1)
#set(CMAKE_COMPILER_IS_CLANGXX 1)
#set(CMAKE_CXX_COMPILER /usr/bin/clang++)
option(build_tests "Build unittests." OFF)
option(build_gitlib "Build gitenabled lib." ON)
#option(build_tests "Build unittests." ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(build_gitlib)
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

if(build_tests)
    add_subdirectory(test)
    #enable_testing()
    #add_test(unittest bin/libtodotxt_test)
    add_custom_target(test bin/libtodotxt_test)
endif()
