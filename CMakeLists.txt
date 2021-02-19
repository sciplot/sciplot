cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CCache)

project(sciplot VERSION 0.2.0
    DESCRIPTION "A modern C++ scientific plotting library powered by gnuplot"
    HOMEPAGE_URL "https://sciplot.github.io")

set(CMAKE_CXX_STANDARD 17)

include(cmake_install_generation.cmake)

option(SCIPLOT_BUILD_EXAMPLES "Build examples" ON)
option(SCIPLOT_BUILD_TESTS "Build tests" ON)
option(SCIPLOT_BUILD_DOCS "Build documentation" ON)

if(SCIPLOT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(SCIPLOT_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(SCIPLOT_BUILD_DOCS)
    add_subdirectory(docs)
endif()

add_subdirectory(scripts)

