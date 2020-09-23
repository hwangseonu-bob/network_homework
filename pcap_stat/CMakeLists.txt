cmake_minimum_required(VERSION 3.14)
project(pcap_stat)

set(CMAKE_CXX_STANDARD 14)

add_executable(pcap_stat src/main.cpp)
target_link_libraries(pcap_stat pcap)