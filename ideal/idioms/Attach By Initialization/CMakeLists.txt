if(NOT MSVC)
    return()
endif()

set(CMAKE_MFC_FLAG 2)

add_executable(attach_by_initialization EXCLUDE_FROM_ALL WIN32 main.cpp)
target_compile_definitions(attach_by_initialization PRIVATE _AFXDLL _UNICODE)
target_link_options(attach_by_initialization PRIVATE "/entry:wWinMainCRTStartup")

set_target_properties(attach_by_initialization PROPERTIES FOLDER "c++ idioms")
