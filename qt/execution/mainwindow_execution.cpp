#include "mainwindow_execution.h"

#include "mainwindow.h"

MainWindowExecution::MainWindowExecution() = default;

MainWindowExecution::~MainWindowExecution() = default;

int MainWindowExecution::main()
{
    mainWindow_ = std::make_unique<MainWindow>();
    mainWindow_->show();
    return 0;
}
