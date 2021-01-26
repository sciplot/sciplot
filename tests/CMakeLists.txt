add_library(catch OBJECT catch.hpp catch.cpp)
target_include_directories(catch PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(tests tests.cpp $<TARGET_OBJECTS:catch>)
target_link_libraries(tests PUBLIC sciplot)
