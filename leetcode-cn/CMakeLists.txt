string(REGEX REPLACE "/$" "" CURRENT_FOLDER_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(CURRENT_FOLDER ${CURRENT_FOLDER_ABSOLUTE} NAME)

file(GLOB FRIST_SUBDIRS
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/*)

function(make_leetcode_target)
    foreach(ARG IN LISTS ARGN)
        set(FILE_PATH_TMP ${FILE_PATH_TMP}/${ARG})
    endforeach()

    string(REGEX REPLACE "^/" "" FILE_PATH_TMP ${FILE_PATH_TMP})

    file(GLOB_RECURSE FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_PATH_TMP}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_PATH_TMP}/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_PATH_TMP}/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_PATH_TMP}/*.cpp)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_PATH_TMP}
        FILES ${FILES})

    set(TARGET_NAME leetcode-cn_${ARGV0}.${ARGV1}_${ARGV2})
    string(REGEX REPLACE "_$" "" TARGET_NAME ${TARGET_NAME})

    add_executable(${TARGET_NAME} ${FILES})
    target_include_directories(${TARGET_NAME}
        PRIVATE ${CMAKE_SOURCE_DIR}/template/LeetCode)
    set_target_properties(${TARGET_NAME}
        PROPERTIES FOLDER ${CURRENT_FOLDER}/${ARGV0}/${ARGV1})

    if(AppleClang)
        set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17)
    else()
        target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
    endif()
endfunction()

foreach(FRIST_SUBDIR ${FRIST_SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR})
        file(GLOB SECOND_SUBDIRS
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}/*)

        set(programs_cnt 0)
        set(targets_cnt 0)

        foreach(SECOND_SUBDIR ${SECOND_SUBDIRS})
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}/${SECOND_SUBDIR}/A)
                file(GLOB THIRD_SUBDIRS
                    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}/${SECOND_SUBDIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}/${SECOND_SUBDIR}/*)

                foreach(THIRD_SUBDIR ${THIRD_SUBDIRS})
                    math(EXPR targets_cnt "${targets_cnt} + 1")
                    make_leetcode_target(${FRIST_SUBDIR} ${SECOND_SUBDIR} ${THIRD_SUBDIR})
                endforeach()
            else()
                math(EXPR targets_cnt "${targets_cnt} + 1")
                make_leetcode_target(${FRIST_SUBDIR} ${SECOND_SUBDIR})
            endif()

            math(EXPR programs_cnt "${programs_cnt} + 1")
        endforeach()

        message(STATUS "Total \"${CURRENT_FOLDER}/${FRIST_SUBDIR}\" <${programs_cnt} programs, ${targets_cnt} targets> generated")
    endif()
endforeach()
