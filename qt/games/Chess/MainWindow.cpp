#include "MainWindow.h"

#include <QGridLayout>

#include "ChessFrame.h"
#include "common_define.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , chessFrame_(new ChessFrame(this)) {

    setParent(parent);

    auto layout = new QGridLayout;
    layout->addWidget(chessFrame_);

    setLayout(layout);
}

MainWindow::~MainWindow() = default;
