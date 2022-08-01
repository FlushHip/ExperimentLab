file(GLOB SOURCE_FILES *.c *.cpp)
file(GLOB HEADER_FILES *.h *.hpp)

init_target()

build_executable(${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

target_compile_definitions(${TARGET_NAME} PRIVATE
    _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
    _CRT_SECURE_NO_WARNINGS
    _WIN32_WINNT=0x0601)

find_package(Boost 1.70.0 REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE
    Boost::headers
    Boost::disable_autolinking
    cinatra::cinatra)
