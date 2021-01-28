file(GLOB_RECURSE FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.test.cxx)

add_executable(sciplot-cpptests ${FILES})
target_link_libraries(sciplot-cpptests sciplot)
target_include_directories(sciplot-cpptests PUBLIC ${PROJECT_SOURCE_DIR})
