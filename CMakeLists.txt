cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(rlcpp)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}")

include_directories ("${PROJECT_SOURCE_DIR}/dumb")
add_subdirectory (dumb) 
include_directories ("${PROJECT_SOURCE_DIR}/timer")
add_subdirectory (timer)

add_executable(rlcpp ${PROJECT_SOURCE_DIR}/main.cc)

target_link_libraries (rlcpp dumb timer)
