add_executable(emc++ main.cpp)
set_target_properties(emc++ PROPERTIES FOLDER "effective c++/emc++")

target_compile_features(emc++ PUBLIC cxx_std_14)

target_link_libraries(emc++ widget)

add_subdirectory(pimpl)