#include "MainWindow.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

#include "ChessFrame.h"
#include "TimeFrame.h"
#include "common_define.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , chessFrame_(new ChessFrame(this))
    , timeFrame_(new TimeFrame(this))
{

    setParent(parent);

    auto mainLayout = new QGridLayout;
    auto gameLayout = new QGridLayout;
    auto rightLayout = new QVBoxLayout;
    mainLayout->addLayout(gameLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);

    gameLayout->addWidget(chessFrame_);
    rightLayout->addWidget(timeFrame_);
    rightLayout->addStretch();

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(mainLayout);
}

MainWindow::~MainWindow() = default;
