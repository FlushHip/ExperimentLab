function(make_leetcode_target)
    foreach(ARG IN LISTS ARGN)
        set(FILE_PATH_TMP ${FILE_PATH_TMP}/${ARG})
    endforeach()

    string(REGEX REPLACE "^/" "" FILE_PATH_TMP ${FILE_PATH_TMP})

    file(GLOB_RECURSE FILES
        ${ROOT_FOLDER_ABSOLUTE}/${FRIST_FOLDER}/${subdir}/${FILE_PATH_TMP}/*.h
        ${ROOT_FOLDER_ABSOLUTE}/${FRIST_FOLDER}/${subdir}/${FILE_PATH_TMP}/*.hpp
        ${ROOT_FOLDER_ABSOLUTE}/${FRIST_FOLDER}/${subdir}/${FILE_PATH_TMP}/*.c
        ${ROOT_FOLDER_ABSOLUTE}/${FRIST_FOLDER}/${subdir}/${FILE_PATH_TMP}/*.cpp)
    source_group(TREE ${ROOT_FOLDER_ABSOLUTE}/${FRIST_FOLDER}/${subdir}/${FILE_PATH_TMP}
        FILES ${FILES})

    set(TARGET_NAME leetcode-cn_${FRIST_FOLDER}.${ARGV0}_${ARGV1})
    string(REGEX REPLACE "_$" "" TARGET_NAME ${TARGET_NAME})

    add_executable(${TARGET_NAME} ${FILES})
    target_link_libraries(${TARGET_NAME} PRIVATE enable_sanitize)
    target_include_directories(${TARGET_NAME}
        PRIVATE ${CMAKE_SOURCE_DIR}/template/LeetCode)
    set_target_properties(${TARGET_NAME}
        PROPERTIES FOLDER ${ROOT_FOLDER}/${FRIST_FOLDER}/${ARGV0})

    if(AppleClang)
        set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20)
    else()
        target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
    endif()
endfunction()

file(GLOB subdirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(SECOND_SUBDIR ${subdirs})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SECOND_SUBDIR})
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${SECOND_SUBDIR}/A)
            file(GLOB THIRD_SUBDIRS
                RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${SECOND_SUBDIR}
                ${CMAKE_CURRENT_SOURCE_DIR}/${SECOND_SUBDIR}/*)

            foreach(THIRD_SUBDIR ${THIRD_SUBDIRS})
                math(EXPR targets_cnt "${targets_cnt} + 1")
                make_leetcode_target(${SECOND_SUBDIR} ${THIRD_SUBDIR})
            endforeach()
        else()
            math(EXPR targets_cnt "${targets_cnt} + 1")
            make_leetcode_target(${SECOND_SUBDIR})
        endif()

        math(EXPR programs_cnt "${programs_cnt} + 1")
    endif()
endforeach()

set(programs_cnt ${programs_cnt} PARENT_SCOPE)
set(targets_cnt ${targets_cnt} PARENT_SCOPE)
