file(GLOB SOURCE_FILES *.c *.cpp)
file(GLOB HEADER_FILES *.h *.hpp)

init_target()

build_executable(${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/in.dat
    COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/in.dat ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "copy ${CMAKE_CURRENT_SOURCE_DIR}/in.dat for freopen to debug stdin"
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/in.dat
    VERBATIM)

add_custom_target(${TARGET_NAME}_AUX
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/in.dat
    VERBATIM)

add_dependencies(${TARGET_NAME} ${TARGET_NAME}_AUX)

target_link_libraries(${TARGET_NAME} PRIVATE $<$<NOT:$<PLATFORM_ID:Windows>>:pthread> prettyprint::prettyprint)
