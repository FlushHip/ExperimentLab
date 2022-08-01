file(GLOB SOURCE_FILES *.c *.cpp)
file(GLOB HEADER_FILES *.h *.hpp)

init_target()

build_executable(${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
target_compile_definitions(${TARGET_NAME}
    PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE
    PRIVATE $<$<PLATFORM_ID:Windows>:_WIN32_WINNT=0x0A00>)
target_link_libraries(${TARGET_NAME} PRIVATE $<$<NOT:$<PLATFORM_ID:Windows>>:pthread>)

find_package(Boost 1.70.0 REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE Boost::headers
    Boost::disable_autolinking
    spdlog::spdlog_header_only)
