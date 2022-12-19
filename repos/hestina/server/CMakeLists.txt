set(TARGET_NAME hestina-server)

if(UNIX)
    add_executable(${TARGET_NAME}
        main.cpp
        log/logger.h
        log/logger.cpp
        net/tcp_server.h
        net/tcp_server.cpp
        net/poller.h
        net/poller.cpp
        net/event_loop.h
        net/event_loop.cpp
        net/channel.h
        net/channel.cpp
        net/addr.h
        net/addr.cpp
        net/socket.h
        net/socket.cpp
        net/acceptor.h
        net/acceptor.cpp
        net/connection.h
        net/connection.cpp
        net/callback.h
        net/buffer.h
        net/buffer.cpp
        net/eloop_thread_pool.h
        net/eloop_thread_pool.cpp
        net/tcp_client.h
        net/tcp_client.cpp
        net/connector.h
        net/connector.cpp
        timer/timer.h
        timer/timer.cpp
        timer/timer_queue.h
        timer/timer_queue.cpp

        # unittest
        unittest/doctest_impl.cpp
        unittest/logger_unittest.cpp
        unittest/timer_unittest.cpp

        unittest/tcp_unittest.cpp
    )

    target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
    target_include_directories(${TARGET_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

    find_package(Threads REQUIRED)
    target_link_libraries(${TARGET_NAME} PRIVATE Threads::Threads rang prettyprint::prettyprint doctest::doctest)

    # target_compile_definitions(${TARGET_NAME} PRIVATE DOCTEST_CONFIG_IMPLEMENT)
    include(${DOCTEST_SRCIPTS_CMAKE_DIR}/doctest.cmake)
    doctest_discover_tests(${TARGET_NAME})
endif()
