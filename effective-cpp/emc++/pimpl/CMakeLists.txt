file(GLOB source_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.*")

add_library(widget STATIC ${source_files})
set_target_properties(widget PROPERTIES FOLDER "effective c++/emc++")

target_compile_features(widget PUBLIC cxx_std_14)