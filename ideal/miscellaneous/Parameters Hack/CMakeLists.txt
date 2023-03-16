file (GLOB SOURCE_FILES *.c *.cpp)
file (GLOB HEADER_FILES *.h *.hpp)

init_target ()

build_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

add_test(ParameterHack ${TARGET_NAME} 5 4 3 6 1)
set_tests_properties(ParameterHack PROPERTIES
    PASS_REGULAR_EXPRESSION "1 3 4 5 6")