macro (include_subdirs PARENT)
    file (GLOB SDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${PARENT}/*")
    foreach (SUBDIR ${SDIRS})
        if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}/CMakeLists.txt")
            add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}")
        endif ()
    endforeach ()
endmacro()

# Initialize target.
macro (init_target)
    string(REGEX REPLACE "/$" "" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})
    string(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CURRENT_FOLDER})

    get_filename_component(SECOND_FOLDER_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
    string(REGEX REPLACE ".*/(.*)" "\\1" SECOND_FOLDER ${SECOND_FOLDER_ABSOLUTE})

    get_filename_component(THIRD_FOLDER_ABSOLUTE ${SECOND_FOLDER_ABSOLUTE} DIRECTORY)
    string(REGEX REPLACE ".*/(.*)" "\\1" THIRD_FOLDER ${THIRD_FOLDER_ABSOLUTE})

    string(REGEX REPLACE " " "_" TARGET_NAME ${CURRENT_FOLDER})

    if(${THIRD_FOLDER_ABSOLUTE} STREQUAL ${CMAKE_SOURCE_DIR})
        string(TOLOWER ${TARGET_NAME} TARGET_NAME)
    endif()
    message (DEBUG "  | ** " ${TARGET_NAME})

    # Include our own module path. This makes #include "x.h"
    # work in project subfolders to include the main directory headers.
    include_directories (${CMAKE_CURRENT_SOURCE_DIR})
endmacro ()

# Build executable for executables
macro (build_executable TARGET_NAME)
    set (TARGET_LIB_TYPE "EXECUTABLE")
    # message (STATUS "-- Build Type:")
    # message (STATUS "       " ${TARGET_LIB_TYPE})

    add_executable (${TARGET_NAME} ${ARGN})

    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ARGN})

    if(NOT ${THIRD_FOLDER_ABSOLUTE} STREQUAL ${CMAKE_SOURCE_DIR})
        set_target_properties (${TARGET_NAME} PROPERTIES FOLDER "${THIRD_FOLDER}/${SECOND_FOLDER}")
    else()
        set_target_properties (${TARGET_NAME} PROPERTIES FOLDER "${SECOND_FOLDER}")
    endif()
endmacro ()