if(UNIX)
    file(GLOB_RECURSE FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.in)

    foreach(FILE ${FILES})
        get_filename_component(FILENAME ${FILE} NAME_WE)
        configure_file(${FILE} ${CMAKE_CURRENT_BINARY_DIR}/${FILENAME} @ONLY)
    endforeach()
endif()
