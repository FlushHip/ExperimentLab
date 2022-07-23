add_library(tutorial_maths maths.cpp)
set_target_properties(tutorial_maths PROPERTIES FOLDER "tutorial")
target_include_directories(tutorial_maths
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(tutorial_maths PRIVATE EXPORTING_MATH)
#target_link_directories(tutorial_maths INTERFACE ${CMAKE_CURRENT_BINARY_DIR})

option(USE_MATHS "Use tutorial maths implementation" ON)
if(USE_MATHS)
    target_compile_definitions(tutorial_maths PRIVATE USE_MATHS)

    add_subdirectory(sqrt)
    target_link_libraries(tutorial_maths PRIVATE tutorial_math_sqrt)
endif()

#install(TARGETS tutorial_maths DESTINATION lib)
#install(FILES $<$<PLATFORM_ID:Windows>:$<TARGET_PDB_FILE:tutorial_maths>> DESTINATION lib OPTIONAL)
#install(FILES maths.h DESTINATION include/math)
