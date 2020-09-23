cmake_minimum_required(VERSION 3.14)
project(netfilter_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(netfilter_test main.cpp)
target_link_libraries(netfilter_test netfilter_queue)