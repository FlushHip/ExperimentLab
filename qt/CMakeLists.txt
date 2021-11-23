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
    mainwindow.h
    forms/widget.h
    forms/finddialog.h
    forms/sortdialog.h
    forms/gotocelldialog.h
    forms/spreadsheet.h
    forms/hexspinbox.h
    forms/iconeditor.h
)

qt5_wrap_cpp(moc_list ${moc_header_list})

qt5_wrap_ui(ui_list
    forms/widget.ui
    forms/sortdialog.ui
    forms/gotocelldialog.ui
)

qt5_add_resources(qrc_list
    res/main.qrc
)

set(header_list
    ${moc_header_list}

    items/cell.h
    items/spreadsheet_compare.h

    # other header
    execution/base.h
    execution/dialog_execution.h
    execution/mainwindow_execution.h
    execution/spreadsheet_execution.h
    execution/customwidgets_execution.h
)

set(src_list
    main.cpp
    mainwindow.cpp
    forms/widget.cpp
    forms/finddialog.cpp
    forms/sortdialog.cpp
    forms/gotocelldialog.cpp
    forms/spreadsheet.cpp
    forms/hexspinbox.cpp
    forms/iconeditor.cpp

    items/cell.cpp
    items/spreadsheet_compare.cpp

    execution/dialog_execution.cpp
    execution/mainwindow_execution.cpp
    execution/spreadsheet_execution.cpp
    execution/customwidgets_execution.cpp
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
