aux_source_directory(. source_files)
add_executable(hestina-unittest ${source_files})
target_link_libraries(hestina-unittest PRIVATE hestina-lib doctest::doctest)

include(${DOCTEST_SRCIPTS_CMAKE_DIR}/doctest.cmake)
doctest_discover_tests(hestina-unittest)
