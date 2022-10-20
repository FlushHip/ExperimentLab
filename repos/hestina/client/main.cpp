#include <iostream>

#include <QApplication>

#include <lib/logger.hpp>

#include "client/login_main_dlg.h"
#include "login_main_dlg.h"

int main(int argc, char* argv[]) {
    hestina::logger::init(spdlog::level::info);

    LOG_INFO << "hestina-client";

    QApplication app(argc, argv);
    hestina::client::ui::login_main_dlg login_main_dlg;
    login_main_dlg.show();
    return app.exec();
}
