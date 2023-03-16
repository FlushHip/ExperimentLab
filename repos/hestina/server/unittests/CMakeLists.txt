aux_source_directory(. source_files)

include(${DOCTEST_SRCIPTS_CMAKE_DIR}/doctest.cmake)

foreach(s_file ${source_files})
    get_filename_component(t_suffix ${s_file} NAME_WE)
    add_executable(hestina-${t_suffix} ${s_file})
    target_sources(hestina-${t_suffix} PRIVATE detail/logger_init.cpp)
    target_link_libraries(hestina-${t_suffix} PRIVATE hestina-lib doctest::doctest_with_main)
    doctest_discover_tests(hestina-${t_suffix})
endforeach()
