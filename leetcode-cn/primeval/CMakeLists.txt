
string(REGEX REPLACE "/$" "" FRIST_FOLDER_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(FRIST_FOLDER ${FRIST_FOLDER_ABSOLUTE} NAME)

set(programs_cnt 0)
set(targets_cnt 0)

file(GLOB subdirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(subdir ${subdirs})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
        configure_file(help.cmake ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt COPYONLY)
        add_subdirectory(${subdir})
    endif()
endforeach()

message(STATUS "  Total \"${ROOT_FOLDER}/${FRIST_FOLDER}\" <${programs_cnt} programs, ${targets_cnt} targets> generated")

math(EXPR targets_cnt_total "${targets_cnt} + ${targets_cnt_total}")
math(EXPR programs_cnt_total "${programs_cnt} + ${programs_cnt_total}")
set(programs_cnt_total ${programs_cnt_total} PARENT_SCOPE)
set(targets_cnt_total ${targets_cnt_total} PARENT_SCOPE)
