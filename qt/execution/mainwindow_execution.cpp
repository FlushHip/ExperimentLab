#include "mainwindow_execution.h"

#include "mainwindow.h"

#include <thread>
#include <chrono>

#include <QSplashScreen>

MainWindowExecution::MainWindowExecution() = default;

MainWindowExecution::~MainWindowExecution() = default;

int MainWindowExecution::main()
{
    QSplashScreen splash(QPixmap(":/images/splash.jpg"));
    splash.show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;

    splash.showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::black);

    mainWindow_ = std::make_unique<MainWindow>();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);

    splash.showMessage(QObject::tr("Loading modules..."), topRight, Qt::black);
    std::this_thread::sleep_for(2s);

    splash.showMessage(QObject::tr("Connectting networks..."), topRight, Qt::black);
    std::this_thread::sleep_for(2s);

    mainWindow_->show();

    splash.finish(mainWindow_.get());

    return 0;
}
