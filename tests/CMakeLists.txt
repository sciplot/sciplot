file(GLOB_RECURSE FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.test.cxx)

add_executable(sciplot-cpptests ${FILES})
target_link_libraries(sciplot-cpptests sciplot)
target_include_directories(sciplot-cpptests PUBLIC ${PROJECT_SOURCE_DIR})

# Test for linking errors (due to missing inline specifiers)
add_subdirectory(testing-project)

# Add target tests that performs all C++ and Python tests
add_custom_target(tests
    COMMENT "Running C++ tests..."
    COMMAND $<TARGET_FILE:sciplot-cpptests>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
