cmake_minimum_required(VERSION 3.0)

project(sciplot VERSION 0.1.0
        DESCRIPTION "A modern C++ scientific plotting library powered by gnuplot"
        HOMEPAGE_URL "https://github.com/sciplot")

set(CMAKE_CXX_STANDARD 11) # All targets in this project need to be compiled with a c++11 standard

include(cmake_install_generation.cmake)

add_subdirectory(examples)
add_subdirectory(tests)
