cmake_minimum_required(VERSION 3.14)
project(pcap_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(pcap_test main.cpp network_addr.h packet.h packet.cpp network_addr.cpp)
target_link_libraries(pcap_test pcap)