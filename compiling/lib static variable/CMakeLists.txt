add_subdirectory(first)
add_subdirectory(second)
add_subdirectory(third)

set(TARGET_NAME lib_static_variable)

add_executable(${TARGET_NAME} main.cpp)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "advanced compiling")

target_link_libraries(${TARGET_NAME}
    PRIVATE lib_static_variable_lib
    PRIVATE lib_static_variable_dll1
    PRIVATE lib_static_variable_dll2
)
