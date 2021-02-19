# Configure the doxygen configuration file
configure_file(api/doxyfile ${CMAKE_CURRENT_BINARY_DIR}/api/doxyfile @ONLY)

# Add target `docs-api` for building doxygen api docs
add_custom_target(docs-api
    COMMAND doxygen doxyfile
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/api")

# Add target `docs` for building the entire documentation
add_custom_target(docs
    COMMAND mkdocs build
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_BINARY_DIR}/api/html/ ${CMAKE_CURRENT_SOURCE_DIR}/site/api/
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Ensure target `docs-api` is build before target `docs`
add_dependencies(docs docs-api)
