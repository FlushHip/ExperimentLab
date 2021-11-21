#include "dialog_execution.h"

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

int DialogExecution::main()
{
    wList_.push_back(std::make_unique<GoToCellDialog>());
    wList_.push_back(std::make_unique<FindDialog>());
    wList_.push_back(std::make_unique<SortDialog>());
    wList_.push_back(std::make_unique<Widget>());
    wList_.push_back(std::make_unique<QInputDialog>());
    //wList.push_back(std::make_unique<QProgressDialog>());
    wList_.push_back(std::make_unique<QMessageBox>());
    wList_.push_back(std::make_unique<QErrorMessage>());
    wList_.push_back(std::make_unique<QColorDialog>());
    wList_.push_back(std::make_unique<QFontDialog>());
    wList_.push_back(std::make_unique<QFileDialog>());

    wList_[0]->show();

    return 0;
}
