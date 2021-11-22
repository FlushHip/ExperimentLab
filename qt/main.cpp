#include <QApplication>

#include <vector>
#include <memory>

#include "execution/dialog_execution.h"
#include "execution/mainwindow_execution.h"
#include "execution/spreadsheet_execution.h"
#include "execution/customwidgets_execution.h"

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    std::vector<std::unique_ptr<ExecutionBase>> eList;

    eList.push_back(std::make_unique<CustomWidgetsExecution>());
    eList.push_back(std::make_unique<MainWindowExecution>());
    eList.push_back(std::make_unique<SpreadsheetExecution>());
    eList.push_back(std::make_unique<DialogExecution>());

    eList[0]->main();

    return app.exec();
}
