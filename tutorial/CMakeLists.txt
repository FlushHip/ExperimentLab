option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_subdirectory(maths)

add_executable(tutorial_main tutorial_main.cpp)
set_target_properties(tutorial_main PROPERTIES FOLDER "tutorial")

configure_file(config.h.in config.h)

target_include_directories(tutorial_main PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(tutorial_main PRIVATE tutorial_maths)

if (WIN32)
    add_custom_command(TARGET tutorial_main POST_BUILD
        COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:tutorial_maths> $<TARGET_FILE_DIR:tutorial_main>
        COMMENT "copy dynamic lib to workdir to run")
endif ()

install(TARGETS tutorial_main DESTINATION bin)
install(FILES $<$<PLATFORM_ID:Windows>:$<TARGET_PDB_FILE:tutorial_main>> DESTINATION bin OPTIONAL)

add_test(NAME Runs COMMAND tutorial_main 25)

add_test(NAME Usage COMMAND tutorial_main)
set_tests_properties(Usage PROPERTIES
    FAIL_REGULAR_EXPRESSION "Usage:.*number"
    WILL_FAIL TRUE)

add_test(NAME Timeout COMMAND tutorial_main 5)
set_tests_properties(Timeout PROPERTIES
    TIMEOUT 3)
