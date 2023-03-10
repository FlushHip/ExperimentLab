cmake_minimum_required(VERSION 3.20)

add_executable(rpc_unittest
    logger.hpp
    io_context_pool.hpp
    com_define.hpp
    connection.hpp
    router.hpp
    rpc_client.hpp
    rpc_server.hpp

    main.cpp)

find_package(Boost 1.70.0 REQUIRED)

target_compile_features(rpc_unittest PRIVATE cxx_std_17)
target_link_libraries(rpc_unittest
    PRIVATE spdlog::spdlog_header_only
    nlohmann_json::nlohmann_json
    doctest::doctest
    Boost::headers
    Boost::disable_autolinking)
target_compile_definitions(rpc_unittest PRIVATE DOCTEST_CONFIG_IMPLEMENT)
