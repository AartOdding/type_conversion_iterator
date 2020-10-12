cmake_minimum_required(VERSION 3.1)

project(type_conversion_iterator VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)


add_library(type_conversion_iterator INTERFACE)

target_sources(type_conversion_iterator INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/tci/conversions/get_pointer_to_second.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/tci/conversions/get_pointer.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/tci/type_conversion_iterator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/tci/views.hpp"
)

target_include_directories(type_conversion_iterator INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
