cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CCache)

project(sciplot VERSION 0.2.0
    DESCRIPTION "A modern C++ scientific plotting library powered by gnuplot"
    HOMEPAGE_URL "https://github.com/sciplot")

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
    add_subdirectory(doxygen)

    # Add target "website" for building website documentation
    add_custom_target(website
      COMMAND mkdocs build
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/doxygen/html/ ${CMAKE_SOURCE_DIR}/site/api/
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

    add_dependencies(website doxygen)
endif()

add_subdirectory(scripts)

