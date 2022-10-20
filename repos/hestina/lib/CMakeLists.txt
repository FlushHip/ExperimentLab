add_library(hestina-lib STATIC
    utils.h
    utils.cpp
    logger.hpp
)

target_compile_features(hestina-lib PRIVATE cxx_std_17)
target_include_directories(hestina-lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../)

target_link_libraries(hestina-lib
    PUBLIC spdlog::spdlog_header_only
)
