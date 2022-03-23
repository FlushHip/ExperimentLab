file (GLOB SOURCE_FILES *.c *.cpp)
file (GLOB HEADER_FILES *.h *.hpp)

init_target ()

build_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/in.dat $<TARGET_FILE_DIR:${TARGET_NAME}>/
    COMMENT "copy in.dat for freopen to debug stdin")

target_compile_options(${TARGET_NAME} PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>,/wd4996,-Wno-deprecated-declarations>)
