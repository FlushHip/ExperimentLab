if(NOT UNIX)
    return()
endif()

message(STATUS "compiler : " ${CMAKE_CXX_COMPILER_ID})

option(HESTINA_BUILD_EXAMPLES "Build hestina examples" ON)
option(HESTINA_BUILD_UNITTESTS "Build hestina unittests" ON)

include(GNUInstallDirs)

add_subdirectory(hestina)

if(HESTINA_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(HESTINA_BUILD_UNITTESTS)
    add_subdirectory(unittests)
endif()
