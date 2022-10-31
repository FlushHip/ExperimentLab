cmake_minimum_required(VERSION 3.12)

project(experimentlab VERSION 1.0.1)

# Include our cmake macros
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CMakeHelpers)

# project setting
set_property(GLOBAL
    PROPERTY USE_FOLDERS ON)
set_property(GLOBAL
    PROPERTY PREDEFINED_TARGETS_FOLDER "_CMakePredefinedTargets")

# Init BOOST_ROOT
if("${BOOST_ROOT}" STREQUAL "")
    file(TO_CMAKE_PATH "$ENV{BOOST_ROOT}" BOOST_ROOT)
    set(BOOST_ROOT ${BOOST_ROOT} CACHE PATH "BOOST_ROOT dependency path" FORCE)
endif()

# Set default cxx standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE 1)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install CACHE PATH "Install prefix directory" FORCE)
endif()

# CPack
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
include(CPack)

enable_testing()

# Add sub module
include_subdirs("effective-cpp")
add_subdirectory(yz)
include_subdirs(compiling)
add_subdirectory(tutorial)
include_subdirs(ideal)

# add_subdirectory(leetcode-cn)
add_subdirectory(qt)
add_subdirectory(3rd-party)
