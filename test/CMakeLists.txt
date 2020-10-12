cmake_minimum_required(VERSION 3.1)

project(type_conversion_iterator_test VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(.. type_conversion_iterator)

add_executable(type_conversion_iterator_test main.cpp)
target_link_libraries(type_conversion_iterator_test PUBLIC type_conversion_iterator)
