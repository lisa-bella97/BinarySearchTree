cmake_minimum_required(VERSION 2.8.7)
project(BinarySearchTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(BinarySearchTree STATIC ${CMAKE_CURRENT_SOURCE_DIR}/source/BinarySearchTree.cpp)

add_executable(Examples ${CMAKE_CURRENT_SOURCE_DIR} examples/main.cpp)
add_executable(Tests ${TESTS_SOURCE} tests/catch.hpp tests/size.cpp tests/insert.cpp tests/find.cpp tests/main.cpp tests/remove.cpp)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
