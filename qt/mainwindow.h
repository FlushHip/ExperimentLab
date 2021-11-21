#pragma once

#include <QMainWindow>

class QAction;
class QLabel;
class QMenu;
class QToolBar;
class FindDialog;
class Spreadsheet;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void find();
    void goToCell();
    void sort();
    void about();
    void openRecentFile();
    void updateStatusBar();
    void spreadsheetModified();

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void writeSettings();
    void readSettings();
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();

private:
    Spreadsheet *spreadsheet_;
    FindDialog *findDialog_;
    QLabel *locationLabel_;
    QLabel *formulaLabel_;
    QStringList recentFiles_;
    QString curFile_;

    enum { MaxRecentFiles = 5 };
    QAction *recentFilesActions_[MaxRecentFiles];
    QAction *separatorAction_;

    QMenu *fileMenu_;
    QMenu *editMenu_;
        QMenu *selectSubMenu_;
    QMenu *toolsMenu_;
    QMenu *optionsMenu_;
    QMenu *helpMenu_;

    QToolBar *fileToolBar_;
    QToolBar *editToolBar_;

    QAction *newAction_;
    QAction *openAction_;
    QAction *saveAction_;
    QAction *saveAsAction_;
    QAction *exitAction_;

    QAction *cutAction_;
    QAction *copyAction_;
    QAction *pasteAction_;
    QAction *deleteAction_;
    QAction *findAction_;
    QAction *goToCellAction_;

    QAction *recalculateAction_;
    QAction *sortAction_;

    QAction *showGridAction_;
    QAction *autoRecalcAction_;

    QAction *aboutAction_;
    QAction *aboutQtAction_;

    QAction *selectRowAction_;
    QAction *selectColumnAction_;
    QAction *selectAllAction_;

    enum { StatusBarMessageTimeout = 2000 };
};
