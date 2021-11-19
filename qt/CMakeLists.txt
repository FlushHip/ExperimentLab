# Init Qt5_DIR
if ("${Qt5_DIR}" STREQUAL "")
    file (TO_CMAKE_PATH "$ENV{Qt5_DIR}" Qt5_DIR)
    set (Qt5_DIR ${Qt5_DIR} CACHE PATH "Qt5_DIR dependency path" FORCE)
endif ()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(moc_header_list
    forms/widget.h
    forms/finddialog.h
    forms/sortdialog.h
    forms/gotocelldialog.h
)

qt5_wrap_cpp(moc_list ${moc_header_list})

qt5_wrap_ui(ui_list
    forms/widget.ui
    forms/sortdialog.ui
    forms/gotocelldialog.ui
)

qt5_add_resources(qrc_list
)

set(header_list
    ${moc_header_list}

    # other header
)

set(src_list
    main.cpp
    forms/widget.cpp
    forms/finddialog.cpp
    forms/sortdialog.cpp
    forms/gotocelldialog.cpp
)

add_executable(qtcmake
    ${ui_list}
    ${header_list}
    ${moc_list}
    ${src_list}
    ${qrc_list}
)

set_target_properties(qtcmake
    PROPERTIES WIN32_EXECUTABLE $<NOT:$<CONFIG:DEBUG>>)

target_link_libraries(qtcmake PRIVATE Qt5::Widgets)
