file (GLOB SOURCE_FILES *.c *.cpp)
file (GLOB HEADER_FILES *.h *.hpp)

init_target ()

build_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

set(OUTPUT_AUX_DIR ${CMAKE_CURRENT_BINARY_DIR})
if (MSVC)
    set(OUTPUT_AUX_DIR ${OUTPUT_AUX_DIR}/${CMAKE_BUILD_TYPE})
endif ()

add_custom_command(OUTPUT ${OUTPUT_AUX_DIR}/in.dat
    COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/in.dat ${OUTPUT_AUX_DIR}
    COMMENT "copy ${CMAKE_CURRENT_SOURCE_DIR}/in.dat for freopen to debug stdin"
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/in.dat
    VERBATIM)

add_custom_target(${TARGET_NAME}_AUX
    DEPENDS ${OUTPUT_AUX_DIR}/in.dat
    VERBATIM)

get_target_property(DIR ${TARGET_NAME} FOLDER)
set_target_properties(${TARGET_NAME}_AUX PROPERTIES FOLDER ${DIR})

add_dependencies(${TARGET_NAME} ${TARGET_NAME}_AUX)

set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${TARGET_NAME}>)
target_compile_options(${TARGET_NAME} PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>,/wd4996,-Wno-deprecated-declarations>)
