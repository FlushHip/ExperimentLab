# Init Qt5_DIR
if ("${Qt5_DIR}" STREQUAL "")
    file (TO_CMAKE_PATH "$ENV{Qt5_DIR}" Qt5_DIR)
    set (Qt5_DIR ${Qt5_DIR} CACHE PATH "Qt5_DIR dependency path" FORCE)
endif ()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

add_subdirectory(gui-tutorial)
add_subdirectory(games)
