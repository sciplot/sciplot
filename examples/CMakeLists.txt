# Collect all cpp files in the current directory
file(GLOB CPPFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# For each cpp file, generate an executable target
foreach(CPPFILE ${CPPFILES})
    get_filename_component(CPPNAME ${CPPFILE} NAME_WE)
    add_executable(${CPPNAME} ${CPPFILE})
    target_link_libraries(${CPPNAME} PUBLIC sciplot)
endforeach()

# Add target `examples` for building all examples above (e.g., make examples)
add_custom_target(examples
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
