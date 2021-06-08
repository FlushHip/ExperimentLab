add_library(dynamic_lib_items_lib1 SHARED lib1.cpp)
set_target_properties(dynamic_lib_items_lib1 PROPERTIES FOLDER "advanced compiling")

#set(CMAKE_CXX_VISIBILITY_PRESET hidden)
#set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include(GenerateExportHeader)
generate_export_header(dynamic_lib_items_lib1)

target_include_directories(dynamic_lib_items_lib1 PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(dynamic_lib_items_lib1 PRIVATE dynamic_lib_items_lib1_EXPORTS)

target_compile_options(dynamic_lib_items_lib1 PUBLIC $<$<PLATFORM_ID:Linux>:-m32>)
target_link_options(dynamic_lib_items_lib1 PUBLIC $<$<PLATFORM_ID:Linux>:-m32>)