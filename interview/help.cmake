file(GLOB nos
    LIST_DIRECTORIES true
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/*)

list(LENGTH nos cnt_nos)
math(EXPR cnt_targets "${cnt_targets} + ${cnt_nos} - 1")

set(cnt_targets ${cnt_targets} PARENT_SCOPE)

foreach(no ${nos})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${no})
        set(target ${root}.${year}-${month}_${company}.${no})
        file(GLOB source_files
            ${CMAKE_CURRENT_SOURCE_DIR}/${no}/*.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/${no}/*.hpp)
        add_executable(${target} ${source_files})
        target_compile_features(${target}
            PRIVATE cxx_std_20)
        target_compile_definitions(${target}
            PRIVATE $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
            DBG_MACRO_NO_WARNING)
        target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR}/template/Interview/dbg-macro)
        target_compile_options(${target} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/wd4819>)

        # freopen std::cin to in.dat
        set(freopen_path ${CMAKE_CURRENT_SOURCE_DIR}/${no})
        configure_file(${CMAKE_SOURCE_DIR}/template/Interview/dummy.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/${no}/dummy.cpp)
        target_sources(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${no}/dummy.cpp)

        source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/${no}
            FILES ${source_files})
        set_target_properties(${target}
            PROPERTIES FOLDER ${root}/${year}/${month}/${company})

        add_test(${target} ${target})
        set_tests_properties(${target}
            PROPERTIES TIMEOUT 1
            LABELS interview)
    endif()
endforeach()
