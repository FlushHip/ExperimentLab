add_subdirectory(lib1)
#add_subdirectory(lib2)

add_executable(dynamic_lib_items_main main.cpp)
set_target_properties(dynamic_lib_items_main PROPERTIES FOLDER "advanced compiling")

target_link_libraries(dynamic_lib_items_main PRIVATE dynamic_lib_items_lib1)

if (WIN32)
    add_custom_command(TARGET dynamic_lib_items_main POST_BUILD COMMAND ${CMAKE_COMMAND}
        ARGS -E copy $<TARGET_FILE:dynamic_lib_items_lib1> $<TARGET_FILE_DIR:dynamic_lib_items_main>
        COMMENT "copy dynamic lib to workdir to run")
endif ()