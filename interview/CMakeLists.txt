get_filename_component(root ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(output_lines " " "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

set(all_sessions 0)
set(all_targets 0)

foreach(year
    2023
)
    file(GLOB months
        LIST_DIRECTORIES true
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${year}
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/${year}/[0-1][0-9])

    set(total_companies 0)
    set(total_targets 0)

    list(REVERSE months)

    foreach(month ${months})
        file(GLOB companies
            LIST_DIRECTORIES true
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${year}/${month}
            CONFIGURE_DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/${year}/${month}/*)

        list(LENGTH companies cnt_company)
        math(EXPR total_companies "${total_companies} + ${cnt_company}")

        set(cnt_targets 0)

        foreach(company ${companies})
            file(GLOB nos
                LIST_DIRECTORIES true
                RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${year}/${month}/${company}
                CONFIGURE_DEPENDS
                ${CMAKE_CURRENT_SOURCE_DIR}/${year}/${month}/${company}/*)

            configure_file(help.cmake ${CMAKE_CURRENT_SOURCE_DIR}/${year}/${month}/${company}/CMakeLists.txt COPYONLY)

            add_subdirectory(${year}/${month}/${company})
        endforeach()

        math(EXPR total_targets "${total_targets} + ${cnt_targets}")

        list(APPEND output_lines "    |   #${month}# == < <sessions : '${cnt_company}'> <targets : '${cnt_targets}'> >")
    endforeach()

    list(APPEND output_lines "    @${year}@ == <total sessions : '${total_companies}'> <total targets : '${total_targets}'>")

    math(EXPR all_sessions "${all_sessions} + ${total_companies}")
    math(EXPR all_targets "${all_targets} + ${total_targets}")
endforeach()

list(APPEND output_lines
    "-----------------------------------------------------------------------"
    "  Interview summary : < <all_sessions : '${all_sessions}'> <all_targets : '${all_targets}'> >"
    "-----------------------------------------------------------------------")

list(REVERSE output_lines)

foreach(line ${output_lines})
    message(STATUS ${line})
endforeach()
