# Copy and configure the doxygen configuration files to binary dir
configure_file(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doxyfile @ONLY)

# Add target "doxygen" for building doxygen api docs
add_custom_target(doxygen
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/css ${CMAKE_CURRENT_BINARY_DIR}/html/css
#   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/fonts ${CMAKE_CURRENT_BINARY_DIR}/html/fonts
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/js ${CMAKE_CURRENT_BINARY_DIR}/html/js
  COMMAND doxygen doxyfile
#   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/img ${CMAKE_CURRENT_BINARY_DIR}/html/img
#   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/bib ${CMAKE_CURRENT_BINARY_DIR}/html/bib
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
