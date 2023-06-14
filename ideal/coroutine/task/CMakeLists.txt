set(target_name co_task)

add_executable(${target_name}
    result.hpp
    task.hpp
    main.cpp)

target_compile_features(${target_name} PRIVATE cxx_std_20)

target_link_libraries(${target_name} PRIVATE doctest::doctest)

target_compile_definitions(${target_name} PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
