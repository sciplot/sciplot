include(GNUInstallDirs)

# create an interface library which will contain all necessary information for compile and install
add_library(sciplot INTERFACE)

# Set sciplot compilation features to be propagated to client code.
target_compile_features(sciplot INTERFACE cxx_std_17)

target_include_directories(sciplot INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

# here begins the cmake export magic

# First we create an export record
# This will write our listed targets to a file in the build directory, and optionally provide ta namespace (sciplot).
export(TARGETS sciplot NAMESPACE sciplot:: FILE sciplotTargets.cmake)

# To allow CMake to find this package, export the package to the CMake Package Registry
export(PACKAGE sciplot)

## Install header files
install(DIRECTORY sciplot TYPE INCLUDE)

# Install the target and enable export generation
install(TARGETS sciplot
        EXPORT sciplot-export
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

# Install the generated export
install(EXPORT sciplot-export
        FILE sciplotTargets.cmake
        NAMESPACE sciplot::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${CMAKE_PROJECT_NAME}/
        )

# generate file necessary to call find_package(sciplot) (sciplotConfig.cmake and sciplotConfigVersion.cmake)

include(CMakePackageConfigHelpers)
configure_package_config_file(
        ${CMAKE_SOURCE_DIR}/cmake/PackageConfigTemplates/sciplotConfig.cmake.in
        ${CMAKE_BINARY_DIR}/sciplotConfig.cmake
        INSTALL_DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/${CMAKE_PROJECT_NAME}/
)

write_basic_package_version_file(
        sciplotConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY
        SameMajorVersion
)

# install generated files

install(FILES
        ${CMAKE_BINARY_DIR}/sciplotConfig.cmake
        ${CMAKE_BINARY_DIR}/sciplotConfigVersion.cmake
        DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/${CMAKE_PROJECT_NAME}/
        )
