cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cpptool LANGUAGES CXX)

file(GLOB_RECURSE testpath ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

add_executable(cpptool ${testpath})

set_target_properties(cpptool PROPERTIES
#        PREFIX lib
        OUTPUT_NAME testoutput)

target_include_directories(cpptool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
