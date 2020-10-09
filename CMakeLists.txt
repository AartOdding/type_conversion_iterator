cmake_minimum_required(VERSION 3.0)

project(type_conversion_iterator VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)


add_library(type_conversion_iterator STATIC)

target_include_directories(type_conversion_iterator PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
