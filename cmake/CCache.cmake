# Speed up repeated and similar compilation operations with this cmake module.
#
# This module tries first to find if ccache is installed in the system.
# If found, the cmake variables CMAKE_C_COMPILER_LAUNCHER and
# CMAKE_CXX_COMPILER_LAUNCHER are then set to the ccache program.
# As a result, ccache will be used, together with the chosen
# (or default) compiler to cache the compilations. Subsequent
# compilations can then be performed much faster (e.g., changing
# branches).
#
# Add the option -DCCACHE_IGNORE=TRUE to ignore ccache speed up.
#
# *** IMPORTANT ***
# To use this module, add:
#
#     include(CCache)
#
# before the project command. For example:
#
#     cmake_minimum_required(VERSION 3.0)
#     include(CCache)
#     project(HelloWorld)

find_program(CCACHE_PROGRAM ccache)

if(NOT CCACHE_IGNORE AND CCACHE_PROGRAM)
    message(STATUS "CCache: Found ccache installed.")
    message(STATUS "CCache: Using ccache to potentially speed up the build operation.")
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
else()
    message(STATUS "CCache: Could not find ccache. Install it to speed up the build operation.")
endif()
