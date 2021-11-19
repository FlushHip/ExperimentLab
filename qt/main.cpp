#include <QApplication>

#include <QInputDialog>
#include <QProgressDialog>
#include <QMessageBox>
#include <QErrorMessage>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>

#include "forms/widget.h"
#include "forms/finddialog.h"
#include "forms/sortdialog.h"
#include "forms/gotocelldialog.h"

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    std::vector<std::unique_ptr<QWidget>> wList;

    wList.push_back(std::make_unique<GoToCellDialog>());
    wList.push_back(std::make_unique<FindDialog>());
    wList.push_back(std::make_unique<SortDialog>());
    wList.push_back(std::make_unique<Widget>());
    wList.push_back(std::make_unique<QInputDialog>());
    wList.push_back(std::make_unique<QProgressDialog>());
    wList.push_back(std::make_unique<QMessageBox>());
    wList.push_back(std::make_unique<QErrorMessage>());
    wList.push_back(std::make_unique<QColorDialog>());
    wList.push_back(std::make_unique<QFontDialog>());
    wList.push_back(std::make_unique<QFileDialog>());

    wList[0]->show();

    return app.exec();
}
