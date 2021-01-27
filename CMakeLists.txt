cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CCache)

project(sciplot VERSION 0.1.0
    DESCRIPTION "A modern C++ scientific plotting library powered by gnuplot"
    HOMEPAGE_URL "https://github.com/sciplot")

set(CMAKE_CXX_STANDARD 11)

include(cmake_install_generation.cmake)

add_subdirectory(examples)
add_subdirectory(tests)
add_subdirectory(scripts)
