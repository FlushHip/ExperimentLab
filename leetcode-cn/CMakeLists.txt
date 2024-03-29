string(REGEX REPLACE "/$" "" ROOT_FOLDER_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR})
get_filename_component(ROOT_FOLDER ${ROOT_FOLDER_ABSOLUTE} NAME)

set(programs_cnt_total 0)
set(targets_cnt_total 0)
set(ctest_timeout_cnt 5)

# sanitize
add_library(enable_sanitize INTERFACE)
target_compile_options(enable_sanitize INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
    -fsanitize=address
    -fsanitize=undefined

    -O0
    -fno-omit-frame-pointer
    -fno-optimize-sibling-calls
    -fno-common>
)
target_link_libraries(enable_sanitize INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:asan ubsan>)

# warnings as error
add_library(enable_warnings_as_error INTERFACE)
target_compile_options(enable_warnings_as_error INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

add_subdirectory(Interview-17)
add_subdirectory(Interview-04)
add_subdirectory(LCP)
add_subdirectory(Offer)
add_subdirectory(primeval)

message(STATUS)
message(STATUS "\"All ${ROOT_FOLDER}\" <<${programs_cnt_total} programs, ${targets_cnt_total} targets>> generated")
