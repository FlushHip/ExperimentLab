string(REGEX REPLACE "/$" "" CURRENT_FOLDER_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(CURRENT_FOLDER ${CURRENT_FOLDER_ABSOLUTE} NAME)

file(GLOB FRIST_SUBDIRS
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(FRIST_SUBDIR ${FRIST_SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR})
        file(GLOB SECOND_SUBDIRS
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}/*)

        foreach(SECOND_SUBDIR ${SECOND_SUBDIRS})
            set(TARGET_NAME LeetCode_${FRIST_SUBDIR}.${SECOND_SUBDIR})

            file(GLOB_RECURSE FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}/${SECOND_SUBDIR}/*.h
                ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}/${SECOND_SUBDIR}/*.hpp
                ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}/${SECOND_SUBDIR}/*.c
                ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}/${SECOND_SUBDIR}/*.cpp)

            add_executable(${TARGET_NAME} ${FILES})
            target_include_directories(${TARGET_NAME}
                PRIVATE ${CMAKE_SOURCE_DIR}/template/LeetCode)

            if(AppleClang)
                set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17)
            else()
                target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
            endif()

            set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${CURRENT_FOLDER}/${FRIST_SUBDIR})
            source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/${FRIST_SUBDIR}/${SECOND_SUBDIR} FILES ${FILES})
        endforeach()
    endif()
endforeach()
