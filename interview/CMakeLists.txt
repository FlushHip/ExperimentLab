get_filename_component(root ${CMAKE_CURRENT_SOURCE_DIR} NAME)

foreach(year
    2023
)
    file(GLOB months
        LIST_DIRECTORIES true
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${year}
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/${year}/[1-9]*)

    foreach(month ${months})
        file(GLOB companies
            LIST_DIRECTORIES true
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${year}/${month}
            CONFIGURE_DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/${year}/${month}/*)

        foreach(company ${companies})
            file(GLOB nos
                LIST_DIRECTORIES true
                RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${year}/${month}/${company}
                CONFIGURE_DEPENDS
                ${CMAKE_CURRENT_SOURCE_DIR}/${year}/${month}/${company}/*)

            configure_file(help.cmake ${CMAKE_CURRENT_SOURCE_DIR}/${year}/${month}/${company}/CMakeLists.txt COPYONLY)

            add_subdirectory(${year}/${month}/${company})
        endforeach()
    endforeach()
endforeach()
