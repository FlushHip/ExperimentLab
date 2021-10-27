file (GLOB SOURCE_FILES *.c *.cpp)
file (GLOB HEADER_FILES *.h *.hpp)

init_target ()

build_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${TARGET_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/template/LeetCode)
