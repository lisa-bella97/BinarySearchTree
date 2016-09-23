<<<<<<< HEAD
cmake_minimum_required(VERSION 2.8)
=======
cmake_minimum_required(VERSION 2.8.7)
>>>>>>> 5f1158490bb349e76cfd7c1c11f7f74481f93a56
project(BinarySearchTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

<<<<<<< HEAD
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(BinarySearchTree STATIC ${CMAKE_CURRENT_SOURCE_DIR}/source/BinarySearchTree.cpp)

add_executable(Examples ${CMAKE_CURRENT_SOURCE_DIR} examples/main.cpp)
=======
set(SOURCE_FILES include/BinarySearchTree.h source/BinarySearchTree.cpp)
add_executable(BinarySearchTree ${SOURCE_FILES} examples/main.cpp )
>>>>>>> 5f1158490bb349e76cfd7c1c11f7f74481f93a56
