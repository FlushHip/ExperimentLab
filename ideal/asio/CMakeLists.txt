configure_file(spdlog.cmake spdlog-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/spdlog-download)
if(result)
    message(FATAL_ERROR "CMake step for spdlog failed, result : ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/spdlog-download)
if(result)
    message(FATAL_ERROR "build spdlog failed, result : ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/spdlog-src
    ${CMAKE_CURRENT_BINARY_DIR}/spdlog-build
    EXCLUDE_FROM_ALL)

file (GLOB subdirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach (subdir ${subdirs})
    if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
        add_subdirectory(${subdir})
    endif ()
endforeach ()
