cmake_minimum_required(VERSION 3.14)
project(vending_machine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)

add_executable(vending_machine main.cpp widget.h widget.cpp widget.ui ui_widget.h)
target_link_libraries(vending_machine Qt5::Widgets)