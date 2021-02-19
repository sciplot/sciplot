cmake_minimum_required(VERSION 3.0)

project(testing-project)

add_executable(testing-project main.cpp util.cpp)

target_include_directories(testing-project PUBLIC ${CMAKE_SOURCE_DIR})
