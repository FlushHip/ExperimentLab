file(GLOB SOURCE_FILES *.c *.cpp)
file(GLOB HEADER_FILES *.h *.hpp)

init_target()

build_executable(${TARGET_NAME} EXCLUDE_FROM_ALL ${SOURCE_FILES} ${HEADER_FILES})

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

target_link_libraries(${TARGET_NAME} PRIVATE $<$<NOT:$<PLATFORM_ID:Windows>>:pthread> argagg::argagg)

set(xpdf_tools_root ${CMAKE_BINARY_DIR}/3rd-party/xpdf-tools-win/files/bin64)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND}
    ARGS -E make_directory
    $<TARGET_FILE_DIR:${TARGET_NAME}>/inc
    COMMAND_EXPAND_LISTS)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND}
    ARGS -E copy
    ${xpdf_tools_root}/pdftopng.exe
    ${xpdf_tools_root}/xpdfrc
    $<TARGET_FILE_DIR:${TARGET_NAME}>/inc
    COMMAND_EXPAND_LISTS)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND}
    ARGS -E copy_directory
    ${xpdf_tools_root}/fonts
    $<TARGET_FILE_DIR:${TARGET_NAME}>/inc/fonts
    COMMAND_EXPAND_LISTS)

install(TARGETS ${TARGET_NAME}
    CONFIGURATIONS Debug Release
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION bin)

install(PROGRAMS
    ${xpdf_tools_root}/pdftopng.exe
    DESTINATION bin/inc
)
install(FILES
    ${xpdf_tools_root}/xpdfrc
    DESTINATION bin/inc
)
install(DIRECTORY
    ${xpdf_tools_root}/fonts
    DESTINATION bin/inc
)
