cmake_minimum_required(VERSION 3.12)

project(converting_view VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(converting_view converting_view.hpp main.cpp)


target_include_directories(converting_view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
