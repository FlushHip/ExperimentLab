set(TARGET_NAME hestina-lib)

add_library(${TARGET_NAME} STATIC)

foreach(dir
    "log"
    "net"
    "pool"
    "timer")
    set(files)
    aux_source_directory(${dir} files)
    list(APPEND source_files ${files})
endforeach()

file(GLOB_RECURSE header_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.hpp" "*.h")

target_sources(${TARGET_NAME}
    PRIVATE ${source_files}

    # only for vscode-tools
    ${header_files})

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
target_include_directories(${TARGET_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/../
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

find_package(Threads REQUIRED)
target_link_libraries(${TARGET_NAME}
    PUBLIC Threads::Threads prettyprint::prettyprint
    PRIVATE rang doctest::doctest)

# message(STATUS ${header_files} ${source_files})
# include(CMakePrintHelpers)
# cmake_print_properties(SOURCES ${header_files} ${source_files} PROPERTIES LOCTION LANGUAGE)
# cmake_print_properties(TARGETS ${TARGET_NAME} PROPERTIES TYPE)
# cmake_print_variables(${header_files} ${source_files})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${header_files} ${source_files})
