# Init Qt5_DIR
if ("${Qt5_DIR}" STREQUAL "")
    file (TO_CMAKE_PATH "$ENV{Qt5_DIR}" Qt5_DIR)
    set (Qt5_DIR ${Qt5_DIR} CACHE PATH "Qt5_DIR dependency path" FORCE)
endif ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(qtcmake
    main.cpp

    forms/widget.ui

    forms/widget.h

    forms/widget.cpp
)

set_target_properties(qtcmake
    PROPERTIES WIN32_EXECUTABLE $<NOT:$<CONFIG:DEBUG>>)

target_link_libraries(qtcmake PRIVATE Qt5::Widgets)
