include_directories(${CMAKE_SOURCE_DIR})

add_library(catch OBJECT catch.hpp catch.cpp)

add_executable(tests tests.cpp $<TARGET_OBJECTS:catch>)
