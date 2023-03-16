#include <iostream>

#include <QApplication>
#include <QTranslator>

#include <lib/logger.hpp>

#include "login_main_dlg.h"

int main(int argc, char* argv[]) {
    hestina::logger::init(spdlog::level::info);

    LOG_INFO << "hestina-client, Local : " << QLocale().name().toStdString();

    QApplication app(argc, argv);
    QTranslator translator;
    translator.load("i18n/lang_zh_CN.qm");
    QCoreApplication::installTranslator(&translator);

    hestina::client::ui::login_main_dlg login_main_dlg;
    login_main_dlg.show();
    return app.exec();
}
