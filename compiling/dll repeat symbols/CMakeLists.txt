add_subdirectory(first)
add_subdirectory(second)
add_subdirectory(third)

set(TARGET_NAME dll_repeat_symbols_main)

add_executable(${TARGET_NAME}_a main.cpp)
set_target_properties(${TARGET_NAME}_a PROPERTIES FOLDER "advanced compiling")

target_link_libraries(${TARGET_NAME}_a
    PRIVATE dll_repeat_symbols_first
    PRIVATE dll_repeat_symbols_second
)
target_compile_definitions(${TARGET_NAME}_a
    PRIVATE CASE_1)

add_executable(${TARGET_NAME}_b main.cpp)
set_target_properties(${TARGET_NAME}_b PROPERTIES FOLDER "advanced compiling")

target_link_libraries(${TARGET_NAME}_b
    PRIVATE dll_repeat_symbols_second
    PRIVATE dll_repeat_symbols_first
)
target_compile_definitions(${TARGET_NAME}_b
    PRIVATE CASE_1)

add_executable(${TARGET_NAME}_c main.cpp)
set_target_properties(${TARGET_NAME}_c PROPERTIES FOLDER "advanced compiling")

target_link_libraries(${TARGET_NAME}_c
    PRIVATE dll_repeat_symbols_first
    PRIVATE dll_repeat_symbols_third
)
target_compile_definitions(${TARGET_NAME}_c
    PRIVATE CASE_2)

add_executable(${TARGET_NAME}_d main.cpp)
set_target_properties(${TARGET_NAME}_d PROPERTIES FOLDER "advanced compiling")

target_link_libraries(${TARGET_NAME}_d
    PRIVATE dll_repeat_symbols_third
    PRIVATE dll_repeat_symbols_first
)
target_compile_definitions(${TARGET_NAME}_d
    PRIVATE CASE_2)
