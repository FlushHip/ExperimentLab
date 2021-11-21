#include "mainwindow.h"

#include <QApplication>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>

#include "forms/finddialog.h"
#include "forms/sortdialog.h"
#include "forms/gotocelldialog.h"
#include "forms/spreadsheet.h"

namespace
{
QString strippedName(const QString &fileName)
{
    return QFileInfo(fileName).fileName();
}
}

MainWindow::MainWindow()
{
    spreadsheet_ = new Spreadsheet;
    setCentralWidget(spreadsheet_);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    findDialog_ = nullptr;

    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");
}

void MainWindow::createActions()
{
    newAction_ = new QAction(tr("&New"), this);
    newAction_->setIcon(QIcon(":/images/new.png"));
    newAction_->setShortcut(QKeySequence::New);
    newAction_->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction_, &QAction::triggered, this, &MainWindow::newFile);

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFilesActions_[i] = new QAction(this);
        recentFilesActions_[i]->setVisible(false);
        connect(recentFilesActions_[i], &QAction::triggered, this, &MainWindow::openRecentFile);
    }

    exitAction_ = new QAction(tr("E&xit"), this);
    exitAction_->setShortcut(tr("Ctrl+Q"));
    exitAction_->setStatusTip(tr("Exit the application"));
    connect(exitAction_, &QAction::triggered, this, &MainWindow::close);

    // selectAllAction_

    // showGridAction_

    aboutQtAction_ = new QAction(tr("About &Qt"), this);
    aboutQtAction_->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction_, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    // File
    fileMenu_ = menuBar()->addMenu(tr("&File"));
    fileMenu_->addAction(newAction_);
    fileMenu_->addAction(openAction_);
    fileMenu_->addAction(saveAction_);
    fileMenu_->addAction(saveAsAction_);

    separatorAction_ = fileMenu_->addSeparator();

    for (int i = 0; i < MaxRecentFiles; ++i) {
        fileMenu_->addAction(recentFilesActions_[i]);
    }

    fileMenu_->addSeparator();

    fileMenu_->addAction(exitAction_);

    // Edit
    editMenu_ = menuBar()->addMenu(tr("&Edit"));
    editMenu_->addAction(cutAction_);
    editMenu_->addAction(copyAction_);
    editMenu_->addAction(pasteAction_);
    editMenu_->addAction(deleteAction_);

    selectSubMenu_ = editMenu_->addMenu(tr("&Select"));
        selectSubMenu_->addAction(selectRowAction_);
        selectSubMenu_->addAction(selectColumnAction_);
        selectSubMenu_->addAction(selectAllAction_);

    editMenu_->addSeparator();

    editMenu_->addAction(findAction_);
    editMenu_->addAction(goToCellAction_);

    // Tools
    toolsMenu_ = menuBar()->addMenu(tr("&Tools"));
    toolsMenu_->addAction(recalculateAction_);
    toolsMenu_->addAction(sortAction_);

    // Options
    optionsMenu_ = menuBar()->addMenu(tr("&Options"));
    optionsMenu_->addAction(showGridAction_);
    optionsMenu_->addAction(autoRecalcAction_);

    menuBar()->addSeparator();

    // Help
    helpMenu_ = menuBar()->addMenu(tr("&Help"));
    helpMenu_->addAction(aboutAction_);
    helpMenu_->addAction(aboutQtAction_);
}

void MainWindow::createContextMenu()
{
    /*
    spreadsheet_->addAction(cutAction_);
    spreadsheet_->addAction(copyAction_);
    spreadsheet_->addAction(pasteAction_);
    spreadsheet_->setContextMenuPolicy(Qt::ActionsContextMenu);
    */
}

void MainWindow::createToolBars()
{
    fileToolBar_ = addToolBar(tr("&File"));
    fileToolBar_->addAction(newAction_);
    fileToolBar_->addAction(openAction_);
    fileToolBar_->addAction(saveAction_);

    editToolBar_ = addToolBar(tr("&Edit"));
    editToolBar_->addAction(cutAction_);
    editToolBar_->addAction(copyAction_);
    editToolBar_->addAction(pasteAction_);
    editToolBar_->addSeparator();
    editToolBar_->addAction(findAction_);
    editToolBar_->addAction(goToCellAction_);
}

void MainWindow::createStatusBar()
{
    locationLabel_ = new QLabel(" W999 ");
    locationLabel_->setAlignment(Qt::AlignHCenter);
    locationLabel_->setMinimumSize(locationLabel_->sizeHint());

    formulaLabel_ = new QLabel;
    formulaLabel_->setIndent(3);

    statusBar()->addWidget(locationLabel_);
    statusBar()->addWidget(formulaLabel_, 1);

    connect(spreadsheet_, &Spreadsheet::currentCellChanged, this, &MainWindow::updateStatusBar);
    connect(spreadsheet_, &Spreadsheet::modified, this, &MainWindow::spreadsheetModified);

    updateStatusBar();
}
void MainWindow::updateStatusBar()
{
    locationLabel_->setText(spreadsheet_->currentLocation());
    formulaLabel_->setText(spreadsheet_->currentFormula());
}

void MainWindow::spreadsheetModified()
{
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (okToContinue()) {
        spreadsheet_->clear();
        setCurrentFile("");
    }
}
bool MainWindow::okToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Spreadsheet")
            , tr("The document has been modified.\n"
                "Do you want to save your changes?")
            , QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }

    return true;
}

void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Spreadsheet")
            , "."
            , tr("Spreadsheet file (*.sp)"));
        if (!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}

bool MainWindow::loadFile(const QString &fileName)
{
    if (!spreadsheet_->readFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), StatusBarMessageTimeout);
    return true;
}

bool MainWindow::save()
{
    if (curFile_.isEmpty()) {
        return false;
    }
    return saveFile(curFile_);
}

bool MainWindow::saveFile(const QString &fileName)
{
    if (!spreadsheet_->writeFile(fileName)) {
        statusBar()->showMessage(tr("Saving cancled"), StatusBarMessageTimeout);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), StatusBarMessageTimeout);
    return true;
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save Spreadsheet")
        , "."
        , tr("Spreadsheet file (*.sp)"));
    if (fileName.isEmpty()) {
        return false;
    }

    return saveFile(fileName);
}

void MainWindow::openRecentFile()
{
    if (okToContinue()) {
        auto action = qobject_cast<QAction *>(sender());
        if (action) {
            loadFile(action->data().toString());
        }
    }
}

void MainWindow::writeSettings()
{

}

void MainWindow::readSettings()
{

}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile_ = fileName;
    setWindowModified(false);

    QString shownName(tr("Untitled"));
    if (!curFile_.isEmpty()) {
        shownName = strippedName(curFile_);
        recentFiles_.removeAll(curFile_);
        recentFiles_.prepend(curFile_);
        updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Spreadsheet")));
}

void MainWindow::updateRecentFileActions()
{
    {
        QMutableStringListIterator i(recentFiles_);
        while (i.hasNext()) {
            if (!QFile::exists(i.next())) {
                i.remove();
            }
        }
    }

    for (int i = 0; i < MaxRecentFiles; ++i) {
        if (i < recentFiles_.count()) {
            QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(recentFiles_[i]));

            recentFilesActions_[i]->setText(text);
            recentFilesActions_[i]->setData(recentFiles_[i]);

            recentFilesActions_[i]->setVisible(true);
        } else {
            recentFilesActions_[i]->setVisible(true);
        }
    }

    separatorAction_->setVisible(!recentFiles_.isEmpty());
}
