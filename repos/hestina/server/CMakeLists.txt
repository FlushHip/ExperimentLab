set(TARGET_NAME hestina-server)

if(UNIX)
    add_executable(${TARGET_NAME}
        main.cpp
        log/logger.h
        log/logger.cpp
        net/tcp_server.h
        net/tcp_server.cpp
    )

    target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
endif()
