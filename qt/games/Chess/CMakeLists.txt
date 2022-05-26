set(TARGET_NAME Chess)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(moc_header_list
    MainWindow.h
    ChessFrame.h
    TimeFrame.h
)

qt5_wrap_cpp(moc_list ${moc_header_list})

qt5_wrap_ui(ui_list
)

qt5_add_resources(qrc_list
    resource.qrc
)

set(header_list
    ${moc_header_list}

    common_define.h
    Piece.h
)

set(src_list
    main.cpp
    Piece.cpp

    MainWindow.cpp
    ChessFrame.cpp
    TimeFrame.cpp
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

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Widgets)
