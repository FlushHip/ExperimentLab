configure_file(3rd-party.cmake download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/download)

if(result)
    message(FATAL_ERROR "CMake step for 3rd-party failed, result : ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/download)

if(result)
    message(FATAL_ERROR "build 3rd-party failed, result : ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}/build
    EXCLUDE_FROM_ALL)

set(DOCTEST_SRCIPTS_CMAKE_DIR ${CMAKE_CURRENT_BINARY_DIR}/src/scripts/cmake
    CACHE PATH "Path to cmake scripts folder for doctest")
mark_as_advanced(DOCTEST_SRCIPTS_CMAKE_DIR)
