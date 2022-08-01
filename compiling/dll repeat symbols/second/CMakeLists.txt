set(TARGET_NAME dll_repeat_symbols_second)

add_library(${TARGET_NAME} SHARED lib.h lib.cpp)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "advanced compiling")

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include(GenerateExportHeader)
generate_export_header(${TARGET_NAME}
    EXPORT_MACRO_NAME API_EXPORT)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(${TARGET_NAME} PRIVATE ${TARGET_NAME}_EXPORTS)
