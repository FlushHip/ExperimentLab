#include "MainWindow.h"

#include <QGridLayout>

#include "ChessFrame.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent) {

    setParent(parent);
    this->setFixedSize(500 - 2, 563);

    chessFrame_ = new ChessFrame(this);

    auto layout = new QGridLayout;
    layout->addWidget(chessFrame_);

    setLayout(layout);
}

MainWindow::~MainWindow() = default;
