get_filename_component(year ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB months
    LIST_DIRECTORIES true
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/[1-9]*)

foreach(month ${months})
    file(GLOB companies
        LIST_DIRECTORIES true
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${month}
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/${month}/*)

    foreach(company ${companies})
        set(tmp ${CMAKE_CURRENT_SOURCE_DIR}/${month}/${company})
        file(GLOB nos
            LIST_DIRECTORIES true
            RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${month}/${company}
            CONFIGURE_DEPENDS
            ${CMAKE_CURRENT_SOURCE_DIR}/${month}/${company}/?)

        foreach(no ${nos})
            set(target ${root}.${year}-${month}_${company}.${no})
            file(GLOB source_files
                ${CMAKE_CURRENT_SOURCE_DIR}/${month}/${company}/${no}/*.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/${month}/${company}/${no}/*.hpp)
            add_executable(${target} ${source_files})
            target_compile_features(${target}
                PRIVATE cxx_std_20)
            target_compile_definitions(${target}
                PRIVATE $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
                DBG_MACRO_NO_WARNING)
            target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR}/template/Interview/dbg-macro)
            target_compile_options(${target} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/wd4819>)

            # freopen std::cin to in.dat
            set(freopen_path ${CMAKE_CURRENT_SOURCE_DIR}/${month}/${company}/${no})
            configure_file(${CMAKE_SOURCE_DIR}/template/Interview/dummy.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/${month}/${company}/${no}/dummy.cpp)
            target_sources(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${month}/${company}/${no}/dummy.cpp)

            source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/${month}/${company}/${no}
                FILES ${source_files})
            set_target_properties(${target}
                PROPERTIES FOLDER ${root}/${year}/${month}/${company})
        endforeach()
    endforeach()
endforeach()
