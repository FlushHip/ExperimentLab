aux_source_directory(. source_files)

foreach(s_file ${source_files})
    get_filename_component(t_suffix ${s_file} NAME_WE)
    add_executable(hestina-${t_suffix} ${s_file})
    target_link_libraries(hestina-${t_suffix} PRIVATE hestina-lib)
endforeach()
