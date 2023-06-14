if(WIN32)
    set(files_root ${CMAKE_CURRENT_BINARY_DIR}/files)

    if(NOT EXISTS ${files_root})
        include(FetchContent)

        FetchContent_Declare(xpdf-tool-win
            GIT_REPOSITORY https://github.com/FlushHip/xpdf-tools-win.git
            GIT_TAG v4.04
            SOURCE_DIR ${files_root}
        )
        FetchContent_MakeAvailable(xpdf-tool-win)
    endif()
endif()
