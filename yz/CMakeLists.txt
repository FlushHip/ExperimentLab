file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*")
foreach(SUBDIR ${SUBDIRS})
    # skip .template and files
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})
        message(DEBUG "** " ${SUBDIR})
        include_subdirs(${SUBDIR})
    endif()
endforeach()
