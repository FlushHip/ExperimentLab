set(TARGET_NAME lib_static_variable_lib)

add_library(${TARGET_NAME} STATIC lib.h lib.cpp)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "advanced compiling")
