set(TARGET_NAME hestina-client)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(moc_header_list
    login_main_dlg.h
)

qt5_wrap_cpp(moc_list ${moc_header_list})

qt5_wrap_ui(ui_list
    login_main_dlg.ui
)

qt5_add_resources(qrc_list
    resource.qrc
)

set(app_rc_list

    # app.rc
)

set(header_list
    ${moc_header_list}
)

set(src_list
    main.cpp

    login_main_dlg.cpp
)

add_executable(${TARGET_NAME}
    ${ui_list}
    ${header_list}
    ${moc_list}
    ${src_list}
    ${qrc_list}
    ${app_rc_list}
)

set_target_properties(${TARGET_NAME}
    PROPERTIES WIN32_EXECUTABLE $<NOT:$<CONFIG:DEBUG>>)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Widgets hestina-lib)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
