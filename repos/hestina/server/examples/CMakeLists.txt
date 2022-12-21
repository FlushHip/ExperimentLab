add_executable(hestina-examples_tcp_test tcp_test.cpp)
target_link_libraries(hestina-examples_tcp_test PRIVATE hestina-lib)

add_executable(hestina-examples_logger_test logger_test.cpp)
target_link_libraries(hestina-examples_logger_test PRIVATE hestina-lib)
