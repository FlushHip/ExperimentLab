file(GLOB SOURCE_FILES *.c *.cpp)
file(GLOB HEADER_FILES *.h *.hpp)

init_target()

build_executable(${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
target_link_libraries(${TARGET_NAME} PRIVATE $<$<NOT:$<PLATFORM_ID:Windows>>:pthread>
    PRIVATE nlohmann_json::nlohmann_json)
