add_executable(mec++ main.cpp)
set_target_properties(mec++ PROPERTIES FOLDER "effective c++/mec++")

find_package(Boost 1.70.0 REQUIRED)
target_link_libraries(mec++ PRIVATE Boost::headers)

if(AppleClang)
    set_target_properties(mec++ PROPERTIES CXX_STANDARD 17)
else()
    target_compile_features(mec++ PUBLIC cxx_std_17)
endif()
