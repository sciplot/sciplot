cmake_minimum_required(VERSION 3.12)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CCache)

project(sciplot VERSION 0.3.1
    DESCRIPTION "A modern C++ scientific plotting library powered by gnuplot"
    HOMEPAGE_URL "https://sciplot.github.io"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(SCIPLOT_BUILD_EXAMPLES "Build examples" ON)
option(SCIPLOT_BUILD_TESTS "Build tests" ON)
option(SCIPLOT_BUILD_DOCS "Build documentation" ON)

# Set compile options in case of MSVC
if(MSVC)
    add_compile_options(/MP)  # enable parallel build
    add_definitions("/wd4267 /wd4244")  # ignore silly warnings related to size_t/int and site_t/double conversions
endif()

if(SCIPLOT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(SCIPLOT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(SCIPLOT_BUILD_DOCS)
    add_subdirectory(docs)
endif()

add_subdirectory(scripts)

include(cmake_install_generation.cmake)
