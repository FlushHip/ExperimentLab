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
#include <QSettings>

#include "forms/finddialog.h"
#include "forms/sortdialog.h"
#include "forms/gotocelldialog.h"
#include "forms/spreadsheet.h"

#include "items/spreadsheet_compare.h"

namespace
{
QString strippedName(const QString &fileName)
{
    return QFileInfo(fileName).fileName();
}
}

MainWindow::MainWindow()
    : findDialog_(nullptr)
{
    spreadsheet_ = new Spreadsheet;
    setCentralWidget(spreadsheet_);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");
}

MainWindow::~MainWindow() = default;

void MainWindow::createActions()
{
    newAction_ = new QAction(tr("&New"), this);
    newAction_->setIcon(QIcon(":/images/new.png"));
    newAction_->setShortcut(QKeySequence::New);
    newAction_->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction_, &QAction::triggered, this, &MainWindow::newFile);

    openAction_ =  new QAction(tr("&Open"), this);
    openAction_->setIcon(QIcon(":/images/open.png"));
    openAction_->setShortcut(QKeySequence::Open);
    openAction_->setStatusTip(tr("Open a spreadsheet file"));
    connect(openAction_, &QAction::triggered, this, &MainWindow::open);

    saveAction_ = new QAction(tr("&Save"), this);
    saveAction_->setIcon(QIcon(":/images/save.png"));
    saveAction_->setShortcut(QKeySequence::Save);
    saveAction_->setStatusTip(tr("Save spreadsheet file"));
    connect(saveAction_, &QAction::triggered, this, &MainWindow::save);

    saveAsAction_ = new QAction(tr(("Save &As")), this);
    saveAsAction_->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction_, &QAction::triggered, this, &MainWindow::saveAs);

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFilesActions_[i] = new QAction(this);
        recentFilesActions_[i]->setVisible(false);
        connect(recentFilesActions_[i], &QAction::triggered, this, &MainWindow::openRecentFile);
    }

    exitAction_ = new QAction(tr("E&xit"), this);
    exitAction_->setShortcut(tr("Ctrl+Q"));
    exitAction_->setStatusTip(tr("Exit the application"));
    connect(exitAction_, &QAction::triggered, this, &MainWindow::close);

    cutAction_ = new QAction(tr("Cu&t"), this);
    cutAction_->setIcon(QIcon(":/images/cut.png"));
    cutAction_->setShortcut(QKeySequence::Cut);
    connect(cutAction_, &QAction::triggered, spreadsheet_, &Spreadsheet::cut);

    copyAction_ = new QAction(tr("&Copy"), this);
    copyAction_->setIcon(QIcon(":/images/copy.png"));
    copyAction_->setShortcut(QKeySequence::Copy);
    connect(copyAction_, &QAction::triggered, spreadsheet_, &Spreadsheet::copy);

    pasteAction_ = new QAction(tr("&Paste"), this);
    pasteAction_->setIcon(QIcon(":/images/paste.png"));
    pasteAction_->setShortcut(QKeySequence::Paste);
    connect(pasteAction_, &QAction::triggered, spreadsheet_, &Spreadsheet::paste);

    deleteAction_ = new QAction(tr("&Delete"), this);
    deleteAction_->setShortcut(QKeySequence::Delete);
    connect(deleteAction_, &QAction::triggered, spreadsheet_, &Spreadsheet::del);

    selectRowAction_ = new QAction(tr("&Row"), this);
    connect(selectRowAction_, &QAction::triggered, spreadsheet_, &Spreadsheet::selectCurrentRow);

    selectColumnAction_ = new QAction(tr("&Column"), this);
    connect(selectColumnAction_, &QAction::triggered, spreadsheet_, &Spreadsheet::selectCurrentColumn);

    selectAllAction_ = new QAction(tr("&All"), this);
    selectAllAction_->setShortcut(QKeySequence::SelectAll);
    selectAllAction_->setToolTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction_, &QAction::triggered, spreadsheet_, &Spreadsheet::selectAll);

    findAction_ = new QAction(tr("&Find"), this);
    findAction_->setIcon(QIcon(":/images/find.png"));
    findAction_->setShortcut(QKeySequence::Find);
    connect(findAction_, &QAction::triggered, this, &MainWindow::find);

    goToCellAction_ = new QAction(tr("&Go to Cell"), this);
    goToCellAction_->setIcon(QIcon(":/images/gotocell.png"));
    goToCellAction_->setShortcut(tr("F5"));
    connect(goToCellAction_, &QAction::triggered, this, &MainWindow::goToCell);

    recalculateAction_ = new QAction(tr("&Recalculate"), this);
    recalculateAction_->setShortcut(tr("F9"));
    connect(recalculateAction_, &QAction::triggered, spreadsheet_, &Spreadsheet::recalculate);

    sortAction_ = new QAction(tr("&Sort"), this);
    connect(sortAction_, &QAction::triggered, this, &MainWindow::sort);

    showGridAction_ = new QAction(tr("&Show Grid"), this);
    showGridAction_->setCheckable(true);
    showGridAction_->setChecked(spreadsheet_->showGrid());
    showGridAction_->setToolTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction_, &QAction::toggled, spreadsheet_, &Spreadsheet::setShowGrid);

    autoRecalcAction_ = new QAction(tr("&Auto recalculate"), this);
    autoRecalcAction_->setCheckable(true);
    autoRecalcAction_->setChecked(spreadsheet_->autoRecalculate());
    connect(autoRecalcAction_, &QAction::toggled, spreadsheet_, &Spreadsheet::setAutoRecalculate);

    aboutAction_ = new QAction(tr("&About"), this);
    connect(aboutAction_, &QAction::triggered, this, &MainWindow::about);

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
    spreadsheet_->addAction(cutAction_);
    spreadsheet_->addAction(copyAction_);
    spreadsheet_->addAction(pasteAction_);
    spreadsheet_->setContextMenuPolicy(Qt::ActionsContextMenu);
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
    QSettings settings("Software Inc.", "Spreadsheet");

    settings.setValue("gemometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles_);
    settings.setValue("showGrid", showGridAction_->isChecked());
    settings.setValue("autoRecalc", autoRecalcAction_->isChecked());
}

void MainWindow::readSettings()
{
    QSettings settings("Software Inc.", "Spreadsheet");

    restoreGeometry(settings.value("gemometry").toByteArray());

    recentFiles_ = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid").toBool();
    showGridAction_->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecalc").toBool();
    autoRecalcAction_->setChecked(autoRecalc);
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

void MainWindow::find()
{
    if (!findDialog_) {
        findDialog_ = new FindDialog(this);
        connect(findDialog_, &FindDialog::findNext, spreadsheet_, &Spreadsheet::findNext);
        connect(findDialog_, &FindDialog::findPrevious, spreadsheet_, &Spreadsheet::findPrevious);
    }

    findDialog_->show();
    findDialog_->raise();
    findDialog_->activateWindow();
}

void MainWindow::goToCell()
{
    GoToCellDialog dialog(this);
    if (QDialog::Accepted == dialog.exec()) {
        QString str = dialog.getLocation();
        spreadsheet_->setCurrentCell(str.mid(1).toInt() - 1, str[0].unicode() - 'A');
    }
}

void MainWindow::sort()
{
    SortDialog dialog(this);
    QTableWidgetSelectionRange range = spreadsheet_->selectedRange();
    dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());

    if (dialog.exec() == QDialog::Accepted) {
        SpreadsheetCompare compare = dialog.compareObject();
        spreadsheet_->sort(compare);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Spreadsheet")
        , tr("<h2>Spreadsheet 1.1</h2>"
            "<p>Copyright &copy; 2021 Software Inc.</p>"
            "<p>FlushHip learn Qt.</p>"));
}
