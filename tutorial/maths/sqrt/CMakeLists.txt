
add_executable(tutorial_math_make_sqrt_table 
    table_sqrt_10_make.cpp)
set_target_properties(tutorial_math_make_sqrt_table PROPERTIES
    FOLDER "tutorial/math"
    EchoString "aux target to generate sqrt table"
    PROJECT_LABEL tutorial_math_sqrt_aux)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/table.h
    COMMAND tutorial_math_make_sqrt_table ${CMAKE_CURRENT_BINARY_DIR}/table.h
    DEPENDS tutorial_math_make_sqrt_table
    VERBATIM)

add_library(tutorial_math_sqrt STATIC
    sqrt.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/table.h)
set_target_properties(tutorial_math_sqrt PROPERTIES
    FOLDER "tutorial/math"
    POSITION_INDEPENDENT_CODE ON)
target_include_directories(tutorial_math_sqrt PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

include(CheckSymbolExists)
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "math.h" HAVE_EXP)
if(HAVE_LOG AND HAVE_EXP)
    target_compile_definitions(tutorial_math_sqrt PRIVATE HAVE_LOG HAVE_EXP)
endif()

install(TARGETS tutorial_math_sqrt DESTINATION lib/static)
install(FILES sqrt.h DESTINATION include/math/sqrt)