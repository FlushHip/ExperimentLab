# https://doc.qt.io/qt-5/qtwidgets-widgets-tetrix-example.html

set(TARGET_NAME Tetrix)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(moc_header_list
    #forms/plotter.h
    TetrixWindow.h
    TetrixBoard.h
)

qt5_wrap_cpp(moc_list ${moc_header_list})

qt5_wrap_ui(ui_list
    #forms/gotocelldialog.ui
)

qt5_add_resources(qrc_list
    #res/main.qrc
)

set(header_list
    ${moc_header_list}

    TetrixPiece.h
)

set(src_list
    main.cpp
    TetrixWindow.cpp
    TetrixBoard.cpp
    TetrixPiece.cpp
)

add_executable(${TARGET_NAME}
    ${ui_list}
    ${header_list}
    ${moc_list}
    ${src_list}
    ${qrc_list}
)

set_target_properties(${TARGET_NAME}
    PROPERTIES WIN32_EXECUTABLE $<NOT:$<CONFIG:DEBUG>>)

target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Widgets)
