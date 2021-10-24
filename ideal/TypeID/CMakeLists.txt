file (GLOB SOURCE_FILES *.c *.cpp)
file (GLOB HEADER_FILES *.h *.hpp)

init_target ()

build_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

find_package(Boost 1.70.0 REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE Boost::headers)
