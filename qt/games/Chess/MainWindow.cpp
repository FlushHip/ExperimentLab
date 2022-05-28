#include "MainWindow.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

#include "ChessFrame.h"
#include "TimeFrame.h"
#include "GainFrame.h"
#include "common_define.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , chessFrame_(new ChessFrame(this))
    , timeFrame_(new TimeFrame(this))
    , gainFrame_{ new GainFrame(PieceBi::kRed, this)
        , new GainFrame(PieceBi::kBlack, this) }
{
    setParent(parent);
    setWindowTitle("Chinese Chess");

    auto mainLayout = new QGridLayout;
    auto gameLayout = new QGridLayout;
    auto rightLayout = new QVBoxLayout;
    auto leftLayout = new QVBoxLayout;
    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(gameLayout, 0, 1);
    mainLayout->addLayout(rightLayout, 0, 2);

    gameLayout->addWidget(chessFrame_);
    rightLayout->addWidget(timeFrame_);
    rightLayout->addStretch();

    leftLayout->addWidget(gainFrame_[0], 0, Qt::AlignTop);
    leftLayout->addWidget(gainFrame_[1], 0, Qt::AlignBottom);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(mainLayout);

    connect(chessFrame_, &ChessFrame::turnChanged
            , timeFrame_, &TimeFrame::changeBackgroundColor);
    chessFrame_->startFrame();

    connect(chessFrame_, &ChessFrame::pieceEated
        , gainFrame_[0], &GainFrame::addPiece);
    connect(chessFrame_, &ChessFrame::pieceEated
        , gainFrame_[1], &GainFrame::addPiece);
}

MainWindow::~MainWindow() = default;
