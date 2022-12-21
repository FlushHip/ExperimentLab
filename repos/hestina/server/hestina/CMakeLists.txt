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

target_sources(${TARGET_NAME} PRIVATE ${source_files})

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
target_include_directories(${TARGET_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/../
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

find_package(Threads REQUIRED)
target_link_libraries(${TARGET_NAME}
    PUBLIC Threads::Threads prettyprint::prettyprint
    PRIVATE rang doctest::doctest)
