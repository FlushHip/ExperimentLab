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
    )

    target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
endif()
