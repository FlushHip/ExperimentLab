file(GLOB subdirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(subdir ${subdirs})
    if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${subdir}/src/CMakeLists.txt)
        add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/${subdir}/src
            ${CMAKE_CURRENT_BINARY_DIR}/${subdir}/build
            EXCLUDE_FROM_ALL)

    elseif(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()
