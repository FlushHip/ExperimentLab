file (GLOB SOURCE_FILES *.c *.cpp)
file (GLOB HEADER_FILES *.h *.hpp)

init_target ()

build_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

if(AppleClang)
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17)
else()
    target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
endif()